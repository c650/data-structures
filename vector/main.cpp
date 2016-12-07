#include <iostream>
#include "./vector.hpp"

static void qprint(bool a) {
	std::cout << a << " ";
}

int main() {

	Charles::Vector<int> test;
	test.push_back(100);
	std::cout << test[0] << std::endl;
	std::cout << test.max_size() << std::endl;

	Charles::Vector<int> test2(7);
	for (size_t i = 0; i < test2.size() ; i++) {
		std::cout << test2[i] << " ";
		test2[i] = 10;
	}
	std::cout << std::endl;

	std::cout << "And now with .each:\n";
	test2.each([](const int& x){
		std::cout << x << " ";
	});
	std::cout << std::endl;

	std::cout << "And let's double with map:\n";
	Charles::Vector<int> test3 = test2.map([](int& x){
		x *= 2;
	});
	test3.each([](const int& x){
		std::cout << x << " ";
	});
	std::cout << std::endl;

	qprint(test2 < test3);
	qprint(test2 > test3);
	qprint(test2 == test3);

	std::cout << test2.pop_back() << "pb\n"
				<< test2.capacity() << "cap\n";

	std::cout << test2.size() << "size\n";

	for (auto it = test2.begin(); it != test2.end(); it++) {
		*it *= 2;
		std::cout << *it << " ";
	}
	std::cout << "\n";

	test2.insert(test2.begin(), 7);
	for (auto it = test2.begin(); it != test2.end(); it++) {
		*it *= 2;
		std::cout << *it << " ";
	}
	std::cout << "\n";

	Charles::Vector<int> test4 = {1,2,3,4};
	test4.each([](int a){
		std::cout << a << " ";
	});
	std::cout << "\n";

	return 0;
}
