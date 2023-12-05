//Example Usage of std::advance iterator usage
//Created By: Kedrick Karasek

#include <iostream>
#include <list>
#include <iterator>
#include <string>

using std::iostream;
using std::list;
using std::string;
using std::cout;
using std::endl;
using std::cin;

int main() {
	//List of random strings
	list<string> myListOfStrings = { "The", "Happy", "Little", "Goose", "Is", "No Longer", "Happy" };

	//iterator pointing at the first element in myListOfStrings
	auto iterator = myListOfStrings.begin();

	//printing out current value of iterators position (should print "The")
	cout << "Value held in iterator iterator: " << *iterator << endl;

	//taking in a number use in next
	int numOfPositionToMoveNext;
	cout << "insert number of positions to move iterator in the list: ";
	cin >> numOfPositionToMoveNext;
	cout << endl;

	//as long as the num of positions to move isn't bigger than the list or less than 0 then 
	if (numOfPositionToMoveNext < myListOfStrings.size() && numOfPositionToMoveNext > 0)
	{
		//going from iterator and moving numOfPositions and returning it into nextIterator (must store iterator, next does not acutally move input iterator)
		auto nextIterator = std::next(iterator, numOfPositionToMoveNext);
		cout << "New Value of iterator after the advance: " << *nextIterator << endl;
		//exit program
		return 0;
	}
	else {
		cout << "Position specified is out of range" << endl;
		//exit program
		return 0;
	}
}