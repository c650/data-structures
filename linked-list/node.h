template <class T>
class node {
  private:
	T data;

  public:
	node<T>* next;

	// class constructor
	node(T _data = 0, node<T>* ptr = nullptr)
		: data(_data), next(ptr) {}
	
	~node();

	T& d(); // data accessor
	void d(T _data); // data setter

	void print();
};