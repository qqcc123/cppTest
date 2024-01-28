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

Song::Song(Song&& temp)
{
	m_singer = temp.m_singer;
	m_song = temp.m_song;
	m_identity = temp.m_identity;

	temp.m_identity = nullptr;
	temp.m_song = L"";
	temp.m_singer = L"";
}

Song::~Song()
{
	
}

////////////////////////////////////////////////////////////////////////////////////
/*
std::move是C++标准库中一个非常常用的函数，主要用于将一个左值引用转化成一个右值引用，
进而支持C++11新特性对移动语义以及完美转发的实现。实际上，std::move只是一个简单的转
换函数，通过使用std::remove_reference<T>::type&&进行类型转换，强制将一个左值引用或
者右值引用转化为一个右值引用。下面是std::move的一个常见定义：
template< class T >
typename std::remove_reference<T>::type&& move( T&& t ) 
{
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}

其中，T&&被称为universal or forwarding reference（转发引用），在模板函数中，这种引用
可以同时接受左值引用和右值引用。std::remove_reference<T>::type用于移除引用，获取原始
类型。static_cast<typename std::remove_reference<T>::type&&>(t)则用于进行类型转换。
通过std::move，原本不能调用移动构造函数或移动赋值函数的左值，就能很方便地调用这两个函
数了，从而实现移动语义，避免不必要的拷贝。

实际上，static_cast到右值引用并不会自动将原始对象的内容“置为空”。它只是将一个对象
的性质变更为"可被移动"，即表示该对象可以被挪走其内部资源到另一个对象中。是否将一个对
象的某些资源置空，依赖于你如何在对应的移动构造函数或移动赋值函数中处理。比如常见的是
在移动构造函数中，我们会将源对象的指针置为空，表示已经将其所有权移交给了新的对象。

以下是一个例子：

class MyString 
{
	char* _data;
	size_t _len;

public:
	MyString(MyString&& str) noexcept // 这是一个移动构造函数
	: _data(str._data), _len(str._len) 
	{
		str._data = nullptr; // 把原先对象的指针置空
		str._len = 0;
	}
};

在这个例子中，_data指针被移动到新的MyString对象，原MyString对象的_data被置为nullptr。
所以，static_cast到右值引用并不能自动将源对象置为空，决定是否将其置为空是开发者的职责，
这通常是通过在移动语义的相关函数中进行手动处理实现的。

默认的移动构造函数并不会将原始对象的指针置为 null。默认的移动构造函数仅仅做了一套浅复制
的行为，也就是复制该类的所有值，这包括了指向堆内存的指针，但并不包括将源对象指针置为 null。
因此，如果你创建的类含有原始指针或其他资源管理对象，应该提供自定义的移动构造函数和移动赋值
操作符，并在其中显式地将指针或者资源释放或置为 null，防止资源在移动后被多次删除。

对于C++标准库提供的智能指针，如std::unique_ptr和std::shared_ptr，它们在移动操作（移动构造或移动赋值）
后确实会将原对象置为"为空"。例如，std::unique_ptr在移动后，原std::unique_ptr会变成空指针，即它不再持
有或指向任何对象。这主要是因为std::unique_ptr的设计初衷就是保证对象的唯一拥有权或独占权，因此在移动操作后，原std::unique_ptr必须放弃对对象的管理权。

以下是一段使用std::unique_ptr进行移动操作的例子：

std::unique_ptr<int> ptr1(new int(5));
std::unique_ptr<int> ptr2(std::move(ptr1)); // 移动构造

// 此时，ptr1 为空

对于std::shared_ptr，移动操作并不改变引用计数，但会使原std::shared_ptr不再指向该对象。这是因为
std::shared_ptr允许对象拥有多个所有者，所以移动操作并不改变对象的所有者数量，只是改变了所有者的身份。
无论是std::unique_ptr还是std::shared_ptr，只要满足移动语义，编译器都会为它们自动生成移动构造函数和
移动赋值操作符，所以在实际使用中无需手动定义。

std::move 本身不会调用任何构造函数。
std::move 仅仅是将它的参数从左值转为右值，让它可以被移动构造函数或移动赋值操作符使用。实际上是否调用
了移动构造函数或移动赋值操作符，取决于你怎么使用 std::move 的结果。例如，之前的这些例子都会触发移动构造函数的调用：


std::unique_ptr<Song> s1 = std::make_unique<Song>(L"Jay", L"star");
std::unique_ptr<Song> s2 = std::move(s1); //调用移动赋值操作符

Song s1(L"Jay", L"star");
Song s2(std::move(s1)); //调用移动构造函数

在这两个例子中，s1 被 std::move 转为了右值，然后被 s2 的移动构造函数或移动赋值操作符接管了资源。
但仅仅运行 std::move(s1)不会有任何影响。

这是因为智能指针，比如 std::unique_ptr 和原始指针在行为上是有区别的。
std::unique_ptr 是一个模板类，它内部定义了移动构造函数和移动赋值运算符。所以当执行 
std::unique_ptr s2 = std::move(s1); 这行代码时，s2 是通过移动构造函数来构造的，这个过程中 s1 
的所有权被转移给了 s2，s1 之后就不再拥有这个对象的所有权。


然而，原始指针并不具备这些特性。当你执行 Song* s2 = std::move(s1); 这行代码时，实质上只是把 s1 的值
（对象地址）赋给了 s2。这没有涉及到任何构造行为，因此也就不会调用移动构造函数。在这个过程中，s1 并没有
失去对对象的所有权，s2 只是得到了一个指向同样对象的新指针而已。如果 s1 或者 s2 其中任何一个被删除，这个
对象就会被删除，可以说原始指针的这种行为可能会导致对象的生命周期管理上出现问题。因此，当需要“移动”对象
所有权的时候，应该使用智能指针，而不是原始指针。

无论如何原始指针（raw pointers）不能定义移动构造函数。移动构造函数是类的一种特殊成员函数，可用于将资源从
一个对象转移到另一个对象，而原始指针是C++的内建类型，不是类或结构，因此你不能为它定义任何类型的构造函数。
原始指针只是一个存储对象内存地址的变量，它本身并不“拥有”其指向的对象，因此无法转移所有权。当使用如
Song* s2 = std::move(s1); 的代码时，你只是将 s1 的地址复制到 s2，s1 并没有改变，也没有失去对对象的所有权。
相反，若你希望在移动操作过程中转移资源所有权，应该使用具有移动语义的智能指针，比如 std::unique_ptr 或 
std::shared_ptr.

例如，以下代码使用 std::unique_ptr 转移所有权:
std::unique_ptr<Song> s1 = std::make_unique<Song>(L"Jay", L"star");
std::unique_ptr<Song> s2 = std::move(s1);  // s1 的所有权被移动到 s2

在这个例子中，std::unique_ptr 是一个类，它为移动语义定义了移动构造函数和移动赋值运算符。在 std::move(s1) 
执行后，所有权从 s1 转移到 s2，并且 s1 不再拥有该对象。

*/

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

	Song* s1 = new Song(L"Jay", L"star");
	Song* s4 = std::move(s1); //不调用移动构造，详解见上述解析
	Song s2(std::move(*s1)); //调用移动构造
	Song s3 = std::move(s2); //调用移动构造

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

void ProcessLargeObject(const LargeObject& lo)
{
	int a = 1;
}
