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
		List (InputIt _begin, InputIt _end);

		void operator=(const List& other);
	 	void operator=(List&& other);
		void operator=(std::initializer_list<T> init);

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

	};
}
