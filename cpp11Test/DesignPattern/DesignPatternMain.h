#pragma once

#include "AdapterPattern.h"
#include "ObserverPattern.h"
#include "compositePattern.h"
#include "bridgePattern.h"
#include "PrototypePattern.h"
#include "StrategyPattern.h"
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

	void testComposite()
	{
		Component* simple = new Leaf;
		std::cout << "Client: I've got a simple component:\n";
		ClientCode(simple);
		std::cout << "\n\n";

		Component* tree = new Composite;
		Component* branch1 = new Composite;

		Component* leaf_1 = new Leaf;
		Component* leaf_2 = new Leaf;
		Component* leaf_3 = new Leaf;
		branch1->Add(leaf_1);
		branch1->Add(leaf_2);
		Component* branch2 = new Composite;
		branch2->Add(leaf_3);
		tree->Add(branch1);
		tree->Add(branch2);
		std::cout << "Client: Now I've got a composite tree:\n";
		ClientCode(tree);
		std::cout << "\n\n";

		std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
		ClientCode2(tree, simple);
		std::cout << "\n";

		delete simple;
		delete tree;
		delete branch1;
		delete branch2;
		delete leaf_1;
		delete leaf_2;
		delete leaf_3;
	}

	void testBridgePattern()
	{
		Implementation* implementation = new ConcreteImplementationA;
		Abstraction* abstraction = new Abstraction(implementation);
		ClientCode(*abstraction);
		std::cout << std::endl;
		delete implementation;
		delete abstraction;

		implementation = new ConcreteImplementationB;
		abstraction = new ExtendedAbstraction(implementation);
		ClientCode(*abstraction);

		delete implementation;
		delete abstraction;
	}

	void testProtoType()
	{
		PrototypeFactory* prototype_factory = new PrototypeFactory();
		Client(*prototype_factory);
		delete prototype_factory;
	}

	void testStrategyPattern()
	{
		Context context(std::make_unique<ConcreteStrategyA>());
		std::cout << "Client: Strategy is set to normal sorting.\n";
		context.doSomeBusinessLogic();
		std::cout << "\n";
		std::cout << "Client: Strategy is set to reverse sorting.\n";
		context.set_strategy(std::make_unique<ConcreteStrategyB>());
		context.doSomeBusinessLogic();
	}

	void start()
	{
		testAdapter();

		//testObserver();

		//testComposite();

		//testBridgePattern();

		//testProtoType();
	}
}