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
		//debug("root was nullptr, so data inserted there");
		len++;
		return;
	}

	node<T>* h = root;
	//debug("root node stored in h");

	while(h->next != nullptr) {
		h = h->next;
	}
	//debug("got to end of linked list");
	
	h->next = new node<T>(_data);
	//debug("new node has been made");

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
node<T>* List<T>::search(const T& q) {
	node<T>* h = root;

	while(h != nullptr) {

		if (h->d() == q)
			return h;

		h = h->next;
	}

	return nullptr;
}

template <class T>
node<T>* List<T>::insert(T val, const size_t& idx) {
	node<T>* h = root;
	size_t cnt = 0;

	while(cnt < idx - 1 && h/*->next*/ != nullptr) {
		h = h->next;
		cnt++;
	}

	if (cnt == idx - 1) {
		if (h != nullptr) {

			node<T>* new_node = new node<T>(val);

			new_node->next = h->next;
			
			h->next = new_node;

			len++; // update length

			return new_node;
		} 
		// should i have else?!?!?
	}

	// WATCH THIS LINE
	return nullptr;
}

template <class T>
T List<T>::del(const size_t& idx) {
	node<T>* h = root;
	size_t cnt = 0;

	while(cnt < idx - 1 && h/*->next*/ != nullptr) {
		h = h->next;
		cnt++;
	}

	if (cnt == idx - 1) {
		if (h != nullptr) {
			
			node<T>* tmp = h->next;
			T tmp2 = tmp->d();

			h->next = tmp->next; // overlap

			tmp->next = nullptr;
			delete tmp;

			len--; // update length

			return tmp2;
		} 
		// should i have else?!?!?
	}

	return 0;
	// maybe throw range error? not sure yet...
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