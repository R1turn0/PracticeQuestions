//
// Created by 71466 on 20/9/2025.
//

#ifndef THREADPOOL_ADVANCEDTHREADPOOL_H
#define THREADPOOL_ADVANCEDTHREADPOOL_H


#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <atomic>
#include <memory>
#include <type_traits>
#include <utility>
#include <map>

class AdvancedThreadPool {
public:
    // 任务优先级
    enum class Priority {
        High,
        Normal,
        Low
    };

    // 构造函数
    explicit AdvancedThreadPool(
        size_t min_threads = std::thread::hardware_concurrency(),
        size_t max_threads = std::thread::hardware_concurrency() * 2,
        size_t max_queue_size = 1000)
        : stop(false), paused(false),
          min_threads(min_threads), max_threads(max_threads),
          max_queue_size(max_queue_size),
          active_threads(0), idle_threads(0) {

        if (min_threads == 0) min_threads = 1;
        if (max_threads < min_threads) max_threads = min_threads;

        // 启动最小数量的工作线程
        for (size_t i = 0; i < min_threads; ++i) {
            add_worker();
        }

        // 启动线程管理线程
        manager_thread = std::thread([this] { manage_workers(); });
    }

    // 禁止拷贝和移动
    AdvancedThreadPool(const AdvancedThreadPool&) = delete;
    AdvancedThreadPool(AdvancedThreadPool&&) = delete;
    AdvancedThreadPool& operator=(const AdvancedThreadPool&) = delete;
    AdvancedThreadPool& operator=(AdvancedThreadPool&&) = delete;

    // 析构函数
    ~AdvancedThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }

        condition.notify_all();
        manager_condition.notify_all();

        for (auto& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }

        if (manager_thread.joinable()) {
            manager_thread.join();
        }
    }

    // 提交任务（带优先级）
    template<class F, class... Args>
    auto enqueue(Priority priority, F&& f, Args&&... args)
        -> std::future<std::invoke_result_t<F, Args...>> {

        using return_type = std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();

        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            // 检查队列是否已满
            if (tasks.size() >= max_queue_size) {
                throw std::runtime_error("task queue is full");
            }

            // 根据优先级添加任务
            PriorityTask pt{priority, [task]() { (*task)(); }};
            tasks.push(pt);

            // 更新任务计数
            task_counts[priority]++;
        }

        condition.notify_one();

        // 如果有必要，唤醒管理器添加更多线程
        if (should_add_worker()) {
            manager_condition.notify_one();
        }

        return res;
    }

    // 提交普通优先级任务
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) {
        return enqueue(Priority::Normal, std::forward<F>(f), std::forward<Args>(args)...);
    }

    // 暂停线程池
    void pause() {
        std::unique_lock<std::mutex> lock(queue_mutex);
        paused = true;
    }

    // 恢复线程池
    void resume() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            paused = false;
        }
        condition.notify_all();
    }

    // 获取线程池状态
    struct PoolStatus {
        size_t total_threads;
        size_t active_threads;
        size_t idle_threads;
        size_t pending_tasks;
        std::map<Priority, size_t> tasks_by_priority;
    };

    PoolStatus get_status() const {
        std::unique_lock<std::mutex> lock(queue_mutex);
        PoolStatus status;
        status.total_threads = workers.size();
        status.active_threads = active_threads;
        status.idle_threads = idle_threads;
        status.pending_tasks = tasks.size();
        status.tasks_by_priority = task_counts;
        return status;
    }

    // 调整线程池大小
    void resize(size_t new_min_threads, size_t new_max_threads) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        min_threads = new_min_threads;
        max_threads = new_max_threads;

        // 通知管理器重新评估线程数量
        manager_condition.notify_one();
    }

    // 等待所有任务完成
    void wait() {
        std::unique_lock<std::mutex> lock(queue_mutex);
        condition_empty.wait(lock, [this] {
            return tasks.empty() && active_threads == 0;
        });
    }

private:
    // 带优先级的任务定义
    struct PriorityTask {
        Priority priority;
        std::function<void()> task;

        // 优先级比较（数值越小优先级越高）
        bool operator<(const PriorityTask& other) const {
            return static_cast<int>(priority) > static_cast<int>(other.priority);
        }
    };

    // 工作线程函数
    void worker_function() {
        for (;;) {
            PriorityTask pt;

            {
                std::unique_lock<std::mutex> lock(queue_mutex);

                // 更新空闲线程计数
                idle_threads++;

                // 等待任务或停止信号
                condition.wait(lock, [this] {
                    return stop || (!tasks.empty() && !paused);
                });

                // 更新空闲线程计数
                idle_threads--;

                if (stop && tasks.empty()) {
                    return;
                }

                if (paused && !stop) {
                    continue;
                }

                // 获取最高优先级的任务
                pt = std::move(tasks.top());
                tasks.pop();

                // 更新任务计数
                task_counts[pt.priority]--;

                // 更新活动线程计数
                active_threads++;
            }

            // 执行任务
            try {
                pt.task();
            } catch (...) {
                // 捕获任务中的异常，防止影响线程
            }

            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                active_threads--;

                // 如果没有任务了，通知等待的线程
                if (tasks.empty() && active_threads == 0) {
                    condition_empty.notify_all();
                }
            }
        }
    }

    // 添加工作线程
    void add_worker() {
        workers.emplace_back([this] { worker_function(); });
    }

    // 判断是否需要添加工作线程
    bool should_add_worker() const {
        return (workers.size() < max_threads) &&
               (tasks.size() > workers.size() * 2) &&
               (idle_threads == 0);
    }

    // 判断是否需要减少工作线程
    bool should_remove_worker() const {
        return (workers.size() > min_threads) &&
               (idle_threads > 0) &&
               (tasks.size() < workers.size() / 2);
    }

    // 管理线程函数（动态调整线程数量）
    void manage_workers() {
        while (!stop) {
            std::unique_lock<std::mutex> lock(queue_mutex);

            manager_condition.wait_for(lock, std::chrono::seconds(1), [this] {
                return stop || should_add_worker() || should_remove_worker();
            });

            if (stop) {
                return;
            }

            // 添加工作线程
            if (should_add_worker()) {
                add_worker();
            }

            // 移除工作线程（通过停止信号）
            if (should_remove_worker()) {
                // 设置停止标志并通知一个线程退出
                stop = true; // 只是示例，实际实现需要更复杂的逻辑
                condition.notify_one();
                stop = false;

                // 找到并移除一个线程
                for (auto it = workers.begin(); it != workers.end(); ++it) {
                    if (it->get_id() == std::this_thread::get_id()) {
                        continue; // 不要移除自己
                    }

                    if (it->joinable()) {
                        it->detach(); // 或者使用更优雅的方式停止线程
                        workers.erase(it);
                        break;
                    }
                }
            }
        }
    }

private:
    // 工作线程
    std::vector<std::thread> workers;
    std::thread manager_thread;

    // 优先队列存储任务
    std::priority_queue<PriorityTask> tasks;

    // 同步原语
    mutable std::mutex queue_mutex;
    std::condition_variable condition;
    std::condition_variable condition_empty;
    std::condition_variable manager_condition;

    // 状态标志
    std::atomic<bool> stop;
    std::atomic<bool> paused;

    // 线程池配置
    size_t min_threads;
    size_t max_threads;
    size_t max_queue_size;

    // 运行时状态
    std::atomic<size_t> active_threads;
    std::atomic<size_t> idle_threads;

    // 任务统计
    std::map<Priority, size_t> task_counts;
};


#endif //THREADPOOL_ADVANCEDTHREADPOOL_H
