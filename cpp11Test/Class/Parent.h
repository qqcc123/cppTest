#pragma once

//复制构造函数 https://zh.cppreference.com/w/cpp/language/copy_constructor#.E5.90.88.E6.A0.BC.E7.9A.84.E5.A4.8D.E5.88.B6.E6.9E.84.E9.80.A0.E5.87.BD.E6.95.B0
//移动构造函数 https://zh.cppreference.com/w/cpp/language/move_constructor#.E5.90.88.E6.A0.BC.E7.9A.84.E7.A7.BB.E5.8A.A8.E6.9E.84.E9.80.A0.E5.87.BD.E6.95.B0
//复制赋值运算符 https://zh.cppreference.com/w/cpp/language/copy_assignment#.E5.90.88.E6.A0.BC.E7.9A.84.E5.A4.8D.E5.88.B6.E8.B5.8B.E5.80.BC.E8.BF.90.E7.AE.97.E7.AC.A6
//移动赋值运算符 https://zh.cppreference.com/w/cpp/language/move_assignment#.E5.90.88.E6.A0.BC.E7.9A.84.E7.A7.BB.E5.8A.A8.E8.B5.8B.E5.80.BC.E8.BF.90.E7.AE.97.E7.AC.A6

#include <iostream>

class Parent
{
public:
	//自定义了构造函数(普通构造，拷贝构造其中一个)会屏蔽掉默认构造函数
	//explicit禁止隐式类型转换 eg: Parent a = 1;
	explicit Parent(int a);  

	explicit Parent(int a, int b);

	//复制构造函数 (以下3种情况会调用)
	//1. 初始化：T a = b; 或 T a(b); 其中 b 的类型是 T；
	//2. 函数实参传递：f(a); ，其中 a 的类型是 T 而 f 是 void f(T t)；
	//3. 函数返回：在像 T f() 这样的函数内部的 return a; ，其中 a 的类型是 T 且它没有移动构造函数
	Parent(const Parent& p); //拷贝构造函数（也称复制构造）

	//移动构造函数
	//1.初始化：T a = std::move(b); 或 T a(std::move(b)); ，其中 b 的类型是 T ；
	//2.函数实参传递：f(std::move(a)); ，其中 a 的类型是 T 且 f 是 Ret f(T t) ；
	//3.函数返回：在像 T f() 这样的函数中的 return a; ，其中 a 的类型是 T，且 T 有移动构造函数
	Parent(const Parent&& p/*, int a*/);

	//赋值运算符
	Parent& operator=(const Parent& p);

	//移动赋值运算符
	Parent& operator=(Parent&& p);

	virtual std::string getName();

	void hide1();

	virtual void hide2(int a);

    virtual ~Parent();

private:
	int m_pAge = 0;

	std::string pName;
};

