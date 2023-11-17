#pragma once

#include <iostream>
#include "Parent.h"

class Child : public Parent
{
public:
	Child();

	~Child();

	std::string getName();

	void hide1();

	void hide2(int a, int b);
};

