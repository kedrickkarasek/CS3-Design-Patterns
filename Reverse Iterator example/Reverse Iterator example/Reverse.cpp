//Example Usage of reverse_iterator iterator usage
//Created By: Kedrick Karasek

#include <iostream>
#include <vector>
#include <iterator>
#include <string>

using std::iostream;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cin;

int main() {
	vector<int> intVector = { 1,2,3,4,5 };

	//printing vector using normal iterator
	std::cout << "Vector printed in order: ";
	for (auto iterator = intVector.begin(); iterator != intVector.end(); ++iterator) {
		cout << *iterator << ", ";
	}
	cout << endl;

	//declaring reverse iterator the easy way and printing
	std::cout << "Vector printed in reverse order: ";
	for (auto reverseIterator = intVector.rbegin(); reverseIterator != intVector.rend(); ++reverseIterator) {
		cout << *reverseIterator << ", ";
	}
	cout << endl;
	
	//long way of declaring reverse iterator
	//vector<int>::reverse_iterator reverseIterator = intVector.rbegin();

	return 0;
}