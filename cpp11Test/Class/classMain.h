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
		//��д��2������
		//1. �����Ա�����ǲ����ǲ����麯��������ͬ�������������Բ�һ��
		//2. �����Ա���������麯��������ͬ�������������һ��
		Child c;
		c.hide1();
		c.hide2(1, 2);

		// "parent constructor" -> "child constructor" ->  "child : getName" -> "child destructor" -> "parent destructor"
		// ���Parent��������������virtual����ô�����¶�̬�Ļ����£���p�ͷ�ʱ�����������child������������ֻ�����parent����������
		// �����ڴ�й©������������������������virtual
		Parent* p = new Child();
		p->getName();
		delete p;
		return;

		std::cout << "ClassMain::start " << std::endl;

		//Parent p(1);

		//Parent p1 = {1, 2}; ���û��explicit���ƣ�ֱ�ӣ������ã�����Parent(int, int)����������ŵ��ÿ�������
		//Parent a = get(); //���û��Parent a��get������������ʱ��������get������ֱ�������������Parent a����a���������ڽ����Ժ���������������ָ�룩

		//���Child�����Զ����������������ʹ�����е���ʽ�ƶ����ƹ��캯��ʧЧ
		Child c1;

		//���ʱ��������ƶ���ֵ���죨ʧЧ����Ϊ�Զ���������������ܻ��ͷ���ʱ���������ݳ�Ա���ڴ棬��Ĭ�ϵ���ʽ�ƶ����ƹ��캯���Ḵ����ʱ�������ڴ棬
		//�����ᵼ�³������ǻ���ø��ƹ��캯��
		Child c2 = std::move(c1); 


		//���������Ͻ��ͣ��Զ���������������ֹ�ƶ���ֵ�������
		Child c3, c4;
		c3 = std::move(c4);

		std::cout << "ClassMain::end " << std::endl;
	}
}

