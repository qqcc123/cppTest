#include "DySharePtr.h"

DySharePtr::DySharePtr()
{
	init();

	std::cout << "after init: " << std::endl;

	std::shared_ptr<testItem> b = m_itemVec.back();

	std::cout << "after init: " << b.use_count() << std::endl;

	m_itemVec.pop_back();

	std::cout << "after init1: " << b.use_count() << std::endl;

	for (const auto& iter : m_itemVec)
	{
		
	}
}

DySharePtr::~DySharePtr()
{

}

void DySharePtr::init()
{
	//auto sp1 = std::make_shared<Song>(L"The Beatles", L"Im Happy Just to Dance With You");

	//std::shared_ptr<Song> sp2(new Song(L"Lady Gaga", L"Just Dance"));

	//std::shared_ptr<Song> sp5(nullptr);
	//sp5 = std::make_shared<Song>(L"Elton John", L"I'm Still Standing");

	getItem();

	//std::shared_ptr<testItem> a = getItem();

	//std::cout << "init: " << a.use_count() << std::endl;
}

void DySharePtr::getItem()
{
	std::shared_ptr<testItem> item = std::make_shared<testItem>(2, "123");
	//移动构造会在智能指针内部将指针成员对象的值赋值，然后将亡值的指针设置为nullptr，不会调用testItem的移动构造
	m_itemVec.emplace_back(std::move(item)); 
	m_itemVec.emplace_back(std::make_shared<testItem>(3, "456"));
}