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

			_iterator operator+(difference_type s) const {
				node *tmp = curr;
				while(tmp != nullptr && s--)
					tmp = tmp->next;
				return _iterator(tmp);
			}

			_iterator operator-(difference_type s) const {
				node *tmp = curr;
				while(tmp != nullptr && s--)
					tmp = tmp->prev;
				return _iterator(tmp);
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

		void assign(size_t count, const T& value = T());

		iterator insert( const_iterator pos, const T& value );
		iterator insert( const_iterator pos, T&& value );
		iterator insert( const_iterator pos, size_t count, const T& value );
		iterator insert( const_iterator pos, std::initializer_list<T> ilist );

		template <class InputIt>
		iterator insert( const_iterator pos, InputIt first, InputIt last );

		iterator erase( const_iterator pos );
		iterator erase( const_iterator first , const_iterator last );

		void resize( size_t count , T value = T() );

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

		void swap(List<T>& other);

		void reverse();

		void remove(const T& value);

		template <class UnaryPredicate>
		void remove_if(UnaryPredicate p);

	private:
		/*              HELPERS              */
		void _init(size_t count, const T& value = T());
		void _destroy();

		void _insert( const_iterator pos, List<T>& other );

		/*
			@param n the node to unlink and delete

			@return a pointer to the node after n,
			or a nullptr if no next node exists.
		*/
		node *_unlink_and_delete(node *n);

	};

	template<class T>
	List<T>::List() : List(0) { }

	template<class T>
	List<T>::List(size_t count , const T& value) {
		first = last = nullptr;
		num_elements = 0;
		this->_init(count, value);
	}

	template<class T>
	List<T>::List(const List& other) : List(other.num_elements) {
		if (this == &other) return;

		for (auto it = this->begin(), o_it = other.cbegin() ; it != this->end() && o_it != other.cend(); it++, o_it++)
			*it = *o_it;
	}

	template<class T>
	List<T>::List(List&& other) {
		this->first        = other.first;
		this->last         = other.last;
		this->num_elements = other.num_elements;

		other.first = other.last = nullptr;
		other.num_elements = 0;
	}

	template<class T>
	List<T>::List(std::initializer_list<T> init) : List(init.size()) {
		auto init_list_it = init.begin();
		auto ll_it = this->begin();
		for (; init_list_it != init.end() && ll_it != this->end() ; init_list_it++, ll_it++)
			*ll_it = *init_list_it;
	}

	template<class T>
	template<class InputIt>
	List<T>::List(InputIt _begin, InputIt _end) : List(0) {
		while(_begin != _end)
			this->push_back(*_begin++);
	}

	template<class T>
	List<T>::~List() {
		_destroy();
	}

	template<class T>
	void List<T>::assign(size_t count, const T& value) {
		_destroy();
		_init(count, value);
	}

	template<class T>
	List<T>& List<T>::operator=(const List& other) {
		if (this == &other)
			return *this;

		_init(other.num_elements);

		for (auto it = this->begin(), o_it = other.begin() ; it != this->end() && o_it != other.end(); it++, o_it++)
			*it = *o_it;
		return *this;
	}

	template<class T>
	List<T>& List<T>::operator=(List&& other) {
		this->first        = other.first;
		this->last         = other.last;
		this->num_elements = other.num_elements;

		other.first = other.last = nullptr;
		other.num_elements = 0;

		return *this;
	}

	template<class T>
	List<T>& List<T>::operator=(std::initializer_list<T> init) {
		_init(init.size());
		auto init_list_it = init.begin();
		auto ll_it = this->begin();
		for (; init_list_it != init.end() && ll_it != this->end() ; init_list_it++, ll_it++)
			*ll_it = *init_list_it;
	}

	template<class T>
	size_t List<T>::size() {
		return num_elements;
	}

	template<class T>
	bool List<T>::empty() {
		return num_elements == 0;
	}

	template<class T>
	T& List<T>::front() {
		if (empty())
			throw std::out_of_range("This List is empty.");
		return first->data;
	}

	template<class T>
	T& List<T>::back() {
		if (empty())
			throw std::out_of_range("This List is empty.");
		return last->data;
	}

	template<class T>
	void List<T>::push_back(const T& elem) {
		if (empty()) {
			_init(1, elem);
		} else {
			this->last->next = new node(elem, this->last, nullptr);
			this->last = this->last->next;
			num_elements++;
		}
	}

	template<class T>
	void List<T>::push_front(const T& elem) {
		if (empty()) {
			_init(1, elem);
		} else {
			this->first = this->first->prev = new node(elem, nullptr, this->first);
		}
		num_elements++;
	}

	template<class T>
	T List<T>::pop_back() {
		num_elements--;
		T elem = this->last->data;
		node *tmp = this->last;
		this->last = this->last->prev;
		delete tmp;
		return elem;
	}

	template<class T>
	T List<T>::pop_front() {
		num_elements--;
		T elem = this->first->data;
		node *tmp = this->first;
		this->first = this->first->next;
		delete tmp;
		return elem;
	}

	template<class T>
	typename List<T>::iterator List<T>::insert( typename List<T>::const_iterator pos, const T& value ) {
		return this->insert( pos , 1 , value); /* calling third version */
	}

	// template<class T>
	// typename List<T>::iterator List<T>::insert( typename List<T>::const_iterator pos, T&& value ) {
	//
	// }

	template<class T>
	typename List<T>::iterator List<T>::insert( typename List<T>::const_iterator pos, size_t count, const T& value ) {
		if ( !count ) return pos;

		List<T> other( count , value );
		this->_insert( pos, other );
		return pos - count;
	}

	template<class T>
	template <class InputIt>
	typename List<T>::iterator List<T>::insert( typename List<T>::const_iterator pos, InputIt first, InputIt last ) {
		if (first == last) return pos;

		List<T> other( first , last );
		this->_insert( pos , other );
		return pos - std::distance(first,last);
	}

	template<class T>
	typename List<T>::iterator List<T>::insert( typename List<T>::const_iterator pos, std::initializer_list<T> ilist ) {
		if ( !ilist.size() ) return pos;

		List<T> other( ilist );
		this->_insert( pos , other );
		return pos - ilist.size();
	}

	template<class T>
	typename List<T>::iterator List<T>::erase( typename List<T>::const_iterator pos ) {
		List<T>::iterator it( _unlink_and_delete(pos.curr) );
		num_elements--;
		return it;
	}

	template<class T>
	typename List<T>::iterator List<T>::erase( typename List<T>::const_iterator first , typename List<T>::const_iterator last ) {
		List<T>::iterator it = first;
		while (it != last) {
			_unlink_and_delete(it.curr);
			it++;
			num_elements--;
		}
		return last;
	}

	template<class T>
	void List<T>::resize( size_t count , T value ) {
		if (num_elements > count) {
			this->erase( this->begin() + count , this->end() );
		} else if (num_elements < count) {
			this->insert( this->end() , count - num_elements , value );
		}
	}

	template<class T>
	typename List<T>::iterator List<T>::begin() {
		return iterator( this->first );
	}

	template<class T>
	typename List<T>::iterator List<T>::end() {
		return iterator( nullptr );
	}

	template<class T>
	typename List<T>::const_iterator List<T>::cbegin() const {
		return iterator(this->first);
	}

	template<class T>
	typename List<T>::const_iterator List<T>::cend() const {
		return iterator( nullptr );
	}

	template <class T>
	void List<T>::clear() {
		_destroy();
	}

	template <class T>
	void List<T>::swap(List<T>& other) {
		std::swap(this->num_elements , other.num_elements);
		std::swap(this->first , other.first);
		std::swap(this->last , other.last);
	}

	template <class T>
	void List<T>::reverse() {
		auto it = this->begin(),
		     it2  = this->begin() + (num_elements-1);

		size_t swaps = num_elements / 2 ;
		while (swaps--) std::swap(*it++ , *it2--);
	}

	template <class T>
	void List<T>::remove(const T& value) {
		List<T>::node *curr = first;
		while (curr != nullptr) {
			if (curr->data == value) {
				curr = _unlink_and_delete(curr);
				num_elements--;
			} else {
				curr = curr->next;
			}
		}
	}

	template <class T>
	template <class UnaryPredicate>
	void List<T>::remove_if( UnaryPredicate p ) {
		List<T>::node *curr = first;
		while (curr != nullptr) {
			if ( p( curr->data ) ) {
				curr = _unlink_and_delete(curr);
				num_elements--;
			} else {
				curr = curr->next;
			}
		}
	}

	/* ----------------------- */
	/*         HELPERS         */
	/* ----------------------- */

	template<class T>
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

	template<class T>
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

	template<class T>
	void List<T>::_insert( typename List<T>::const_iterator pos, List<T>& other ) {
		auto curr = pos.curr;

		if (curr) {
			if (curr->prev) {
				curr->prev->next = other.first;
			}
			if (curr->next) {
				curr->next->prev = other.last;
			}
			other.first->prev = curr->prev;
			curr->prev = other.last;
		} else {
			this->last->next = other.first;
			this->last = other.last;
		}

		other.last->next = curr;

		while(this->first->prev)
			this->first = this->first->prev;
		while(this->last->next)
			this->last = this->last->next;

		this->num_elements += other.num_elements;

		other.first = other.last = nullptr; /* so that newly inserted elements aren't
		                                       destroyed at the end of the func. */
	}

	template<class T>
	typename List<T>::node *List<T>::_unlink_and_delete(typename List<T>::node *n) {
		if (n == nullptr)
			return nullptr;

		if (n->next)
			n->next->prev = n->prev;
		if (n->prev)
			n->prev->next = n->next;

		if (n == first)
			first = first->next;
		if (n == last)
			last = last->prev;

		node *next = n->next;
		delete n;

		return next;
	}

}
#endif // CHARLES_VECTOR_H
