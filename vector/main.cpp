#include <iostream>
#include "./vector.hpp"

int main() {

	Charlie::Vector<int> test;
	test.push_back(100);
	std::cout << test[0] << std::endl;
	std::cout << test.max_size() << std::endl;

	Charlie::Vector<int> test2(7);
	for (size_t i = 0; i < test2.size() ; i++)
		std::cout << test2[i] << " ";
	std::cout << std::endl;

	return 0;
}
