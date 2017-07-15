/*
	A vector implementation by Charles Bailey
	Because sundays are boring.

	12/4/16
*/

#ifndef CHARLES_VECTOR_H
#define CHARLES_VECTOR_H

#include <stdexcept>
#include <initializer_list>
#include <iterator>

#include <iostream>

namespace Charles {

	/*
		This implementation corresponds closely to std::vector,
		except that Allocators are not present here. Also, I have
		added .each and .map, because sorta-functional programming
		is pretty cool.
	*/

	typedef unsigned int size_t;

	template <typename T>
	class Vector {

		typedef T value_type;
		typedef long difference_type;
		typedef value_type& reference;
		typedef const reference const_reference;
		typedef T* pointer;
		typedef const pointer const_pointer;

		T *stuff;
		size_t actual_size, num_elements;

		class _iterator : public std::iterator<std::random_access_iterator_tag, value_type, difference_type, pointer, reference> {
		  public:
			T* ptr;

			explicit _iterator(T* _ptr) : ptr(_ptr) {}

			_iterator& operator++() {
				++ptr;
				return *this;
			}
			_iterator operator++(int) {
				T* temp = ptr++;
				return _iterator(temp);
			}

			_iterator& operator--() {
				--ptr;
				return *this;
			}
			_iterator operator--(int) {
				T* temp = ptr--;
				return _iterator(temp);
			}

			_iterator operator+(difference_type s) const {
				return _iterator(ptr + s);
			}

			_iterator operator-(difference_type s) const {
				return _iterator(ptr - s);
			}

			difference_type operator-(_iterator& other) const {
				return this->ptr > other.ptr ? this->ptr - other.ptr : other.ptr - this->ptr;
			}

			bool operator==(const _iterator& other) const {
				return this->ptr == other.ptr;
			}
			bool operator!=(const _iterator& other) const {
				return this->ptr != other.ptr;
			}

			reference operator*() const {
				return *ptr;
			}
		};

		typedef _iterator iterator;
		typedef const iterator const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef const reverse_iterator const_reverse_iterator;


	  public:
		Vector();
		Vector(size_t _size, T def = T());
		Vector(const Vector<T>& other);
		Vector(Vector<T>&& other);
		Vector(std::initializer_list<T> init);

		template <class InputIt>
		Vector(InputIt _begin, InputIt _end);

		Vector<T>& operator=(const Vector<T>& other);
		Vector<T>& operator=(Vector<T>&& other);
		Vector<T>& operator=(std::initializer_list<T> init);

		~Vector();

		T& operator[](size_t index);
		const T& operator[](size_t index) const;

		T& at(size_t index);
		const T& at(size_t index) const;

		T& front();
		const T& front() const;

		T& back();
		const T& back() const;

		iterator begin();
		iterator end();
		const_iterator cbegin() const;
		const_iterator cend() const;

		T* data();
		const T* data() const;

		bool empty() const;

		void push_back(const T& item);
 		T pop_back();

		void insert(int& index , T& item);

		/* TODO: */
		iterator insert(const_iterator pos, const T& item);
		iterator insert(const_iterator pos, T&& item);
		iterator insert(const_iterator pos, size_t count, const T& item);

		size_t size() const;
		size_t capacity() const;
		size_t max_size() const;

		void shrink_to_fit();
		void reserve(size_t new_size);

		void resize(size_t count);
		void resize(size_t count , const T& value);
		void assign(size_t count , const T& value);

		void clear();

		iterator erase(const_iterator pos);
		iterator erase(const_iterator first, const_iterator last);

		void swap(Vector<T>& other);

		bool operator==(const Vector<T>& other) const;
		bool operator!=(const Vector<T>& other) const;
		bool operator<=(const Vector<T>& other) const;
		bool operator>=(const Vector<T>& other) const;
		bool operator<(const Vector<T>& other) const;
		bool operator>(const Vector<T>& other) const;

		template <class Func>
		Vector<T> map(const Func& f);

		template <class Func>
		void each(const Func& f) const;

	  private:

		void _grow();
		void _resize(const size_t& new_size);
	};

	template <typename T>
	Vector<T>::Vector() : actual_size(10), num_elements(0) {
		stuff = new T[actual_size];
	}

	template <typename T>
	Vector<T>::Vector(size_t _size, T def) {
		actual_size = _size;
		stuff = new T[actual_size];

		num_elements = 0;
		while (num_elements < actual_size)
			stuff[num_elements++] = def;
	}

