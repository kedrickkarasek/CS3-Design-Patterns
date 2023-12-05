/*
Here is some useful knowledge about a Singleton:
1. Static featurs are allocated per class rather than per object
2. Static features are shared between objects of the saame class
3. We can specify behavior at program shutdown through using atexit()
4. Singleton is a creational pattern meaning it creates objects for the client
5. Singleton Design Pattern Explaination:
	1.Singleton ensures that there is a single instance of a *CLASS* in the program
		Requirements for singleton:
			1. The Singleton must able to be accessed globally meaning that more than a single function/method should be able to manipulate the Singleton
			2. Should have a function that if the Singleton does not exist it should create one on the first invokation (This is called lazy instantiation)
				2.5. If the Singleton does exist that the function shoul return a reference/pointer to the instance.
			3. The should deallocate the resources on termination of the program
*/

// Kedrick Karasek
// Meyers Singleton Practice Example
// 11/27/23
#include <iostream>
#include <vector>

using std::cout; using std::endl;
using std::vector; 
using std::string;

class MeyersSingleton 
{
public:
	//Required Instance function for Singleton Pattern
	static MeyersSingleton& Instance() 
	{ 
		static MeyersSingleton meyersSingleton;
		return meyersSingleton;
	}

	//Destructor
	~MeyersSingleton() 
	{
		//Infoming User Destructor Was Called
		cout << "Destructor was called" << endl;
		//Clearing The Vector
		payload_.clear(); 
		//Range based For Looping throught the hopfully cleared vector and printing nothing
		print();
	}

	//Some functions to go along with our Singleton (NOT REQUIRED)
	void addString(string inputString)
	{
		payload_.push_back(inputString);
	}

	void print() {
		for (const auto& individualElement : payload_)
		{
			cout << individualElement << endl;
		}
		cout << "All Elements are printed still in the vector are printed above." << endl;
	}

private:
	MeyersSingleton() {} //Private Default Constructor
	MeyersSingleton(const MeyersSingleton&) {} //Private Copy Constructor
	MeyersSingleton& operator=(const MeyersSingleton&) {} //Private Operator = Assignment Overloading

	vector<string> payload_; // This is the Payload
};

//Singleton Example Usage
int main() {
	//Populating Payload_
	MeyersSingleton::Instance().addString("Doesn't This Class Suck?");
	MeyersSingleton::Instance().addString("Yeah Man, This Class Does Suck.");
	MeyersSingleton::Instance().addString("What Are We Gonna Do?");
	MeyersSingleton::Instance().addString("Go Fuck Ourselves Am I Right?");
	MeyersSingleton::Instance().addString("Truth");
	
	//Printing Payload_
	MeyersSingleton::Instance().print();
	
	//Does Not create a copy, v is the same as if we had a d
	MeyersSingleton& v = MeyersSingleton::Instance();
	v.addString("Go Back To The Barnyard Buddy!");
	v.print();

	//Proving point about no copy
	MeyersSingleton& d = MeyersSingleton::Instance();
	d.addString("No Way!");
	d.print();

	//printing v again after creating d (prints the same as d.print even though we didn't purposly change v)
	v.print();
}