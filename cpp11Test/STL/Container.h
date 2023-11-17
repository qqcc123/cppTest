#pragma once

class Container
{
public:
	//如果类中未声明构造函数，则编译器提供隐式 inline 默认构造函数。
	Container();

	~Container() = default;

	void testArray();

	void testVector();

	void testList();

	void testMap();

	void testPair();

private:
	const int m_a = 0;

	int m_b = 2;

	int& m_c = m_b;

	const int& m_d = 2;
};

