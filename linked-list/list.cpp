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
	if (root == nullptr) {
		root = new node<T>(_data);
		debug("root was nullptr, so data inserted there");
		len++;
		return;
	}

	node<T>* h = root;
	debug("root node stored in h");

	while(h->next != nullptr) {
		h = h->next;
	}
	debug("got to end of linked list");
	
	h->next = new node<T>(_data);
	debug("new node has been made");

	len++;
}

template <class T>
T List<T>::pop() {
	if (root == nullptr) {
		throw std::out_of_range("ERROR: root is nullptr, cannot pop()");
	}
	node<T>* h = root;

	while(h->next->next != nullptr) {
		h = h->next;
	}
	T tmp = std::move( h->next->d() );

	delete h->next;

	h->next = nullptr;

	return tmp;
}

template <class T>
size_t List<T>::size() {
	return len;
}

template <class T>
void List<T>::print() {
	node<T>* h = root;

    std::cout << "| ";

    while(h != nullptr) {
      std::cout << h->d() << " ";

      h = h->next;
    }

    std::cout << "|\n";
}