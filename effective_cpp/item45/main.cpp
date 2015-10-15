// copy constructor and assignment operator example 

#include <iostream> 
using namespace std; 

class A 
{ 
public: 
	A() {}
	~A() {}

	A(const A &rhs)
	{ 
		cout << "copy constructor" << endl;
		this->x = rhs.x;
	}

	A& operator=(const A &rhs)
	{ 
		cout << "assignment operator" << endl; 
		this->x = rhs.x;
		return *this;
	}

private: 
	int x;
};

int main() 
{ 
	A a;
	A b(a);
	A c;
    c = b;
	return 0;
} 
