#include "DySharePtr.h"

/*
make_shared 异常安全。 它使用同一调用为控制块和资源分配内存，这会减少构造开销。 如果不使用 make_shared，
则必须先使用显式 new 表达式来创建对象，然后才能将其传递到 shared_ptr 构造函数。

实际上，对shared_ptr线程安全的描述有一定的误解，也容易被误解。让我来详细解释一下。首先，shared_ptr本身只保证
其引用计数器的操作是原子性的、线程安全的。这意味着，你可以在不同的线程中生成多个shared_ptr实例，它们都指向同
一块内存，而且这些shared_ptr实例的创建和销毁不会导致引用计数器的混乱。

然而，当多个线程都需要更新一个共享的shared_ptr实例时，情况就变得复杂了。这种情况下，虽然每个单独的shared_ptr
引用计数的更新是线程安全的，但当shared_ptr实例自身被多个线程同时写入时，并不能保证线程安全。例如，如果线程1读取
shared_ptr中存储的指针，而线程2同时改变了shared_ptr中的指针，这可能会导致线程1读到一个已经被释放的对象，这显然就
不是线程安全的了。因此，正确的描述应该是，shared_ptr的引用计数操作是线程安全的，但shared_ptr实例本身的读写操作在
多线程环境下并不是线程安全的，还是需要附加同步机制，如互斥锁或者原子操作等。

*/

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

	//可测试，item1不需要在声明的时候设置为nullptr
	std::shared_ptr<testItem> item1 = nullptr;
	std::shared_ptr<testItem> item2(nullptr);

	
}

void DySharePtr::getItem()
{
	//先调用testItem的构造函数，再调用shared_ptr的构造函数
	std::shared_ptr<testItem> sp2(new testItem(2, "123"));

	//直接调用shared_ptr的构造函数，并完成testItem构造相关的工作
	std::shared_ptr<testItem> item = std::make_shared<testItem>(2, "123");

	//移动构造会在智能指针内部将指针成员对象的值赋值，然后将亡值的指针设置为nullptr，不会调用testItem的移动构造
	m_itemVec.emplace_back(std::move(item)); 
	m_itemVec.emplace_back(std::make_shared<testItem>(3, "456"));
}