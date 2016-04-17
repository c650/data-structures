#include <iostream>

template <class T>
List<T>::~List() {
	delete root; // root is a node<T>*,
	// whose destructor deletes whatever the node points to
}

template <class T>
T& List<T>::operator[](size_t idx) {
	if (idx >= len) {
		throw std::invalid_argument("operator[] in List out of bounds");
	}
	node<T>* ptr = root;
	size_t i = 0;

	while(i < idx && ptr != nullptr) {
		ptr = ptr->next;
		i++;
	}

	return ptr->d();
}

template <class T>
void List<T>::append(T _data) {
	node<T>* h = root;

	while(h->next != nullptr) {
		h = h->next;
	}
	
	h->next = new node<T>(_data);

	len++;
}

template <class T>
T List<T>::pop() {
	node<T>* h = root;

	while(h->next != nullptr) {
		h = h->next;
	}
	T tmp = std::move( h->d() );

	delete h;

	return tmp;
}

template <class T>
size_t List<T>::size() {
	return len;
}

template <class T>
std::ostream& List<T>::operator<<(std::ostream& out) {
	node<T>* h = root;

	out << "| ";

	while(h != nullptr) {
		out << h->d() << " ";
	}

	out << "|\n";

	return out;
}