	template <typename T>
	Vector<T>::Vector(const Vector<T>& other) {
		*this = other;
	}

	template <typename T>
	Vector<T>::Vector(Vector<T>&& other) {
		*this = other;
	}

	template <typename T>
	Vector<T>::Vector(std::initializer_list<T> init) {
		*this = init;
	}

	template <typename T>
	template <class InputIt>
	Vector<T>::Vector(InputIt _begin, InputIt _end) {
		num_elements = actual_size = std::distance(_end, _begin);

		stuff = new T[actual_size];
		for (size_t i = 0; i < num_elements && _begin != _end; i++) {
			stuff[i] = *_begin++;
		}
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
		if (this == &other)
			return *this;

		actual_size = other.actual_size;
		stuff = new T[actual_size];

		num_elements = 0;
		while(num_elements < other.num_elements) {
			stuff[num_elements] = other.stuff[num_elements];
			num_elements++;
		}
		return *this;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
		if (this == &other)
			return *this;

		actual_size = other.actual_size;
		num_elements = other.num_elements;

		stuff = other.stuff;
		other.stuff = nullptr;
		return *this;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(std::initializer_list<T> init) {
		num_elements = actual_size = init.size();
		stuff = new T[actual_size];
		for (size_t i = 0; i < num_elements; i++) {
			stuff[i] = *(init.begin() + i);
		}
		return *this;
	}

	template <typename T>
	Vector<T>::~Vector() {
		if (stuff != nullptr)
			delete [] stuff;
	}

	template <typename T>
	T& Vector<T>::operator[](size_t index) {
		return stuff[index];
	}

	template <typename T>
	const T& Vector<T>::operator[](size_t index) const {
		return stuff[index];
	}

	template <typename T>
	T& Vector<T>::at(size_t index) {
		if (index >= num_elements)
			throw std::out_of_range("That index is out of range.");
		return stuff[index];
	}

	template <typename T>
	const T& Vector<T>::at(size_t index) const {
		if (index >= num_elements)
			throw std::out_of_range("That index is out of range.");
		return stuff[index];
	}

	template <typename T>
	T& Vector<T>::front() {
		return at(0);
	}

	template <typename T>
	const T& Vector<T>::front() const {
		return at(0);
	}

	template <typename T>
	T& Vector<T>::back() {
		return at(num_elements - 1);
	}

	template <typename T>
	const T& Vector<T>::back() const {
		return at(num_elements - 1);
	}

	template <typename T>
	typename Vector<T>::iterator Vector<T>::begin() {
		return iterator(stuff);
	}

	template <typename T>
	typename Vector<T>::iterator Vector<T>::end() {
		return iterator(stuff + num_elements);
	}

	template <typename T>
	typename Vector<T>::const_iterator Vector<T>::cbegin() const {
		return begin();
	}

	template <typename T>
	typename Vector<T>::const_iterator Vector<T>::cend() const {
		return end();
	}

	template <typename T>
	T* Vector<T>::data() {
		return stuff;
	}

	template <typename T>
	const T* Vector<T>::data() const {
		return (const T*)stuff;
	}

	template <typename T>
	bool Vector<T>::empty() const {
		return num_elements == 0;
	}

	template <typename T>
	void Vector<T>::push_back(const T& item) {
		if (num_elements >= actual_size)
			_grow();
		stuff[num_elements++] = item;
	}

	template <typename T>
	T Vector<T>::pop_back() {
		return stuff[--num_elements];
	}

	template <typename T>
	void Vector<T>::insert(int& index , T& item) {
		this->insert( begin() + index , 1 , item );
	}

	/* still working on this */
	template <typename T>
	typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, const T& item) {
		return this->insert(pos, 1, item);
	}

