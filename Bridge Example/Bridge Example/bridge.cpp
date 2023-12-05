//Example Bridge Design Pattern
//Created by Kedrick Karasek

/*
*************************Important Information about Bridge Design Pattern*******************************************************************
1. Delegation: delegator object relying upon another delegatee object to provide a specifified set of functionality                         *
   - Commonly implemented using a pointer from delegator to delegatee and then invoking a method of delegatee within delegator method       *
   - Delegator: is the high-level interface or abstraction that the clients interact with                                                   *
   - Delegatee: is the lower-level component that provides the actual implementation for the abstraction                                    *
2. Bridge Design Pattern: decouples interface hierarchy from implementation hierarchy through delegation (pointer)                          *
3. Handle: is the abstract interface class                                                                                                  *
4. Body: is the abstract implementor class                                                                                                  *
5. Bridge Design Pattern is a Structural Design Pattern                                                                                     *
6. The purpose of the Bridge Design Pattern is to seperate abstraction from implemention, allowing both to evolve independently.            *
	- want to avoid a permanent binding between an abstraction and its implementation                                                       *
7. Bridge uses delegation by separating the abstraction from its implementation.                                                            *
	- It allows the abstraction to delegate its responsibilities to the implementation                                                      *
*********************************************************************************************************************************************
*/

#include <iostream>

// Abstract Body
class Fill {
public:
	//Default Constructor
	Fill(char fillChar) : fillChar_(fillChar) {}

	//Abstract methods
	virtual char getBorder() = 0;
	virtual char getInternal() = 0;

	//Destructor
	virtual ~Fill(){}

protected:
	char fillChar_;

};

// Concrete Body
class Hollow : public Fill {
public: 
	//Default Constructor
	Hollow(char fillChar) : Fill(fillChar) {}

	//Concrete Methods
	char getBorder() override { return fillChar_; }
	char getInternal() override { return fillChar_; }

	//Destructor
	~Hollow() override {}
};

// Concrete Body
class Filled : public Fill {
public:
	//Default Constructor
	Filled(char fillChar) : Fill(fillChar) {}

	//Concrete Methods
	char getBorder() override { return fillChar_; }
	char getInternal() override { return fillChar_; }

	//Destructor
	~Filled() override {}
};

// Abstract Handle
class Figure {
public:
	//Default Constructor
	Figure(int size, Fill* fill) : size_(size), fill_(fill) {}

	//Abstract Method
	virtual void draw() = 0;

	//Destructor
	virtual ~Figure() {}

protected:
	int size_;
	Fill* fill_;
};

//Concrete Handle
class Square : public Figure {
public:
	//Default Constructor
	Square(int size, Fill* fill) : Figure(size, fill) {}

	//Concrete Method
	void draw() override {
		for (int i = 0; i < size_; ++i) {
			for (int j = 0; j < size_; ++j) {
				if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1) {
					std::cout << fill_->getBorder();
				}
				else {
					std::cout << fill_->getInternal();
				}
			}
			std::cout << std::endl;
		}
	}
};

int main() {
	// ask user for figure parameters
	std::cout << "Enter fill character: ";
	char fchar; std::cin >> fchar;
	std::cout << "Filled or hollow? [f/h] ";
	char ifFilled; std::cin >> ifFilled;
	std::cout << "Enter size: "; int size; std::cin >> size;


	if (ifFilled == 'f') {
		Figure* userBox = new Square(size, new Filled(fchar));
		userBox->draw();
		std::cout << std::endl;
	}
	else {
		Figure* userBox = new Square(size, new Hollow(fchar));
		userBox->draw();
		std::cout << std::endl;
	}
}