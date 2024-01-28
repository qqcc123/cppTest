#include <iostream>
#include <utility>

namespace AutoTest {
	template<class T, class U>
	auto add(T a, U b)
	{
		return a + b;
	}
}