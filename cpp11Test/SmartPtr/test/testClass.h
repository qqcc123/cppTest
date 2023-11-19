#pragma once

#include <iostream>

class testClass
{
public:
	void testSet(int a);

	int testGet();

private:
	int m_integer = 0;
};