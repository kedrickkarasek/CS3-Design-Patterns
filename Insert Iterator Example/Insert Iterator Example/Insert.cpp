//Example Usage of std::prev iterator usage
//Created By: Kedrick Karasek

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>


using std::iostream;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::copy;
using std::copy_if;

int main() {
	//vector of integers
	vector<int> intVector = { 1,2,3,4,5,6,7 };

	//vector to insert elements into
	vector<int> targetVector;

	//creating insert iterator 
	std::insert_iterator<vector<int>> insertIterator(targetVector, targetVector.begin());

	//using copy to insert elements from intVector to targetVector
	copy(intVector.begin(), intVector.end(), insertIterator);

	//printing target vector after copy
	cout << "target Vector Values: ";
	for (const auto& element: targetVector) {
		cout << element << ", ";
	}
	cout << endl;

	//clearing target vector for copy_if example
	targetVector.clear();

	//copy if only works with back isnerter
	copy_if(intVector.begin(), intVector.end(), std::back_inserter(targetVector), [](int num) {return num % 2 == 0; });

	cout << "target Vector Values: ";
	for (const auto& element : targetVector) {
		cout << element << ", ";
	}
	cout << endl;

	return 0;
}