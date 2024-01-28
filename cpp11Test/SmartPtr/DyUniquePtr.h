#pragma once

#include <iostream>
#include <memory>
#include <vector>

//https://learn.microsoft.com/zh-cn/cpp/cpp/how-to-create-and-use-weak-ptr-instances?view=msvc-170

class Song
{
public:
	explicit Song(std::wstring singer, std::wstring song);

	Song(const Song& temp);

	Song(Song&& temp);

	~Song();

	friend class DyUniquePtr;

private:
	std::wstring m_singer;

	std::wstring m_song;

	char* m_identity = nullptr;
};

class DyUniquePtr
{
public:
	DyUniquePtr();

	~DyUniquePtr();

	void init();

	std::unique_ptr<Song> songFactory(const std::wstring& artist, const std::wstring& title);

	void songVector();

private:
	std::unique_ptr<Song> m_song_unique_ptr;
};

///////////////////////////////////////////////////////////////////////////////
class LargeObject
{
public:
	LargeObject()
	{

	}

	~LargeObject()
	{
		int test = 0;
	}

	void DoSomething() {}
};

//声明在头文件，实现在cpp，不加static也可以
void ProcessLargeObject(const LargeObject& lo);

//以下两个接口需要加static，因为在该类的cpp中会导入该头文件，导致重复定义，static可以起到隔绝文件的作用
static void ProcessLargeObject1(const std::shared_ptr<LargeObject>& lo)
{
	int size = lo.use_count(); //引用计数不增加
}

static void ProcessLargeObject2(const std::shared_ptr<LargeObject> lo)
{
	int size = lo.use_count(); //引用计数增加
}

static void SmartPointerDemo()
{
	std::shared_ptr<LargeObject> pLarge(new LargeObject());
	pLarge->DoSomething();
	ProcessLargeObject1(pLarge);
	int size0 = pLarge.use_count();
	const LargeObject* lo = pLarge.get(); //引用计数不会增加
	const std::shared_ptr<LargeObject> lp = pLarge;
	int size = pLarge.use_count();

	std::unique_ptr<LargeObject> pLarge1(new LargeObject());
	//const std::unique_ptr<LargeObject> lp1 = pLarge1; //unique_ptr 没有拷贝构造和赋值运算符重载，因为没有引用计数
	pLarge1->DoSomething();
	pLarge1.reset();
}

