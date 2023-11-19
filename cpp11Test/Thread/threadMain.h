#pragma once

#include <iostream>
#include "ThreadPool.h"
#include "DyThread.h"

namespace ThreadMain {
    void startThreadPool()
    {
        ThreadPool pool(4);
        std::vector< std::future<int> > results;

        std::mutex taskMutex;

        for (int i = 0; i < 8; ++i) {
            //results.emplace_back(
            pool.enqueue([i, &taskMutex] {
                {
                    std::unique_lock<std::mutex> lock(taskMutex);
                    std::cout << "hello world" << i << " thread id £º" << this_thread::get_id() << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return i * i;
            });
            //);
        }

        //for (auto&& result : results)
        //    std::cout << result.get() << ' ';
        //std::cout << std::endl;
    }

	void start() {
        std::cout << "ThreadMain::start " << std::endl;

        //DyThread thread;

        startThreadPool();

        std::cout << "ThreadMain::end " << std::endl;
	}
}