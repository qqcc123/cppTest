#include "DySharePtr.h"

DySharePtr::DySharePtr()
{
	init();
}

DySharePtr::~DySharePtr()
{

}

void DySharePtr::init()
{
	auto sp1 = std::make_shared<Song>(L"The Beatles", L"Im Happy Just to Dance With You");

	std::shared_ptr<Song> sp2(new Song(L"Lady Gaga", L"Just Dance"));

	std::shared_ptr<Song> sp5(nullptr);
	sp5 = std::make_shared<Song>(L"Elton John", L"I'm Still Standing");
}