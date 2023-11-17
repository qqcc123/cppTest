#pragma once

#include <iostream>
#include "DyUniquePtr.h"

namespace SmartMain {
	void start() 
	{
		std::cout << "SmartMain::start " << std::endl;

		DyUniquePtr ptr;
	}
}
