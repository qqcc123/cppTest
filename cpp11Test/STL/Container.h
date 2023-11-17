#pragma once

class Container
{
public:
	//�������δ�������캯������������ṩ��ʽ inline Ĭ�Ϲ��캯����
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

