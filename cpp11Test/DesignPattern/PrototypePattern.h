#pragma once

#include <iostream>
#include <Windows.h>
#include <unordered_map>

using std::string;

enum Type {
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

class Prototype 
{
public:
    Prototype() = default;

    Prototype(string prototype_name) : prototype_name_(prototype_name) {};

    virtual ~Prototype() = default;

    virtual Prototype* Clone() const = 0;

    virtual void Method(float prototype_field) 
    {
        this->prototype_field_ = prototype_field;
        std::cout << "Call Method from " << prototype_name_ << " with field : " << prototype_field << std::endl;
    }

protected:
    string prototype_name_;

    float prototype_field_;
};

class ConcretePrototype1 : public Prototype 
{
public:
    ConcretePrototype1(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field) 
    {

    }

    ConcretePrototype1(const ConcretePrototype1& t)
    {

    }

    Prototype* Clone() const override {
        return new ConcretePrototype1(*this);
    }

private:
    float concrete_prototype_field1_;

};

class ConcretePrototype2 : public Prototype 
{
public:
    ConcretePrototype2(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field) 
    {

    }

    //ConcretePrototype2(const ConcretePrototype2& t)
    //{

    //}

    Prototype* Clone() const override 
    {
        return new ConcretePrototype2(*this);
    }

private:
    float concrete_prototype_field2_;
};


class PrototypeFactory 
{
public:
    PrototypeFactory() 
    {
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2 ", 60.f);
    }

    ~PrototypeFactory() 
    {
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
    }

    Prototype* CreatePrototype(Type type) 
    {
        return prototypes_[type]->Clone();
    }

private:
    std::unordered_map<Type, Prototype*, std::hash<int>> prototypes_;
};

void Client(PrototypeFactory& prototype_factory) 
{
    std::cout << "Let's create a Prototype 1\n";

    Prototype* prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90);
    delete prototype;

    std::cout << "\n";

    std::cout << "Let's create a Prototype 2 \n";

    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10);

    delete prototype;
}
