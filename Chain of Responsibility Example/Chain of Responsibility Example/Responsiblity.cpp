//Example Chain of Responsibility
//Created by Kedrick Karasek

/*
*************************Important Information about Chain of Responsibility Design Pattern*******************************************************************
1. Invoking an Ovrriden function: B* p = new B; p->A::func();
2. handlers: able to handle a request, if one handler cannot handle request, needs to pass it on to the next
3. chain of responsibility is formed at run-time and maintained by the abstract handler
4. abstract class keeps track of the chain of handlers and dispatches to next handler if previous pushes it up
5. chain of responsibility pattern is a behavioral pattern
*******************************************************************************************************************************************************
*/

#include <iostream>

using std::cout; using std::endl; using std::cin;

//abstract class
//sets up individual links in the chain of responsibility (handler)
class Administrator {
public:
	//Default Constructor
	Administrator(Administrator* successor = nullptr) : successor_(successor) {}

	//Abstract method (handler must have default implementation)
	virtual void handleRequest(int amount) {
		if (successor_ != nullptr) {
			successor_->handleRequest(amount);
		}
		else {
			cout << "nobody can handle this request" << endl;
		}
	}
private:
	Administrator* successor_;
};

//Concrete Derived class
class Teller : public Administrator {
public:
	Teller(Administrator* successor = nullptr) : Administrator(successor) {}
	void handleRequest(int amount) override {
		if (amount < 500) {
			cout << "Teller approves request for " << amount << endl;
		}
		else {
			Administrator::handleRequest(amount);
		}
	}
};

//Concrete Derived class
class Manager : public Administrator {
public:
	Manager(Administrator* successor = nullptr) : Administrator(successor) {}
	void handleRequest(int amount) override {
		if (amount < 2000) {
			cout << "Manager approves request for " << amount << endl;
		}
		else {
			Administrator::handleRequest(amount);
		}
	}
};

//Concrete Derived class
class President : public Administrator {
public:
	President(Administrator* successor = nullptr) : Administrator(successor) {}
	void handleRequest(int amount) override {
		if (amount < 10000) {
			cout << "President approves request for " << amount << endl;
		}
		else {
			Administrator::handleRequest(amount);
		}
	}
};

int main() {
	Administrator* tp = new Teller(new Manager(new President));

	int amount = 0;
	do {
		cout << "How much money would you like to withdraw? ";
		cin >> amount;
		if (amount > 0) {
			tp->handleRequest(amount);
		}
	} while (amount > 0);
}