#include <iostream>

// constructor is in node.h

template <class T>
node<T>::~node() {
	if (next != nullptr) {
		delete next;
	}
}

template <class T>
T& node<T>::d() {
	return data;
}

template <class T>
void node<T>::d(T _data) {
	data = _data;
}

template <class T>
std::ostream& node<T>::operator<<(std::ostream& out) {
	out << data;
	return out;
}