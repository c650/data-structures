/*
	A vector implementation by Charles Bailey
	Because sundays are boring.

	12/4/16
*/
#include <stdexcept>

namespace Charlie {

	typedef unsigned int size_t;

	template <typename T>
	class Vector {
		T *stuff;
		size_t actual_size, num_elements;

	  public:
		Vector();
		Vector(size_t _size, T def = T());
		Vector(const Vector<T>& other);
		Vector(Vector<T>&& other);

		void operator=(const Vector<T>& other);
		void operator=(Vector<T>&& other);

		~Vector();

		T& operator[](size_t index);
		const T& operator[](size_t index) const;

		T& at(size_t index);
		const T& at(size_t index) const;

		T& front();
		const T& front() const;

		T& back();
		const T& back() const;

		T* data();
		const T* data() const;

		bool empty() const;

		void push_back(const T& item);
		T pop_back();

		void insert(const int& index , const T& item);

		size_t size() const;
		size_t capacity() const;
		size_t max_size() const;

		void shrink_to_fit();
		void reserve(size_t new_size);

		void resize(size_t count);
		void resize(size_t count , const T& value);
		void assign(size_t count , const T& value);

		void clear();
		void swap(Vector<T>& other);

		bool operator==(const Vector<T>& other) const;
		bool operator!=(const Vector<T>& other) const;
		bool operator<=(const Vector<T>& other) const;
		bool operator>=(const Vector<T>& other) const;
		bool operator<(const Vector<T>& other) const;
		bool operator>(const Vector<T>& other) const;

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
	void Vector<T>::operator=(const Vector<T>& other) {
		if (this == &other)
			return;

		actual_size = other.actual_size;
		stuff = new T[actual_size];

		num_elements = 0;
		while(num_elements < other.num_elements) {
			stuff[num_elements] = other.stuff[num_elements];
			num_elements++;
		}
	}

	template <typename T>
	void Vector<T>::operator=(Vector<T>&& other) {
		if (this == &other)
			return;

		actual_size = other.actual_size;
		num_elements = other.num_elements;

		stuff = other.stuff;
		other.stuff = nullptr;
	}

	template <typename T>
	Vector<T>::~Vector() {
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
		insert(num_elements, item);
	}

	template <typename T>
	T Vector<T>::pop_back() {
		return stuff[--num_elements];
	}

	template <typename T>
	void Vector<T>::insert(const int& index , const T& item) {
		if (num_elements >= actual_size) {
			_grow();
		}


		int curr = num_elements++; /* pay attention to this. I'm too lazy to make it its own line. :) */
		while (--curr >= index) {
			stuff[curr+1] = stuff[curr];
		}
		stuff[ index ] = item;
	}

	template <typename T>
	size_t Vector<T>::size() const {
		return actual_size;
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
			_resize(actual_size);
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
	void Vector<T>::swap(Vector<T>& other) {
		std::swap(this->num_elements , other.num_elements);
		std::swap(this->actual_size , other.actual_size);
		std::swap(this->stuff, other.stuff);
	}

	template <typename T>	
	bool Vector<T>::operator==(const Vector<T>& other) const {
		if (other.actual_size != this->actual_size) return false;
		for (size_t i = 0; i < this->actual_size; i++) {
			if (other.stuff[i] !+ this->stuff[i])
				return false;
		}
		return true;
	}
	
	template <typename T>
	bool Vector<T>::operator!=(const Vector<T>& other) const {
		return !(*this == other);
	}
	
	template <typename T>
	bool Vector<T>::operator<=(const Vector<T>& other) const;
	
	template <typename T>
	bool Vector<T>::operator>=(const Vector<T>& other) const;
	
	template <typename T>
	bool Vector<T>::operator<(const Vector<T>& other) const;
	
	template <typename T>
	bool Vector<T>::operator>(const Vector<T>& other) const;

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
