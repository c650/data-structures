#include <iostream>

// custom files
#include "./node.h"
#include "./node.cpp"
#include "./list.h"
#include "./list.cpp"
// end inclusions

void debug(const std::string& s) {
	std::cout << "DEBUG: " << s << std::endl;
}

int main() {
	
	// make new list here
	List<int> mylist;

	for(int i = 0; i < 4; i++) {
		mylist.append(i);
	}

	return 0;
}