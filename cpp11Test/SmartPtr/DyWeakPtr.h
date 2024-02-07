#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class DyWeakPtr
{
public:
    DyWeakPtr() = default;

    ~DyWeakPtr() = default;

    void RunTest();
};

class Controller
{
public:
    explicit Controller(int i);

    ~Controller();

    void CheckStatuses() const;

    int Num;

    wstring Status;

    vector<weak_ptr<Controller>> others;
};
