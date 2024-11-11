//
// Created by 71466 on 20/9/2025.
//

#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H


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

class ThreadPool {
public:
    // 构造函数，启动指定数量的工作线程
    explicit ThreadPool(size_t threads = std::thread::hardware_concurrency())
        : stop(false), paused(false) {
        if (threads == 0) {
            threads = 1; // 至少一个线程
        }

        workers.reserve(threads);
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                for (;;) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);

                        // 等待任务或停止信号
                        this->condition.wait(lock, [this] {
                            return this->stop || (!this->tasks.empty() && !this->paused);
                        });

                        // 如果停止且任务队列为空，则退出
                        if (this->stop && this->tasks.empty()) {
                            return;
                        }

                        // 如果暂停且未停止，则继续等待
                        if (this->paused && !this->stop) {
                            continue;
                        }

                        // 获取任务
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    // 执行任务
                    task();
                }
            });
        }
    }

    // 禁止拷贝和移动
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    // 析构函数，等待所有任务完成
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    // 提交任务到线程池，返回future对象
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
        using return_type = std::invoke_result_t<F, Args...>;

        // 创建任务包装器
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();

        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            // 不允许在停止后添加任务
            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            // 将任务添加到队列
            tasks.emplace([task]() { (*task)(); });
        }

        // 通知一个等待的线程
        condition.notify_one();
        return res;
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
        condition.notify_all(); // 通知所有线程
    }

    // 获取等待中的任务数量
    size_t pending_tasks() const {
        std::unique_lock<std::mutex> lock(queue_mutex);
        return tasks.size();
    }

    // 获取线程数量
    size_t thread_count() const {
        return workers.size();
    }

    // 等待所有任务完成
    void wait() {
        std::unique_lock<std::mutex> lock(queue_mutex);
        condition_empty.wait(lock, [this] {
            return tasks.empty();
        });
    }

private:
    // 工作线程
    std::vector<std::thread> workers;

    // 任务队列
    std::queue<std::function<void()>> tasks;

    // 同步原语
    mutable std::mutex queue_mutex;
    std::condition_variable condition;
    std::condition_variable condition_empty;

    // 状态标志
    std::atomic<bool> stop;
    std::atomic<bool> paused;
};


#endif //THREADPOOL_THREADPOOL_H
