#include "AsyncTask.h"
#include <cmath>
#include <functional>
#include <future>
#include <iostream>
#include <thread>

int f(int a, int b)
{
	return  std::pow(a, b);
}

AsyncTask::AsyncTask()
{
	task_lambda();
	task_bind();
	task_thread();
}

void AsyncTask::testAsyncTask()
{

}

void AsyncTask::task_lambda()
{
	std::packaged_task<int(int, int)> task([](int a, int b) {
			return  std::pow(a, b);
		});

	std::future<int> result = task.get_future();

	task(2, 9);

	std::cout << "task_lambda:\t" << result.get() << '\n';
}

void AsyncTask::task_bind()
{
	//std::bind将带参数的函数包装成int().因此packaged_task在定义的时候不需要指定参数
	std::packaged_task<int()> task(std::bind(f, 2, 10)); 
	std::future<int> result = task.get_future();
	task();

	std::cout << "task_bind:\t" << result.get() << '\n';
}

void AsyncTask::task_thread()
{
	std::packaged_task<int(int, int)> task([](int a, int b) {
			std::cout << "task_thread id:\t" << std::this_thread::get_id() << '\n';
			return  a + b;
		});
	std::future<int> result = task.get_future();

	std::thread(std::move(task), 8, 10).join();

	std::cout << "task_thread:\t" << result.get() << '\n';
}