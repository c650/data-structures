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

      node<T>* search(const T& q);

      node<T>* insert(T val, const size_t& idx);

      T del(const size_t& idx);

      size_t size();

      void print();


};