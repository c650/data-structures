#include <iostream>
#include "../debug.cpp"
// custom files
#include "./node.h"
#include "./node.cpp"
#include "./list.h"
#include "./list.cpp"
// end inclusions

int main() {
	
	// make new list here
	List<int> mylist;

	for(int i = 0; i < 4; i++) {
		mylist.append(i);
	}

	mylist.print();

	node<int>* s = mylist.search(6);

	if (s != nullptr) {
		std::cout << "6 was found in mylist!!!\n";
	} else {
		std::cout << "6 was not found in mylist\n";
	}

	auto a = mylist.insert(7, 9);

	if (a == nullptr) {
		std::cout <<"convention worked\n";
	}

	mylist.print();
	return 0;
}