// unique_ptrs are same size as raw pointers. little or no overhead
// exclusive ownership semantics. i.e. ownership is with the source pointer always
// no copy allowed, but ownership can be moved to destination 
// upon destruction, a non-null unique_ptr always destroys its resource. i.e. it calls delete automagically. 
// if custom deleters are used then its quite possible that size of the pointer will grow depending on
// how much state the function stores. 

// the unique_ptr API can be used with arrays 

#include <memory> 
#include <iostream> 

using namespace std; 

void print_unique_ptr_size() 
{ 
    unique_ptr<int> ptr(new int(2)); 
    cout << sizeof(ptr) << endl; 
} 

int main() 
{ 
    print_unique_ptr_size();
    return 0; 
}
