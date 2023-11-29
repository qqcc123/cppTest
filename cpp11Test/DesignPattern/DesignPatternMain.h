#pragma once

#include "AdapterPattern.h"
#include "ObserverPattern.h"
#include <memory>

namespace DesignPattern {

	void testAdapter()
	{
		std::shared_ptr<Target> targetObj = std::make_shared<Target>();
		clientCode(targetObj.get());

		std::shared_ptr<Adaptee> adapteeObj(new Adaptee);
		std::shared_ptr<Target> adapterObj = std::make_shared<Adapter>(adapteeObj.get());
		clientCode(adapterObj.get());
	}

	void testObserver()
	{
		std::shared_ptr<Subject> subject = std::make_shared<Subject>();
		std::shared_ptr<Observer> observer1(new Observer(subject.get()));
		std::shared_ptr<Observer> observer2(new Observer(subject.get()));
		std::shared_ptr<Observer> observer3(new Observer(subject.get()));
		std::shared_ptr<Observer> observer4;
		std::shared_ptr<Observer> observer5;

		subject->changeSubject("Hello World! :D");
		observer3->removeMeFromList();

		subject->changeSubject("The weather is hot today! :p");
		observer4 = std::make_shared<Observer>(subject.get());

		observer2->removeMeFromList();
		observer5 = std::make_shared<Observer>(subject.get());

		subject->changeSubject("My new car is great! ;)");
		observer5->removeMeFromList();

		observer4->removeMeFromList();
		observer1->removeMeFromList();
	}

	void start()
	{
		//testAdapter();

		testObserver();
	}
}