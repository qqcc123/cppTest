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

