#include "DyWeakPtr.h"

void DyWeakPtr::RunTest()
{
    vector<shared_ptr<Controller>> v
    {
        make_shared<Controller>(0),
        make_shared<Controller>(1),
        make_shared<Controller>(2),
        make_shared<Controller>(3),
        make_shared<Controller>(4),
    };

    for (int i = 0; i < v.size(); ++i)
    {
        for_each(v.begin(), v.end(), [&v, i](shared_ptr<Controller> p) {
            if (p->Num != i)
            {
                v[i]->others.push_back(weak_ptr<Controller>(p));
                wcout << L"push_back to v[" << i << "]: " << p->Num << endl;
            }
        });
    }

    for_each(v.begin(), v.end(), [](shared_ptr<Controller>& p) {
        wcout << L"use_count = " << p.use_count() << endl;
        p->CheckStatuses();
    });
}

Controller::Controller(int i) : Num(i), Status(L"On")
{
    wcout << L"Creating Controller" << Num << endl;
}

Controller::~Controller()
{
    wcout << L"Destroying Controller" << Num << endl;
}

// Demonstrates how to test whether the
// pointed-to memory still exists or not.
void Controller::CheckStatuses() const
{
    for_each(others.begin(), others.end(), [](weak_ptr<Controller> wp) 
    {
        //检测当前weak_ptr指向的shared_ptr资源是否被释放
        auto p = wp.lock();
        if (p)
        {
            wcout << L"Status of " << p->Num << " = " << p->Status << endl;
        }
        else
        {
            wcout << L"Null object" << endl;
        }
    });
}