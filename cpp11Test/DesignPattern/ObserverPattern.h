#pragma once

#include <iostream>
#include <list>

class IObserver
{
public:
	IObserver() = default;

	virtual ~IObserver() 
	{
		std::cout << "Goodbye, I was the IObserver \"" << "\".\n";
	};

	virtual void update(const std::string& msg) = 0;
};

class Isubject
{
public:
	Isubject() = default;

	virtual ~Isubject() 
	{
		std::cout << "Goodbye, I was the Isubject.\n";
	};

	virtual void attach(IObserver* observer) = 0;

	virtual void detach(IObserver* observer) = 0;

	virtual void notify() = 0;
};

class Observer : public IObserver
{
public:
	Observer(Isubject* sub) : m_subject(sub)
	{
		m_subject->attach(this);
		m_static_ob_number++;
		m_number = m_static_ob_number;

		std::cout << "Hi, I'm the Observer \"" << m_number << "\".\n";
	}

	~Observer()
	{
		std::cout << "Goodbye, I was the Observer \"" << m_number << "\".\n";
	}

	void removeMeFromList()
	{
		m_subject->detach(this);
		
		std::cout << "Observer \"" << m_number << "\" removed from the list.\n";
	}

	void update(const std::string& msg)
	{
		std::cout << "Observer \"" << m_number << "\": a new message is available --> " << msg << "\n";
	}

private:
	Isubject* m_subject = nullptr;

	static int m_static_ob_number;

	int m_number = 0;
};

int Observer::m_static_ob_number = 0;

class Subject : public Isubject
{
public:
	Subject() = default;

	~Subject()
	{
		std::cout << "Goodbye, I was the Subject.\n";
	}

	void attach(IObserver* observer)
	{
		m_ob_list.emplace_back(observer);
	}

	void detach(IObserver* observer)
	{
		m_ob_list.remove(observer);
	}

	void notify()
	{
		for (auto &it : m_ob_list)
		{
			it->update(m_subMessage);
		}
	}

	void changeSubject(const std::string& msg)
	{
		m_subMessage = msg;
		notify();
	}

private:
	std::list<IObserver*> m_ob_list;

	std::string m_subMessage;
};