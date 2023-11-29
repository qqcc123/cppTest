#pragma once

#include <iostream>

class Target {
public:
	Target() = default;

	virtual ~Target()
	{
		std::cout << "destruct Target" << std::endl;
	}

	virtual std::string request() const
	{
		std::cout << "default: default request" << std::endl;
		return "default request";
	}
};

class Adaptee {
public:
	Adaptee() = default;

	~Adaptee()
	{
		std::cout << "destruct Adaptee" << std::endl;
	}

	std::string transffer() const
	{
		return "transffer request";
	}
};

class Adapter : public Target
{
public:
	Adapter(Adaptee* adaptee) : m_adaptee(adaptee) {};

	~Adapter()
	{
		std::cout << "destruct Adapter" << std::endl;
	}

	std::string request() const override
	{
		std::string specificRequest = m_adaptee->transffer();
		std::reverse(specificRequest.begin(), specificRequest.end());
		std::cout << "after transffer: " << specificRequest << std::endl;
		return specificRequest;
	}

private:
	Adaptee* m_adaptee = nullptr;
};

void clientCode(Target* target)
{
	target->request();
}