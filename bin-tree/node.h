template <class T>
class node {
  private:
	T data;
	
  public:

  	node<T>* left,right;
	
	// class constructor
	node(T _data = 0, node<T>* l = nullptr, node<T>* r = nullptr)
		: data(_data), left(l), right(r) {}
	
	~node();

	T& d(); // data accessor
	void d(T _data); // data setter

	void print();
};