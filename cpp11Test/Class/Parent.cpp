#include "Parent.h"

Parent::Parent(int a)
{
	m_pAge = a;

	std::cout << "parent constructor" << std::endl;
}

Parent::Parent(int a, int b)
{
	m_pAge = a;
}

Parent::Parent(const Parent& p)
{
	std::cout << "Parent: 复制构造" << std::endl;
}

Parent::Parent(const Parent&& p/*, int a*/)
{
	std::cout << "Parent: 移动复制构造" << std::endl;
}

Parent& Parent::operator=(const Parent& p)
{
	std::cout << "Parent: 复制赋值运算符" << std::endl;
	return *this;
}

//移动赋值运算符
Parent& Parent::operator=(Parent&& p)
{
	std::cout << "Parent: 移动赋值运算符" << std::endl;
	return *this;
}

std::string Parent::getName()
{
	std::cout << "Parent: getName" << std::endl;
	return "parent::getName()";
}

Parent::~Parent()
{
	std::cout << "parent destructor" << std::endl;
}

void Parent::hide1()
{
	std::cout << "parent: hide1" << std::endl;
}

void Parent::hide2(int a)
{
	std::cout << "parent: hide2" << std::endl;
}