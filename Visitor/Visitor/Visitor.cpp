//Example Visitor Design Pattern
//Created by Kedrick Karasek

/*
*************************Important Information about Visitor Design Pattern*******************************************************************
1.Double Dispatch: Is selection based on multiple objects, not directly supported by C++ but implemented using the Visitor Design Pattern
2.Other types of dispatch:
	1. Static Dispatch: compile time selection of which version of the polymorphic function to execute.
	2. Dynamic Dispatch: run time selection (Double Dispatch is an example of this)
		1. Single Dispatch: selection based on a single object, supported in C++ using virtual functions.
		2. Double DIspatch easier to understand: run time selection based on multiple objects
3.Visitor separates data from operations on it by defining visitor class that implements the operations and a;;pws tp easily add the operations since they are added to visitor.
4. Participants:
	1. element: has accept() method that takes visitor as argument, and calles visit() method of the visitor, element passes itself to the visit() method
	2. visitor: defines visit() with parameter corresponding to the particular concrete element
5. When accept() is invoked, its implementation is based on the type of concrete element
6. Easiest to add a new concrete visitor
*******************************************************************************************************************************************************
*/

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl;
using std::string;
using std::vector;

//Abstract Element
class CarPart {
public :
	virtual void accept(class CarPartVisitor*) = 0;
};

//Abstract Visitor
class CarPartVisitor {
public:
	virtual void visit(class Engine*) = 0;
	virtual void visit(class Transmission*) = 0;
	virtual void visit(class Wheel*) = 0;
};

//Concrete Element
class Engine : public CarPart {
public:
	void accept(CarPartVisitor* v) override{
		v->visit(this);
	}
};

//Another Concrete Element
class Transmission : public CarPart {
public:
	void accept(CarPartVisitor* v) override {
		v->visit(this);
	}
};

//Another Concrete Element
//This element is stateful
class Wheel : public CarPart {
public:
	//Default COnstructor
	Wheel(const string &place): place_(place), rotations_(0) {}
	const string& getPlace() { return place_; }
	int getRotations() const { return rotations_; }
	void rotate() { ++rotations_; }
	void accept(CarPartVisitor* v) override {
		v->visit(this);
	}
private:
	const string place_;
	int rotations_;
};

//Simple Concrete Visitor
class Inspector : public CarPartVisitor {
public:
	void visit(Engine* e) override {
		cout << "Inspector checks engine" << endl;
	}

	void visit(Transmission* t) override {
		cout << "Inspector checks Transmission" << endl;
	}

	void visit(Wheel* w) override {
		cout << "Inspector checks "
			<< w->getPlace() << " wheel"
			<< endl;
		cout << "sees # rotations: " << w->getRotations() << endl;
	}
};

//Stateful Concrete Visitor
class Operator : public CarPartVisitor {
public:
	//Default Constructor
	Operator() : ops_(0) {}

	void visit(Engine* e) override {
		cout << "Operator starts engine. So far ops: " << ++ops_ << endl;
	}

	void visit(Transmission* t) override {
		cout << "Operator shifts transimission. so far ops: " << ++ops_ << endl;
	}

	void visit(Wheel* w) override {
		w->rotate();
		cout << "Operator turns " << w->getPlace() << " wheel" << endl;
		cout << "it was turned " << w->getRotations() << " times" << endl;
		cout << "so far ops: " << ++ops_ << endl;
	}
private:
	int ops_; //This is the number of operations performed
};

int main() {
	vector<CarPart*> parts = { new Transmission, new Engine, new Wheel("back right"), new Wheel("back left") , new Wheel("front center") , new Wheel("steering") };

	vector<CarPartVisitor*> visitors = { new Operator, new Inspector };

	for (auto v : visitors) {
		for (auto e : parts) {
			e->accept(v); //method is dispatched on the basis of types of both "e" and "v"
			cout << endl;
		}
	}
}