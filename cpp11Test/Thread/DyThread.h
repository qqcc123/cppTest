#pragma once

#include <Windows.h>
#include <thread>

using namespace std;

class DyThread
{
public:
	DyThread();

	~DyThread();

	void init();
	
private:
	const int m_flag1;
};

