#pragma once

#include <iostream>
#include <future>
#include <thread>
#include <iostream>
#include <cmath>
#include <thread>
#include <functional>

//https://zh.cppreference.com/w/cpp/thread/future  

//给一个异步操作的对象提供访问异步操作结果
namespace qcFuture {
    int f(int x, int y) { return std::pow(x, y); }

    void task_lambda()
    {
        std::packaged_task<int(int, int)> task([](int a, int b) {
            return std::pow(a, b);
        });
        std::future<int> result = task.get_future();

        task(2, 9);

        std::cout << "task_lambda:\t" << result.get() << '\n';
    }

    void task_bind()
    {
        std::packaged_task<int()> task(std::bind(f, 2, 11));
        std::future<int> result = task.get_future();

        task();

        //等待或从 std::future 提取值。若异步操作仍未提供值，则这些方法可能阻塞
        //此时值必须确定，否则阻塞，task()必须先一步执行
        std::cout << "task_bind:\t" << result.get() << '\n';

        
    }

    void task_thread()
    {
        std::packaged_task<int(int, int)> task(f);
        std::future<int> result = task.get_future();

        std::thread task_td(std::move(task), 2, 10);
        task_td.join();

        std::cout << "task_thread:\t" << result.get() << '\n';
    }


    void test() {
        task_lambda();
        task_bind();
        task_thread();

        return;

        // 来自 packaged_task 的 future
        std::packaged_task<int()> task([]() { return 7; }); // 包装函数
        std::future<int> f1 = task.get_future();  // 获取 future
        std::thread(std::move(task)).detach(); // 在线程上运行

        // 来自 async() 的 future
        std::future<int> f2 = std::async(std::launch::async, []() { return 8; });

        // 来自 promise 的 future
        std::promise<int> p;
        std::future<int> f3 = p.get_future();
        std::thread([&p] { p.set_value_at_thread_exit(9); }).detach();

        std::cout << "Waiting..." << std::flush;
        f1.wait();
        f2.wait();
        f3.wait();
        std::cout << "Done!\nResults are: "
            << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
    }

}
