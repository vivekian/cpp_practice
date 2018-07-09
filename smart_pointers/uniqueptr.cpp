// Simple example to illustrate RAII for unique pointers 
// Unique pointers support both -> and * operators and provide automatic garbage collection.  

#include <iostream> 
#include <vector> 
using namespace std; 

class X 
{ 
public: 
	X(){} 
	~X() { cout << "Destructor X" << endl; } 
	void Print() { cout << "X" << endl; } 
private: 
	int _foo; 
}; 

int main() 
{ 
	unique_ptr<X> ptr(new X()); 
	ptr->Print();

	vector<unique_ptr<X>> v; 
	v.push_back(move(ptr));  
	ptr->Print(); 
	v.front()->Print();  	

	return 0; 
} 
