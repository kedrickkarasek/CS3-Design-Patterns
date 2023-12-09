//Example Composite Design Pattern
//Created by Kedrick Karasek

/*
*************************Important Information about Composite Design Pattern*******************************************************************
1. Motivation: grphics editor allows figures out of primitive items (lines, circles, points) then more complex figures out of simpler ones
2. Composite Pattern: abstract class that represents bboth primitives and their containers
	1. allows clients to treat them uniformly
	2. encodes traversal of composition hierarchy
3. Containers: allows clients to treat them uniformly, and encodes traversal of composition hierarchy
4.Terms:
	1. Component: abstract uniform interface class for both collections and primitive items
	2. Leaf: concrete primitive class
	3. Composite: collection that possibly consists of leaves or other composites, implements interface and access (traversal) to children/parents
5. This is frequently implemented with visitor where composite implements traversal while visitor implements processing of individual elements
*******************************************************************************************************************************************************
*/

#include <iostream>
#include <string>

using std::cout; using std::endl; using std::cin;
using std::string;

//Abstract Component
class Expression {
public:
	//Abstract Methods
	virtual int evaluate() = 0;
	virtual string print() = 0;

	//Abstract Destructor
	virtual ~Expression() {}
};

//Concrete Component
//This is a Leaf
//Primitive  Class
class Number : public Expression {
public:
	//Default Constructor
	Number(int value) : value_(value) {}
	int evaluate() override { return value_; }
	string print() override { return std::to_string(value_); }
private:
	int value_;
};

//Concrete Component 
//Composite Class
class Add : public Expression {
public:
	//Defualt Constructor
	Add(Expression* left, Expression* right) : left_(left), right_(right) {}

	//Concrete Methods
	int evaluate() override {
		//This adds the left and right
		return left_->evaluate() + right_->evaluate();
	}
	string print() override {
		//prints out the operation
		return '[' + left_->print() + '+' + right_->print() + ']';
	}
private:
	Expression* left_;
	Expression* right_;
};

//Concrete Component 
//Composite Class
class Subtract : public Expression {
public:
	//Defualt Constructor
	Subtract(Expression* left, Expression* right) : left_(left), right_(right) {}

	//Concrete Methods
	int evaluate() override {
		//This subtracts the left and right
		return left_->evaluate() - right_->evaluate();
	}
	string print() override {
		//prints out the operation
		return '[' + left_->print() + '-' + right_->print() + ']';
	}
private:
	Expression* left_;
	Expression* right_;
};

//Concrete Component 
//Composite Class
class Multiply : public Expression {
public:
	//Defualt Constructor
	Multiply(Expression* left, Expression* right) : left_(left), right_(right) {}

	//Concrete Methods
	int evaluate() override {
		//This adds the left and right
		return left_->evaluate() * right_->evaluate();
	}
	string print() override {
		//prints out the operation
		return '[' + left_->print() + '*' + right_->print() + ']';
	}
private:
	Expression* left_;
	Expression* right_;
};

//Concrete Component 
//Composite Class
class Divide : public Expression {
public:
	//Defualt Constructor
	Divide(Expression* left, Expression* right) : left_(left), right_(right) {}

	//Concrete Methods
	int evaluate() override {
		//This adds the left and right
		return left_->evaluate() / right_->evaluate();
	}
	string print() override {
		//prints out the operation
		return '[' + left_->print() + '/' + right_->print() + ']';
	}
private:
	Expression* left_;
	Expression* right_;
};

int main() {
	Expression* const55 = new Number(55);
	cout << const55->print() << " = " << const55->evaluate() << endl;

	Expression* exp1 = new Add(const55, new Number(25));
	cout << exp1->print() << " = " << exp1->evaluate() << endl;

	Expression* const42 = new Number(42);

	Expression* exp2 = new Subtract(exp1, new Add(const42, new Number(9)));
	cout << exp2->print() << " = " << exp2->evaluate() << endl;

	Expression* exp3 = new Divide(exp1, exp2);
	cout << exp3->print() << " = " << exp3->evaluate() << endl;

	cout << "Enter first factor: ";
	int factor1; cin >> factor1;
	cout << "Enter second factor ";
	int factor2; cin >> factor2;

	Expression* product = new Divide(new Number(factor1), new Number(factor2));
	cout << product->print() << " = " << product->evaluate() << endl;
}