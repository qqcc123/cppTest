#pragma once

//���ƹ��캯�� https://zh.cppreference.com/w/cpp/language/copy_constructor#.E5.90.88.E6.A0.BC.E7.9A.84.E5.A4.8D.E5.88.B6.E6.9E.84.E9.80.A0.E5.87.BD.E6.95.B0
//�ƶ����캯�� https://zh.cppreference.com/w/cpp/language/move_constructor#.E5.90.88.E6.A0.BC.E7.9A.84.E7.A7.BB.E5.8A.A8.E6.9E.84.E9.80.A0.E5.87.BD.E6.95.B0
//���Ƹ�ֵ����� https://zh.cppreference.com/w/cpp/language/copy_assignment#.E5.90.88.E6.A0.BC.E7.9A.84.E5.A4.8D.E5.88.B6.E8.B5.8B.E5.80.BC.E8.BF.90.E7.AE.97.E7.AC.A6
//�ƶ���ֵ����� https://zh.cppreference.com/w/cpp/language/move_assignment#.E5.90.88.E6.A0.BC.E7.9A.84.E7.A7.BB.E5.8A.A8.E8.B5.8B.E5.80.BC.E8.BF.90.E7.AE.97.E7.AC.A6

#include <iostream>

class Parent
{
public:
	//�Զ����˹��캯��(��ͨ���죬������������һ��)�����ε�Ĭ�Ϲ��캯��
	//explicit��ֹ��ʽ����ת�� eg: Parent a = 1;
	explicit Parent(int a);  

	explicit Parent(int a, int b);

	//���ƹ��캯�� (����3����������)
	//1. ��ʼ����T a = b; �� T a(b); ���� b �������� T��
	//2. ����ʵ�δ��ݣ�f(a); ������ a �������� T �� f �� void f(T t)��
	//3. �������أ����� T f() �����ĺ����ڲ��� return a; ������ a �������� T ����û���ƶ����캯��
	Parent(const Parent& p); //�������캯����Ҳ�Ƹ��ƹ��죩

	//�ƶ����캯��
	//1.��ʼ����T a = std::move(b); �� T a(std::move(b)); ������ b �������� T ��
	//2.����ʵ�δ��ݣ�f(std::move(a)); ������ a �������� T �� f �� Ret f(T t) ��
	//3.�������أ����� T f() �����ĺ����е� return a; ������ a �������� T���� T ���ƶ����캯��
	Parent(const Parent&& p/*, int a*/);

	//��ֵ�����
	Parent& operator=(const Parent& p);

	//�ƶ���ֵ�����
	Parent& operator=(Parent&& p);

	virtual std::string getName();

	void hide1();

	virtual void hide2(int a);

    virtual ~Parent();

private:
	int m_pAge = 0;

	std::string pName;
};

