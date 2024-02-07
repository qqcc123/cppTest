#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool {
public:
	ThreadPool(size_t size);

	~ThreadPool();

	template<class F, class... Args>
	auto enqueue(F&& f, Args&&... args)
		->std::future<typename std::result_of<F(Args...)>::type>;

private:
	std::vector<std::thread> works;

	std::queue<std::function<void()>> tasks;

	std::mutex queue_Mutex;

	std::condition_variable condition;

	bool isStop = false;
};

inline ThreadPool::ThreadPool(size_t threads)
{
	for (size_t i = 0; i < threads; i++)
		works.emplace_back( [this] {
			while (true)
			{
				std::function<void()> task;

				{
					std::unique_lock<std::mutex> lock(this->queue_Mutex);
					condition.wait(lock, [this] {
						return this->isStop || !tasks.empty();
					});
					
					if (isStop && tasks.empty()) {
						return;
					}

					task = std::move(tasks.front()); //ºı…Ÿ“ª¥ŒøΩ±¥
					tasks.pop();
				}
				
				task();
			}
		});
}

template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
	->std::future<typename std::result_of<F(Args...)>::type>
{
	using return_type = typename std::result_of<F(Args...)>::type; 

	auto task = std::make_shared<std::packaged_task<return_type()>>(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
	);

	std::future<return_type> res = task->get_future();

	{
		std::unique_lock<std::mutex> lock(queue_Mutex);

		if (isStop) {
			throw std::runtime_error("enqueue on stopped ThreadPool");
		}
			
		this->tasks.emplace([task] () {
			(*task)();
		});
	}

	condition.notify_one();

	return res;
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(queue_Mutex);
		isStop = true;
	}

	condition.notify_all();
	for (std::thread& it : works)
	{
		it.join();
	}
}


#endif



