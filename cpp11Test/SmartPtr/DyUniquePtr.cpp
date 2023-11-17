#include "DyUniquePtr.h"

Song::Song(std::wstring singer, std::wstring song)
{
	m_singer = singer;
	m_song = song;

	m_identity = new char[100];
	memset(m_identity, 0, 100);
	memcpy(m_identity, "421122", 6);

	std::cout << "normal constructor: " << m_identity << std::endl;
}

Song::Song(const Song& temp)
{
	m_singer = temp.m_singer;
	m_song = temp.m_song;

	std::cout << "copy constructor" << std::endl;

	if (m_identity)
	{
		int size = sizeof(temp.m_identity);
		m_identity = new char[size];
		memset(m_identity, 0, size);
		memcpy(m_identity, temp.m_identity, size);
	}
}

Song::~Song()
{
	
}

////////////////////////////////////////////////////////////////////////////////////

DyUniquePtr::DyUniquePtr() 
	: m_song_unique_ptr(std::make_unique<Song>(L"Jay", L"star"))
{
	init();
}


DyUniquePtr::~DyUniquePtr()
{

}

void DyUniquePtr::init()
{
	std::wstring song = m_song_unique_ptr->m_song;

	auto singer = std::make_unique<Song>(L"Jay", L"star");

	std::vector<std::wstring> titles = { singer->m_song };
	//变为右值, unique_ptr只允许移动，无法拷贝，因为内部没有引用计数，只单纯的保存原始指针
	std::unique_ptr<Song> singer2 = std::move(singer);
	auto singer3 = songFactory(L"JJ", L"southRiver");

	songVector();
}

std::unique_ptr<Song> DyUniquePtr::songFactory(const std::wstring& artist, const std::wstring& title)
{
	return std::make_unique<Song>(artist, title);
}

void DyUniquePtr::songVector()
{
	std::vector<std::unique_ptr<Song>> songs;
	songs.push_back(std::make_unique<Song>(L"B'z", L"Juice"));
	songs.push_back(std::make_unique<Song>(L"Namie Amuro", L"Funky Town"));
	songs.push_back(std::make_unique<Song>(L"Kome Kome Club", L"Kimi ga Iru Dake de"));
	songs.push_back(std::make_unique<Song>(L"Ayumi Hamasaki", L"Poker Face"));

	for (const auto& iter : songs) //此处需用引用，unique_ptr不允许拷贝，不用引用会调用拷贝构造（复制构造被废弃）
	{
		std::wcout << L"Artist: " << iter->m_song << L"   Title: " << iter->m_singer << std::endl;
	}
}

