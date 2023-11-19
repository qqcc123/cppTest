#include "testClass.h"

void testClass::testSet(int a)
{
	m_integer = a;

	std::cout << "test set: " << a << std::endl;
}

int testClass::testGet()
{
	std::cout << "test get: " << m_integer << std::endl;

	return m_integer;
}