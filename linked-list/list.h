#include <iostream>

template <class T>
class List {
  private:
	  node<T>* root;
	  size_t len;

  public:

  	List()
  		: root(nullptr), len(0) {}

  	~List();

  	T& operator[](size_t idx);

  	void append(T _data);

  	T pop();

  	size_t size();

    void print();
};