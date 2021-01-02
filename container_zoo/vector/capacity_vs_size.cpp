#include <cassert> 
#include <iostream> 
#include <string> 
#include <vector> 

using namespace std; 

// struct foo to show how the vector invokes move and copy constructors when reallocating the
// array.
struct foo { 
    int a_; 
    int b_; 

    foo() = default; 
    foo(int a, int b): a_(a), b_(b) {cout << "constructor\n"; }

    // move constructor 
    foo(foo&& f) noexcept: a_(move(f.a_)), b_(move(f.b_)) { cout << "move constructor\n"; }
    ~foo() {cout << "destructor\n"; }
};


int main()
{
    // capacity is an attribute which tells how many items a vector could hold without having to reallocate the underlying array. 
    // size is the number of items which the vector is currently holding
    // when a vector reallocates the underlying memory, the start address changes, so all the iterators which are underlying this are invalided e.g. vec.begin(). this is a common source of bugs.    // .resize() invokes the default constructor.  
    
    vector<foo> vec; 

    auto printv = [&vec]() { 
        cout << "addr: " << &vec[0] << " size: " << vec.size() << " capacity: " << vec.capacity() << endl; 
    }; 

    vec.reserve(2); // vec now holds memory for 2 ints but vec.size() is still 0. 
    printv(); 
    vec.emplace_back(foo{1,2});
    vec.emplace_back(foo{2,3});
    printv(); 

    // size > capacity here so the vector will reallocate the underlying array. 
    vec.emplace_back(foo{1,2});
    printv();
    assert(vec.capacity() == 4);  
    vec.emplace_back(foo{2,3});  

    // size > capacity here so the vector will reallocate the underlying array. 
    vec.emplace_back(foo{2,3});
    printv();  
    assert(vec.capacity() == 8);  

    vec.resize(10); 
    return 0;  
}
