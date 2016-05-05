// the lifetime of an object managed by shared_ptr is the range of the scope 
// of the pointers. when the last shared_ptr stops pointing to the object, 
// reference count becomes 0, and the object is destroyed. 
//
// this gives deterministic destruction along with automatic garbage collection. 
//
// shared_ptr maintains a refernce count which tells it how many shared_ptrs are tracking it. 
//
// constructors increment this count, destructors decrement this count and when count == 0, 
// object is destroyed. 
//
// the size of shared_ptr is twice that of the raw pointer, because it maintains a ref count. 

#include <iostream> 
#include <memory> 

class X 
{ 
public: 
    X(int data):_data(data) { 
        std::cout << "ctr" << std::endl; 
    }

    ~X() { std::cout << "dtr: " << _data << std::endl; } 

    X(const X& other) 
    { 
        std::cout << "copy ctr" << std::endl; 
        _data = other._data; 
    }
   
    void setData(int a) 
    { 
        _data = a;
    } 

    int getData()
    { 
        return _data; 
    }

private: 
    int _data; 
}; 

int main() 
{ 
    X a(23);    // normal construction 
    X& b = a;   // normal reference to an object 
    std::shared_ptr<X> res = std::make_shared<X>(b); // shared_ptr pointing to b (copy ctr invoked)
    std::shared_ptr<X> res2 = res;                   // reference count increased 

    // size is 16 bytes. 
    std::cout << "size of a shared_ptr: " << sizeof(res) << std::endl; 

    a.setData(46); // changing a has no effect on res because a new object was created with make_shared
    std::cout << res->getData() << std::endl;        
    res2->setData(55); 
    std::cout << res->getData() << std::endl; 

    // implicitly res is destroyed 
    // implicitly res2 is destroyed 

    return 0; 
}
