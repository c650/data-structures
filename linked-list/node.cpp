#include <iostream>

// constructor is in node.h

template <class T>
node<T>::~node() {
	if (next != nullptr) {
		delete next;
	}

	//debug("node<T>::~node was called!");
}

template <class T>
T& node<T>::d() {
	return data;
}

template <class T>
void node<T>::d(T _data) {
	data = _data;
}

template<class T>
node<T>* node<T>::n() {
	return next;
}

template <class T>
void node<T>::print() {
	std::cout << data << "\n";
}
