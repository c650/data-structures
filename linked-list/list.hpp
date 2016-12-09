#include <stdexcept>
#include <initializer_list>

namespace Charles {

	typedef unsigned int size_t;

	template <class T>
	class List {
	  private:
		struct node {
			T data;
			struct node *next, *prev;

			explicit node(T _data, struct node *_prev = nullptr, struct node *_next = nullptr)
				: data(_data),
				prev(_prev),
				next(_next) {}
		};

		node *first, *last;
		size_t num_elements;

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

		void assign()

		size_t size();
		bool empty();

		T& front();
		T& end();

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		void push_back();
		void push_front();

		T pop_back();
		T pop_front();

	  private:
		void _init(size_t count, const T& value = T());

	};

	template<typename T>
	List<T>::List() : this(0) { }

	template<typename T>
	List<T>::List(size_t count , const T& value = T()) {
		this->_init(count, value);
	}

	template<typename T>
	List<T>::List(const List& other) : this(other.num_elements) {
		if (this == &other) return;

		node *curr = other.first,
		     *local_curr = this->first;
		while(curr != nullptr && local_curr != nullptr) {
			local_curr->data = curr->data;
			curr = curr->next;
			local_curr = local_curr->next;
		}
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
	List<T>::List(std::initializer_list<T> init) : this(init.size()) {
		auto init_list_it = init.begin();
		node *curr = this->first;
		while(curr != nullptr && init_list_it != init.end()) {
			curr->data = *init_list_it++;
			curr = curr->next;
		}
	}

	// template<typename T>
	// template<class InputIt>
	// List<T>::List(InputIt _begin, InputIt _end) {
	//
	// }

	template<typename T>
	List<T>::~List() {
		node *curr, *last;
		curr = first;
		last = nullptr;
		while(curr != nullptr) {
			last = curr;
			curr = curr->next;
			delete last;
		}
	}

	template<typename T>
	List<T>& List<T>::operator=(const List& other) {
		if (this == &other)
			return *this;

		_init(other.num_elements);
		node *curr = other.first,
		     *local_curr = this->first;
		while(curr != nullptr && local_curr != nullptr) {
			local_curr->data = curr->data;
			curr = curr->next;
			local_curr = local_curr->next;
		}
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
		
	}

	/* ----------------------- */
	/*       HELPERS           */
	/* ----------------------- */

	template<typename T>
	void Vector<T>::_init(size_t count, const T& value = T()) {
		if (num_elements != 0 || first != nullptr)
			return;/* rudimentary way to avoid memory leaks at this point... */

		this->first = this->last = nullptr;
		if ( count != 0 ) {
			this->first = this->last = new node(value, nullptr, nullptr);
			for (size_t i = 1; i < count; i++) {
				this->last->next = this->last = new node(value, this->last, nullptr); /* if this works, it'd be so cool, omg. */
			}
		}
		num_elements = count;
	}
}
