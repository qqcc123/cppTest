#pragma once
#include <iostream>
#include "Container.h"
#include <vector>
#include "Allocator/DyAllocator.h"

namespace StlMain {
    class Test {

    };

    void get(std::string&& text)
    {

    }

    void testStl()
    {
        Container stl;
    }

    void testAllocate()
    {
        int a[5] = { 0,1,2,3,4 };
        //unsigned int i;

        //std::vector<int, dy::allocator<int>> iv(a, a + 5);
        //for ( i = 0; i < iv.size(); i++)
        //{
        //    std::cout << iv[i] << "  ";
        //}
        //std::cout << std::endl;
    }

	void start()
	{
        std::cout << "StlMain::start " << std::endl;

        testAllocate();
        return;

        //Test bb;
        Test&& aa = Test();

        std::string i = "hello";
        //std::string && j = std::move(i);
        get(std::move(i));

        std::string foo = "foo-string";
        std::string bar = "bar-string";
        std::vector<std::string> myvector;

        myvector.push_back(foo);                    // copies
        myvector.push_back(std::move(bar));         // moves

        std::cout << "myvector contains:";
        for (std::string& x : myvector) std::cout << ' ' << x;

        testStl();

        std::cout << "StlMain::end " << std::endl;
	}
}