//Example Class Adapter Design Pattern
//Created by Kedrick Karasek

/*
****************************************Important Information about Adapter Design Pattern*****************************************************
1. Public Inheritance: allows to inherit the interface: is-a relationship
2. Private Inheritance: allows to inherit implementation interface is not inherited (by default): implemented-in-terms-of relationship
3. If inheriting a private base class feature, it may be made public by using BaseClass::BaseClassFeature;
4. Multiple Class Inheritance: A class may need to inherit the interface from one class and the implementation from another.
5. Adapter design pattern is used for when you have and interface class and an implementation class with incompatible interface.
6. Adapter (Wrapper): concrete class that inherits from interface
7. Adaptee: Implementation class whose interface is modified (adapted)
8. Two approches: Class Adapter and Object Adapter
9. Class Adapter: uses multiple inheritance, adapter (publicly) iherits interface from target and (privately) implementation from adaptee
10. Object Adapter: uses delegation from adapter to adaptee, adapter uses aggregation to delegate requests to adaptee
11. The Adapter design pattern is a structural design pattern
12. The difference between this pattern and bridge is in its usage, bridge is used to build a new class hierarchy, while
		adapter is used to modify existing classes to a particular use.
*********************************************************************************************************************************************
*/

//This Example is the Class Adapter

#include <iostream>
#include <string>

using std::cout; using std::endl; 

//base interface
class Square {
public:
	virtual void draw() const = 0;
	virtual ~Square() {}
};

// Adaptee Class / Impelmentor class
class LegacyRectangle {
public:
	//Default Constructor
	LegacyRectangle(int topLeftX,
		int topLeftY,
		int bottomRightX,
		int bottomRightY) :
		topLeftX_(topLeftX),
		topLeftY_(topLeftY),
		bottomRightX_(bottomRightX),
		bottomRightY_(bottomRightY) {}

	// Regular Draw Function called oldDraw()
	void oldDraw() const {
		for (int i = 0; i < bottomRightY_; ++i) {
			for (int j = 0; j < bottomRightX_; ++j)
				if (i >= topLeftY_ && j >= topLeftX_)
					cout << '*';
				else
					cout << ' ';
			cout << endl;
		}
	}

private:
	int topLeftX_;
	int topLeftY_;
	int bottomRightX_;
	int bottomRightY_;
};

// Adapter Class
// Uses multiple inheritance to inherit interface and implementation
class SquareAdapter : public Square, private LegacyRectangle {
public:
	SquareAdapter(int size): LegacyRectangle(0, 0, size, size) {};

	void draw() const override {
		oldDraw();
	}
};

int main() {
	//Creating a square pointer that points at a new SquareAdapter of size 14 
	Square* square = new SquareAdapter(14);
	//square callign the draw method which is overriden by the adapter class and the overriden implementation calls the oldDraw() function from the LegacyRectangle
	square->draw();
}

