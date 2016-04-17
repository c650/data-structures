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

	std::cout << "mylist.size() = " << mylist.size() << "\n";

	std::cout << "popping... popped: " << mylist.pop() << "\n";

	std::cout << "now reprint:\n";

	mylist.print();

	std::cout << "mylist[1] = "<< mylist[1] << "\n";

	return 0;
}