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

//������ͷ�ļ���ʵ����cpp������staticҲ����
void ProcessLargeObject(const LargeObject& lo);

//���������ӿ���Ҫ��static����Ϊ�ڸ����cpp�лᵼ���ͷ�ļ��������ظ����壬static�����𵽸����ļ�������
static void ProcessLargeObject1(const std::shared_ptr<LargeObject>& lo)
{
	int size = lo.use_count(); //���ü���������
}

static void ProcessLargeObject2(const std::shared_ptr<LargeObject> lo)
{
	int size = lo.use_count(); //���ü�������
}

static void SmartPointerDemo()
{
	std::shared_ptr<LargeObject> pLarge(new LargeObject());
	pLarge->DoSomething();
	ProcessLargeObject1(pLarge);
	int size0 = pLarge.use_count();
	const LargeObject* lo = pLarge.get(); //���ü�����������
	const std::shared_ptr<LargeObject> lp = pLarge;
	int size = pLarge.use_count();

	std::unique_ptr<LargeObject> pLarge1(new LargeObject());
	//const std::unique_ptr<LargeObject> lp1 = pLarge1; //unique_ptr û�п�������͸�ֵ��������أ���Ϊû�����ü���
	pLarge1->DoSomething();
	pLarge1.reset();
}

