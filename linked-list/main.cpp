#include <iostream>
#include "./list.hpp"

template <class InputIt>
static void print_out(InputIt first , InputIt last) {
	for (InputIt it = first ; it != last ; ++it)
		std::cout << *it << ' ';
	std::cout << '\n';
}

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
	print_out(test.begin(), test.end());
	std::cout << '\n';

	test.push_back(1111);
	test.push_front(195);
	print_out(test.begin() , test.end());

	auto test2 = test;
	auto test3 = std::move(test2);

	Charles::List<char> test4({'c','h','a','r','l','e','s'});
	print_out(test4.begin(), test4.end());

	Charles::List<char> test5(test4.begin(), test4.end());
	std::cout << test5.size() << '\n';

	char tmp = 'h';
	test5.insert(test5.end(), tmp);
	print_out(test5.begin(), test5.end());
	std::cout << test5.size() << '\n';

	test5.insert(test5.begin() , tmp);
	print_out(test5.begin() , test5.end());
	std::cout << test5.size() << '\n';

	test5.insert(test5.begin() + test5.size() / 2 , 3 , tmp);
	print_out(test5.begin() , test5.end());
	std::cout << test5.size() << '\n';

	test5.erase(test5.begin());
	print_out(test5.begin() , test5.end());
	std::cout << test5.size() << '\n';

	test5.resize(5);
	print_out(test5.begin() , test5.end());
	std::cout << test5.size() << '\n';

	test5.swap(test4);

	print_out(test5.begin() , test5.end());
	std::cout << test5.size() << '\n';

	return 0;
}
