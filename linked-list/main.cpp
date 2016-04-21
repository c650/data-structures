#include <iostream>
//#include "../debug.cpp"
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

	int a = mylist.del(3);

	mylist.print();
	return 0;
}