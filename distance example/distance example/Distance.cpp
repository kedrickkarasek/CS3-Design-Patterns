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

int main(){
	//creating integer list
	list<int> intList = { 1, 2, 3, 4, 5, 6, 7 };

	//two iterators one at the beginninng and one at the end of the list
	auto iteratorBegin = intList.begin();
	auto iteratorEnd = intList.end();

	//distance returns an int which is the number between the two iterators
	int distance = std::distance(iteratorBegin, iteratorEnd);

	//printing distance
	cout << "The distance between the beginning and the end of the list is: " << distance << endl;
}