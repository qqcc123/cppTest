#include "DySharePtr.h"

/*
make_shared �쳣��ȫ�� ��ʹ��ͬһ����Ϊ���ƿ����Դ�����ڴ棬�����ٹ��쿪���� �����ʹ�� make_shared��
�������ʹ����ʽ new ���ʽ����������Ȼ����ܽ��䴫�ݵ� shared_ptr ���캯����

ʵ���ϣ���shared_ptr�̰߳�ȫ��������һ������⣬Ҳ���ױ���⡣��������ϸ����һ�¡����ȣ�shared_ptr����ֻ��֤
�����ü������Ĳ�����ԭ���Եġ��̰߳�ȫ�ġ�����ζ�ţ�������ڲ�ͬ���߳������ɶ��shared_ptrʵ�������Ƕ�ָ��ͬ
һ���ڴ棬������Щshared_ptrʵ���Ĵ��������ٲ��ᵼ�����ü������Ļ��ҡ�

Ȼ����������̶߳���Ҫ����һ�������shared_ptrʵ��ʱ������ͱ�ø����ˡ���������£���Ȼÿ��������shared_ptr
���ü����ĸ������̰߳�ȫ�ģ�����shared_ptrʵ����������߳�ͬʱд��ʱ�������ܱ�֤�̰߳�ȫ�����磬����߳�1��ȡ
shared_ptr�д洢��ָ�룬���߳�2ͬʱ�ı���shared_ptr�е�ָ�룬����ܻᵼ���߳�1����һ���Ѿ����ͷŵĶ�������Ȼ��
�����̰߳�ȫ���ˡ���ˣ���ȷ������Ӧ���ǣ�shared_ptr�����ü����������̰߳�ȫ�ģ���shared_ptrʵ������Ķ�д������
���̻߳����²������̰߳�ȫ�ģ�������Ҫ����ͬ�����ƣ��绥��������ԭ�Ӳ����ȡ�

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

	//�ɲ��ԣ�item1����Ҫ��������ʱ������Ϊnullptr
	std::shared_ptr<testItem> item1 = nullptr;
	std::shared_ptr<testItem> item2(nullptr);

	
}

void DySharePtr::getItem()
{
	//�ȵ���testItem�Ĺ��캯�����ٵ���shared_ptr�Ĺ��캯��
	std::shared_ptr<testItem> sp2(new testItem(2, "123"));

	//ֱ�ӵ���shared_ptr�Ĺ��캯���������testItem������صĹ���
	std::shared_ptr<testItem> item = std::make_shared<testItem>(2, "123");

	//�ƶ������������ָ���ڲ���ָ���Ա�����ֵ��ֵ��Ȼ����ֵ��ָ������Ϊnullptr���������testItem���ƶ�����
	m_itemVec.emplace_back(std::move(item)); 
	m_itemVec.emplace_back(std::make_shared<testItem>(3, "456"));
}