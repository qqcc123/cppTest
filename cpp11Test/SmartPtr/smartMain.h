#pragma once

#include <iostream>
#include "DyUniquePtr.h"
#include "test/testClass.h"
#include "qcSmartPtr/qc_unique_ptr.h"
#include "DySharePtr.h"

namespace SmartMain {

	void testQcUniquePtr()
	{
		auto a = new testClass;

		qc_unique_ptr<testClass> b(a);
		b->testSet(1);

		qc_unique_ptr<testClass> c = std::move(b);

		if (b)
		{
			std::cout << "b: " << b->testGet() << std::endl;
		}
		
		std::cout << "c: " << c->testGet() << std::endl;

		qc_unique_ptr<testClass> d;
		c->testSet(2);
		d = std::move(c);
		if (c)
		{
			std::cout << "c: " << c->testGet() << std::endl;
		}

		std::cout << "d: " << d->testGet() << std::endl;


	}

	void start() 
	{
		std::cout << "SmartMain::start " << std::endl;

		//testQcUniquePtr();

		DySharePtr* p = new DySharePtr();

		return;

		DyUniquePtr ptr;
	}

	
}
