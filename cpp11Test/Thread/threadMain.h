#pragma once

#include <iostream>
#include "ThreadPool.h"
#include "DyThread.h"
#include "AsyncTask.h"

namespace ThreadMain {
    enum TYPE {
        ADD,
        MUL,
    };

    struct Event {
        TYPE type;
        int result;
    };

    void startThreadPool()
    {
        ThreadPool pool(4);
        std::vector<std::future<int>> results;

        std::mutex taskMutex;

        for (int i = 0; i < 8; ++i) {
            pool.enqueue([i, &taskMutex] {
                {
                    std::unique_lock<std::mutex> lock(taskMutex);
                    std::cout << "hello world" << i << " thread id £º" << this_thread::get_id() << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return i * i;
            });
        }
    }

    void startThreadPool1()
    {
        ThreadPool pool(4);
        std::vector<std::future<Event>> results;
        for (int i = 0; i < 8; ++i) {
            results.emplace_back(
                pool.enqueue([i] {
                        {
                            std::cout << "hello " << i << " ,thread " << std::this_thread::get_id() << std::endl;
                            std::this_thread::sleep_for(std::chrono::seconds(2));
                            std::cout << "world " << i << std::endl;
                        }
                        Event e;
                        e.result = i * i;
                        e.type = i % 3 == 0 ? ADD : MUL;
                        return e;
                    })
            );
        }

        for (auto&& result : results)
        {
            Event e = result.get();
            std::cout << "type:  " << e.type  << ", result : " << e.result;
        }
            
        std::cout << std::endl;
    }

	void start() {
        std::cout << "ThreadMain::start " << std::endl;

        //DyThread thread;

        //startThreadPool();

        //startThreadPool1();

        AsyncTask task;

        std::cout << "ThreadMain::end " << std::endl;
	}
}