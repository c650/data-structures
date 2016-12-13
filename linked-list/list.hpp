#ifndef CHARLES_LLIST_H
#define CHARLES_LLIST_H

#include <stdexcept>
#include <initializer_list>
#include <iterator>
#include <iostream>

namespace Charles {

	typedef unsigned int size_t;

	template <class T>
	class List {
	  private:
		struct node {
			T data;
			struct node *prev, *next;

			explicit node(T _data, struct node *_prev = nullptr, struct node *_next = nullptr)
				: data(_data),
				prev(_prev),
				next(_next) {}
		};

		node *first, *last;
		size_t num_elements;

		typedef T value_type;
		typedef long difference_type;
		typedef value_type& reference;
		typedef const reference const_reference;
		typedef T* pointer;
		typedef const pointer const_pointer;

		class _iterator : public std::iterator<std::random_access_iterator_tag, value_type, difference_type, pointer, reference> {
		  public:
			node *curr;

			explicit _iterator(node *_curr) : curr(_curr) {}

			_iterator& operator++() {
				curr = curr->next;
				return *this;
			}
			_iterator operator++(int) {
				node *tmp = curr;
				curr = curr->next;
				return _iterator(tmp);
			}

			_iterator& operator--() {
				curr = curr->prev;
				return *this;
			}
			_iterator operator--(int) {
				node *tmp = curr;
				curr = curr->prev;
				return _iterator(tmp);
			}

			_iterator operator+(difference_type s) {
				node *tmp = curr;
				while(curr != nullptr && s--)
					curr = curr->next;
				return _iterator(curr);
			}

			_iterator operator-(difference_type s) {
				node *tmp = curr;
				while(curr != nullptr && s--)
					curr = curr->prev;
				return _iterator(curr);
			}

			bool operator==(const _iterator& other) const {
				return this->curr == other.curr;
			}
			bool operator!=(const _iterator& other) const {
				return this->curr != other.curr;
			}

			reference operator*() const {
				return curr->data;
			}
		};

		typedef _iterator iterator;
		typedef const iterator const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef const reverse_iterator const_reverse_iterator;

	  public:

	  	List();
		explicit List( size_t count , const T& value = T());
		List(const List& other);
		List(List&& other);
		List(std::initializer_list<T> init);

		template <class InputIt>
		List(InputIt _begin, InputIt _end);

		List<T>& operator=(const List& other);
	 	List<T>& operator=(List&& other);
		List<T>& operator=(std::initializer_list<T> init);

		~List();

		void assign(size_t count, const T& value = T()); /* TODO */

		size_t size();
		bool empty();

		T& front();
		T& back();

		iterator begin();
		iterator end();
		const_iterator cbegin() const;
		const_iterator cend() const;

		void push_back(const T& elem);
		void push_front(const T& elem);

		T pop_back();
		T pop_front();

		void clear();

	private:
		/*              HELPERS              */
		void _init(size_t count, const T& value = T());
		void _destroy();

	};

	template<typename T>
	List<T>::List() : List(0) { }

	template<typename T>
	List<T>::List(size_t count , const T& value) {
		first = last = nullptr;
		num_elements = 0;
		this->_init(count, value);
	}

	template<typename T>
	List<T>::List(const List& other) : List(other.num_elements) {
		if (this == &other) return;

		for (auto it = this->begin(), o_it = other.cbegin() ; it != this->end() && o_it != other.cend(); it++, o_it++)
			*it = *o_it;
	}

	template<typename T>
	List<T>::List(List&& other) {
		this->first        = other.first;
		this->last         = other.last;
		this->num_elements = other.num_elements;

		other.first = other.last = nullptr;
		other.num_elements = 0;
	}

	template<typename T>
	List<T>::List(std::initializer_list<T> init) : List(init.size()) {
		auto init_list_it = init.begin();
		auto ll_it = this->begin();
		for (; init_list_it != init.end() && ll_it != this->end() ; init_list_it++, ll_it++)
			*ll_it = *init_list_it;
	}

