#include "DyThread.h"
#include <iostream>
#include <functional>

typedef void (*func)(int a);

const int get()
{
	return 1;
}

void thread_function(int a)
{
	std::cout << "thread_function: " << a << std::endl;
}

DyThread::DyThread() : m_flag1(2)
{
	init();
}

DyThread::~DyThread()
{

}

void DyThread::init()
{
	std::function<void(int)> f1 = std::bind(&thread_function, 1);
	auto lam = [=](int i){
		std::cout << "thread_function: " << i << std::endl;
	};
	func f2 = thread_function;
	std::thread t(f2, 1);

	std::thread t1(lam, 2);
	std::cout << "main thread\n";
	t.join();
	t1.join();
}