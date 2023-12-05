//Example Usage of std::prev iterator usage
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
	auto iterator = myListOfStrings.end();

	//taking in a number use in prev
	int numOfPositionToMovePrev;
	cout << "insert number of positions to move iterator in the list: ";
	cin >> numOfPositionToMovePrev;
	cout << endl;

	//as long as the num of positions to move isn't bigger than the list or less than 0 then 
	if (numOfPositionToMovePrev < myListOfStrings.size() && numOfPositionToMovePrev > 0)
	{
		//going from iterator and moving numOfPositions and returning it into prevIterator (must store iterator, prev does not acutally move input iterator)
		auto prevIterator = std::prev(iterator, numOfPositionToMovePrev);
		cout << "Value of prev iterator: " << *prevIterator << endl;
		//exit program
		return 0;
	}
	else {
		cout << "Position specified is out of range" << endl;
		//exit program
		return 0;
	}
}