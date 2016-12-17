#include <iostream>
#include "./list.hpp"

int main(void) {

	Charles::List<int> test;
	test.push_back(11);
	std::cout << test.back();
	std::cout << '\n' << test.front();

	test.push_back(15);
	std::cout << '\n' << test.back();
	std::cout << '\n' << test.front();

	test.push_front(178);
	std::cout << '\n' << test.back();
	std::cout << '\n' << test.front();

	std::cout << '\n' << test.pop_back();
	std::cout << '\n' << test.back() << '\n';

	std::cout << (*(test.begin()) == test.front()) << '\n';
	for (auto it = test.begin() ; it != test.end() ; ++it)
		std::cout << *it << " ";
	std::cout << '\n';

	test.push_back(1111);
	test.push_front(195);
	for (auto it = test.begin() ; it != test.end() ; ++it)
		std::cout << *it << " ";
	std::cout << '\n';

	auto test2 = test;
	auto test3 = std::move(test2);

	Charles::List<char> test4({'c','h','a','r','l','e','s'});
	for (auto it = test4.begin() ; it != test4.end() ; ++it)
		std::cout << *it << " ";
	std::cout << '\n';

	Charles::List<char> test5(test4.begin(), test4.end());
	for (auto it = test5.begin() ; it != test5.end() ; ++it)
		std::cout << *it << " ";
	std::cout << '\n';

	char tmp = 'h';
	test5.insert(test5.end(), tmp);
	for (auto it = test5.begin() ; it != test5.end() ; ++it)
		std::cout << *it << " ";
	std::cout << '\n';


	return 0;
}
