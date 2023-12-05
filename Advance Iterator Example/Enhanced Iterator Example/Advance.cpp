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
	auto iteratorToAdvance = myListOfStrings.begin();

	//printing out current value of iterators position (should print "The")
	cout << "Current Value of iterator before the advance: " << *iteratorToAdvance << endl;

	//taking in a number to advance that many positions
	int numOfPositionToAdvance;
	cout << "insert number of positions to move iterator in the list: ";
	cin >> numOfPositionToAdvance;
	cout << endl;

	//as long as the num of positions to move isn't bigger than the list or less than 0 then 
	if (numOfPositionToAdvance < myListOfStrings.size() && numOfPositionToAdvance > 0)
	{
		//move iteratorToAdvance numOfPositionToAdvance
		std::advance(iteratorToAdvance, numOfPositionToAdvance);
		//print out what the new position holds
		cout << "New Value of iterator after the advance: " << *iteratorToAdvance << endl;
		//exit program
		return 0;
	}
	else {
		cout << "Position specified is out of range" << endl;
		//exit program
		return 0;
	}
}