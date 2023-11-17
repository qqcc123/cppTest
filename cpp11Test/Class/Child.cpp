#include "Child.h"
#include <iostream>

Child::Child() : Parent(2)
{
	std::cout << "child constructor" << std::endl;
}

Child::~Child()
{
	std::cout << "child destructor" << std::endl;
}

std::string Child::getName()
{
	std::cout << "child: getName" << std::endl;
	return "child::getName()";
}

void Child::hide1()
{
	std::cout << "child: hide1" << std::endl;
}

void Child::hide2(int a, int b)
{
	std::cout << "child: hide2" << std::endl;
}