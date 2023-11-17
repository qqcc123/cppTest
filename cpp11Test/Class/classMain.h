#pragma once

#include "Parent.h"
#include "Child.h"

namespace ClassMain {
	Parent get()
	{
		Parent a(1);
		return a;
	}

	void start()
	{
		//重写的2个种类
		//1. 父类成员函数是不论是不是虚函数，子类同名函数参数可以不一样
		//2. 父类成员函数不是虚函数，子类同名函数必须参数一样
		Child c;
		c.hide1();
		c.hide2(1, 2);

		// "parent constructor" -> "child constructor" ->  "child : getName" -> "child destructor" -> "parent destructor"
		// 如果Parent的析构函数不加virtual，那么在如下多态的环境下，当p释放时，并不会调用child的析构函数，只会调用parent的析构函数
		// 导致内存泄漏。虚基类的析构函数都必须是virtual
		Parent* p = new Child();
		p->getName();
		delete p;
		return;

		std::cout << "ClassMain::start " << std::endl;

		//Parent p(1);

		//Parent p1 = {1, 2}; 如果没有explicit限制，直接（仅调用）调用Parent(int, int)，并不会接着调用拷贝构造
		//Parent a = get(); //如果没有Parent a，get函数产生的临时变量会在get结束后直接析构，如果有Parent a则在a的生命周期结束以后析构（类似智能指针）

		//如果Child中有自定义的析构函数，会使得类中的隐式移动复制构造函数失效
		Child c1;

		//则此时不会调用移动赋值构造（失效。因为自定义的析构函数可能会释放临时变量的数据成员的内存，而默认的隐式移动复制构造函数会复用临时变量的内存，
		//这样会导致出错）但是会调用复制构造函数
		Child c2 = std::move(c1); 


		//此例子如上解释（自定义析构函数会阻止移动赋值运算符）
		Child c3, c4;
		c3 = std::move(c4);

		std::cout << "ClassMain::end " << std::endl;
	}
}