	template <typename T>
	typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, T&& item) {
		return this->insert(pos, 1, item);
	}

	template <typename T>
	typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, size_t count, const T& item) {
		while (num_elements + count > actual_size)
			_grow();

		long curr = num_elements;
		long index = pos.ptr - stuff;

		while (--curr >= index ) {
			stuff[curr + count] = stuff[curr];
		}
		for (size_t i = 0; i < count; i++) {
			stuff[index++] = item;
		}
		num_elements += count;
		return pos;
	}

	template <typename T>
	size_t Vector<T>::size() const {
		return num_elements;
	}

	template <typename T>
	size_t Vector<T>::capacity() const {
		return actual_size;
	}

	template <typename T>
	size_t Vector<T>::max_size() const {
		size_t sz = 0;
		return (sz-1);
	}

	template <typename T>
	void Vector<T>::shrink_to_fit() {
		_resize(num_elements);
	}

	template <typename T>
	void Vector<T>::reserve(size_t new_size) {
		if (new_size > actual_size)
			_resize(new_size);
	}

	template <typename T>
	void Vector<T>::resize(size_t count) {
		_resize(count);
	}

	template <typename T>
	void Vector<T>::resize(size_t count , const T& value) {
		bool writein = count > actual_size;
		_resize(count);

		if (writein)
			while (num_elements < actual_size)
				stuff[num_elements++] = value;
	}

	template <typename T>
	void Vector<T>::assign(size_t count , const T& value) {
		num_elements = 0;
		resize(count, value);
	}

	template <typename T>
	void Vector<T>::clear() {
		for (size_t i = 0; i < num_elements; i++) {
			stuff[i] = T();
		}
		num_elements = 0;
	}

	template <typename T>
	typename Vector<T>::iterator Vector<T>::erase(const_iterator pos) {
		return this->erase(pos, pos+1);
	}

	template <typename T>
	typename Vector<T>::iterator Vector<T>::erase(const_iterator first, const_iterator last) {
		for (iterator peek = last, hold = first; peek != this->end(); ++peek, ++hold) {
			*hold = std::move(*peek);
		}
		// amend size.
		num_elements -= std::distance(first, last); /* pretty sure the iterators meet RandomAccessIterator so this is constant time */
		return first;
	}

	template <typename T>
	void Vector<T>::swap(Vector<T>& other) {
		std::swap(this->num_elements , other.num_elements);
		std::swap(this->actual_size , other.actual_size);
		std::swap(this->stuff, other.stuff);
	}

	template <typename T>
	bool Vector<T>::operator==(const Vector<T>& other) const {
		if (other.num_elements != this->num_elements) return false;
		for (size_t i = 0; i < this->num_elements; i++) {
			if (other.stuff[i] != this->stuff[i])
				return false;
		}
		return true;
	}

	template <typename T>
	bool Vector<T>::operator!=(const Vector<T>& other) const {
		return !(*this == other);
	}

	template <typename T>
	bool Vector<T>::operator<=(const Vector<T>& other) const {
		/* check that *this <= other by factoring out a NOT */
		return !(*this > other);
	}

	template <typename T>
	bool Vector<T>::operator>=(const Vector<T>& other) const {
		return !(*this < other);
	}

	template <typename T>
	bool Vector<T>::operator<(const Vector<T>& other) const {
		size_t n = this->num_elements < other.num_elements ? this->num_elements : other.num_elements;
		for (size_t i = 0; i < n; i++) {
			if ( this->stuff[i] >= other.stuff[i] )
				return false;
		}
		/* A shorter list is "less than," but two list of equal size are
			ALSO "less than" because the elements of *this must all be less than
			the corresponding elements of other to have gotten this far. */
		return this->num_elements <= other.num_elements;
	}

	template <typename T>
	bool Vector<T>::operator>(const Vector<T>& other) const {
		size_t n = this->num_elements < other.num_elements ? this->num_elements : other.num_elements;
		for (size_t i = 0; i < n; i++) {
			if ( this->stuff[i] <= other.stuff[i] )
				return false;
		}
		/* same logic as < */
		return this->num_elements >= other.num_elements;
	}

	template <typename T>
	template <class Func>
	Vector<T> Vector<T>::map(const Func& f) {
		Vector<T> new_vec(*this);
		for (size_t i = 0; i < num_elements; i++)
			f(new_vec[i]);
		return new_vec;
	}

	template <typename T>
	template <class Func>
	void Vector<T>::each(const Func& f) const {
		T tmp;
		for (size_t i = 0; i < num_elements; i++) {
			tmp = stuff[i];
			f(tmp);
		}
	}

	template <typename T>
	void Vector<T>::_grow() {
		_resize(2 * actual_size + 1);
	}

	template <typename T>
	void Vector<T>::_resize(const size_t& new_size) {
		if (actual_size == new_size)
			return;

		actual_size = new_size;
		T *tmp = new T[actual_size];

		size_t n = actual_size < num_elements ? actual_size : num_elements;
		for (size_t i = 0; i < n; i++)
			tmp[i] = stuff[i];

		delete [] stuff;
		stuff = tmp;
	}

};

#endif // CHARLES_VECTOR_H
