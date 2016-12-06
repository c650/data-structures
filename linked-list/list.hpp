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

			node(T _data) : data(_data) , next(nullptr) {}
			node() : this(T()) {}
		};

		node *first, *last;
		size_t len;

	  public:

	  	List();
		explicit List( size_t count , const T& value = T());
		List(const List& other);
		List(List&& other);
		List(std::initializer_list<T> init);

		template <class InputIt>
		List (InputIt _begin, InputIt _end);

		void operator=(const List& other);
	 	void operator=(List&& other);
		void operator=(std::initializer_list<T> init);

		~List();

	  	void append(T _data);

	  	T pop();

		node<T>* search(const T& q);

		node<T>* insert(T val, const size_t& idx);

		T del(const size_t& idx);

		size_t size();

	};
}
