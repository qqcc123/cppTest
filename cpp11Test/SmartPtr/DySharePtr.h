#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class testItem {
public:
    testItem(int a, const char* data)
    {
        m_a = a;
        int len = std::strlen(data);
        m_p = new char[len + 1];
        std::strcpy(m_p, data);
        m_p[len] = '\0';

        std::cout << "default construct" << std::endl;
    }

    testItem(const testItem& item)
    {
        m_a = item.m_a;
        int len = std::strlen(item.m_p);
        m_p = new char[len + 1];
        std::strcpy(m_p, item.m_p);
        m_p[len] = '\0';

        std::cout << "copy destruct" << std::endl;
    }

    testItem(testItem&& item)
    {
        m_a = item.m_a;
        m_p = item.m_p;
        item.m_p = nullptr;

        std::cout << "move destruct" << std::endl;
    }

    ~testItem()
    {
        std::cout << "destruct testItem" << std::endl;
    }

private:
    int m_a = 0;

    char* m_p = nullptr;
};

//struct MediaAsset
//{
//    virtual ~MediaAsset() = default; // make it polymorphic
//};

//struct Song : public MediaAsset
//{
//    std::wstring artist;
//    std::wstring title;
//    Song(const std::wstring& artist_, const std::wstring& title_) :
//        artist{ artist_ }, title{ title_ } {}
//};
//
//struct Photo : public MediaAsset
//{
//    std::wstring date;
//    std::wstring location;
//    std::wstring subject;
//    Photo(
//        const std::wstring& date_,
//        const std::wstring& location_,
//        const std::wstring& subject_) :
//        date{ date_ }, location{ location_ }, subject{ subject_ } {}
//};

class DySharePtr
{
public:
    DySharePtr();

    ~DySharePtr();

    void init();

    void getItem();

private:
    std::vector<std::shared_ptr<testItem>> m_itemVec;
};