	template<typename T>
	template<class InputIt>
	List<T>::List(InputIt _begin, InputIt _end) : List(0) {
		while(_begin != _end)
			this->push_back(*_begin++);
	}

	template<typename T>
	List<T>::~List() {
		_destroy();
	}

	template<typename T>
	void List<T>::assign(size_t count, const T& value) {
		_destroy();
		_init(count, value);
	}

	template<typename T>
	List<T>& List<T>::operator=(const List& other) {
		if (this == &other)
			return *this;

		_init(other.num_elements);

		for (auto it = this->begin(), o_it = other.begin() ; it != this->end() && o_it != other.end(); it++, o_it++)
			*it = *o_it;
		return *this;
	}

	template<typename T>
	List<T>& List<T>::operator=(List&& other) {
		this->first        = other.first;
		this->last         = other.last;
		this->num_elements = other.num_elements;

		other.first = other.last = nullptr;
		other.num_elements = 0;

		return *this;
	}

	template<typename T>
	List<T>& List<T>::operator=(std::initializer_list<T> init) {
		_init(init.size());
		auto init_list_it = init.begin();
		auto ll_it = this->begin();
		for (; init_list_it != init.end() && ll_it != this->end() ; init_list_it++, ll_it++)
			*ll_it = *init_list_it;
	}

	template<typename T>
	size_t List<T>::size() {
		return num_elements;
	}

	template<typename T>
	bool List<T>::empty() {
		return num_elements == 0;
	}

	template<typename T>
	T& List<T>::front() {
		if (empty())
			throw std::out_of_range("This List is empty.");
		return first->data;
	}

	template<typename T>
	T& List<T>::back() {
		if (empty())
			throw std::out_of_range("This List is empty.");
		return last->data;
	}

	template<typename T>
	void List<T>::push_back(const T& elem) {
		if (empty()) {
			_init(1, elem);
		} else {
			this->last->next = new node(elem, this->last, nullptr);
			this->last = this->last->next;
		}
		num_elements++;

	}

	template<typename T>
	void List<T>::push_front(const T& elem) {
		if (empty()) {
			_init(1, elem);
		} else {
			this->first = this->first->prev = new node(elem, nullptr, this->first);
		}
		num_elements++;
	}

	template<typename T>
	T List<T>::pop_back() {
		num_elements--;
		T elem = this->last->data;
		node *tmp = this->last;
		this->last = this->last->prev;
		delete tmp;
		return elem;
	}

	template<typename T>
	T List<T>::pop_front() {
		num_elements--;
		T elem = this->first->data;
		node *tmp = this->first;
		this->first = this->first->next;
		delete tmp;
		return elem;
	}

	template<typename T>
	typename List<T>::iterator List<T>::begin() {
		return iterator(this->first);
	}

	template<typename T>
	typename List<T>::iterator List<T>::end() {
		return iterator( this->last->next ); /* a fancy way to say nullptr */
	}

	template<typename T>
	typename List<T>::const_iterator List<T>::cbegin() const {
		return iterator(this->first);
	}

	template<typename T>
	typename List<T>::const_iterator List<T>::cend() const {
		return iterator( this->last->next );
	}

	template <typename T>
	void List<T>::clear() {
		_destroy();
	}

	/* ----------------------- */
	/*         HELPERS         */
	/* ----------------------- */

	template<typename T>
	void List<T>::_init(size_t count, const T& value) {
		if (num_elements != 0 || first != nullptr)
			return;/* rudimentary way to avoid memory leaks at this point... */

		this->first = this->last = nullptr;
		if ( count != 0 ) {
			this->first = this->last = new node(value, nullptr, nullptr);
			for (size_t i = 1; i < count; i++) {
				this->last->next = new node(value, this->last, nullptr); /* if this works, it'd be so cool, omg. */
				this->last = this->last->next;
			}
		}
		num_elements = count;
	}

	template<typename T>
	void List<T>::_destroy() {
		node *curr, *last;
		curr = first;
		last = nullptr;
		while(curr != nullptr) {
			last = curr;
			curr = curr->next;
			delete last;
		}
		num_elements = 0;
	}
}
#endif // CHARLES_VECTOR_H
