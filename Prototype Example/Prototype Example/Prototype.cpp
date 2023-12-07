//Example Prototype Design Pattern
//Created by Kedrick Karasek

/*
****************************************Important Information about Prototype Design Pattern*****************************************************
1. Enumeration: a type whose values are distinct constants called enumerators
2. Type Convariance: overriding virtual function of derived class may accept or return types of derived class (valid only for pointers and references)
3. Motivation for Prototype: creating objects from scratch may be undesirable because its too expensive, little difference between newly created objects,
		need to create an object in a particular state.
4. Solution: Create a prototype object and create a copy of it with a clone() operation
5. Clone(): returns the pointer to the copy of prototype, clone() is virutal and is implemented in the derived class, the concrete clone may return covariant type
6. Abstract Prototype (prototype interface): allows clients to abstract from prototype details (prototype implementations)
7. Prototype is a creational pattern
8. If multiple prototypes - we can create a registry of prototypes, associate (factory) creation method with each: design a prototype factory:
*********************************************************************************************************************************************
*/

#include <iostream>
#include <vector>

using std::cout; using std::endl;
using std::vector;

//Base Class
class Figure {
public:
	//Default Constructor
	Figure(int size) : size_(size) {}

	//Regular Rezize Function
	void resize(int newSize) { size_ = newSize; }

	//Virtual Method Reqired for Prototype Pattern
	virtual Figure* clone() = 0;

	//Abstract Method
	virtual void draw() = 0;

	//Abstract Destructor
	virtual ~Figure() {}
protected:
	int size_;
};

//Enumerated Class Called Direction
enum class Direction {Horizontal, Vertical};

class Line : public Figure {
public:
	Line(int size, Direction dir) : dir_(dir), Figure(size) {}
	
	//clone returns base class type
	// Figure* clone() override { return new Line(size_, dir_); }

	//clone returns covariant type
	Line* clone() override { return new Line(size_, dir_); }

	//flip changes direction of line, only lines can flip not figures
	void flip() {
		dir_ = dir_ == Direction::Horizontal ?
					   Direction::Vertical :
			           Direction::Horizontal;
	}

	void draw() {
		for (int i = 0; i < size_; ++i) {
			cout << '*';
			if (dir_ == Direction::Vertical) cout << endl;;
		}
		if (dir_ == Direction::Horizontal) cout << endl;
	}

protected:
	Direction dir_;
};

int main() {
	// declares prototype line
	Line prototypeLine(4, Direction::Horizontal);
	// vector <Figure*> figures; 
	vector <Line*> figures;

	for (int i = 0; i < 5; ++i)
		figures.push_back(prototypeLine.clone());

	// flip every other one
	for (int i = 0; i < 5; ++i) {
		// use method available for lines only
		if (i % 2 == 0)
			figures[i]->flip();
	}
	// draw figures
	for (int i = 0; i < 5; ++i) figures[i]->draw();
}
