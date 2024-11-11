#include <iostream>
#include <chrono>
#include <random>

#include "ThreadPool.h"
#include "AdvancedThreadPool.h"

// 简单任务函数
int simple_task(int id) {
    std::cout << "Task " << id << " started on thread "
              << std::this_thread::get_id() << std::endl;

    // 模拟工作负载
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "Task " << id << " finished" << std::endl;
    return id * 2;
}

// 异常任务函数
void throwing_task() {
    throw std::runtime_error("Task failed intentionally");
}

int main() {
    // 创建线程池
    ThreadPool pool(4);

    // 提交多个任务
    std::vector<std::future<int>> results;
    for (int i = 0; i < 10; ++i) {
        results.emplace_back(
            pool.enqueue(simple_task, i)
        );
    }

    // 提交一个会抛出异常的任务
    auto exception_future = pool.enqueue(throwing_task);

    // 获取结果
    for (size_t i = 0; i < results.size(); ++i) {
        try {
            int result = results[i].get();
            std::cout << "Task " << i << " result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Task " << i << " exception: " << e.what() << std::endl;
        }
    }

    // 处理异常任务
    try {
        exception_future.get();
    } catch (const std::exception& e) {
        std::cout << "Exception task failed: " << e.what() << std::endl;
    }

    // 使用高级线程池
    AdvancedThreadPool advanced_pool(2, 8, 100);

    // 提交不同优先级的任务
    std::vector<std::future<int>> high_priority_results;
    std::vector<std::future<int>> normal_priority_results;

    for (int i = 0; i < 5; ++i) {
        high_priority_results.emplace_back(
            advanced_pool.enqueue(AdvancedThreadPool::Priority::High, simple_task, i + 100)
        );

        normal_priority_results.emplace_back(
            advanced_pool.enqueue(AdvancedThreadPool::Priority::Normal, simple_task, i + 200)
        );
    }

    // 等待所有任务完成
    advanced_pool.wait();

    // 获取线程池状态
    auto status = advanced_pool.get_status();
    std::cout << "Thread pool status: " << status.total_threads << " threads, "
              << status.active_threads << " active, " << status.idle_threads << " idle, "
              << status.pending_tasks << " pending tasks" << std::endl;

    return 0;
}