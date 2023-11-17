#include "Container.h"
#include <array>
#include <vector>
#include <list>
#include <map>
#include <Windows.h>
#include <algorithm>
#include <iostream>

Container::Container()
{
	testArray();

	testVector();
}

void Container::testArray()
{
	std::array<int, 4> arr = { 2,1,3,4 };
	std::sort(arr.begin(), arr.end(), [=](int a, int b) {
		return a > b;
	});
}

void Container::testVector()
{
	std::vector<int> vec = { 1,2,3 };
	vec.push_back(4);
	vec.pop_back();
	vec.assign(5, 2);
	vec.back() = 6;
	vec.front() = 3;
	vec.reserve(10);
	std::allocator<int> allocator = vec.get_allocator();
}

void Container::testList()
{
	std::list<int> list = { 1,2,3 };
}

void Container::testPair()
{
	std::pair<int, std::string> pair = std::make_pair<int, std::string>(1, "hello");
	int a = pair.first;
	std::string b = pair.second;

}

void Container::testMap()
{

}


