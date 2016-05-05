#include <iostream> 
#include <memory> 

class X 
{ 
public: 
    X(int data):_data(data) { 
        std::cout << "ctr" << std::endl; 
    }

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
    X a(23);
    X& b = a;  
    std::shared_ptr<X> res = std::make_shared<X>(b);
    std::shared_ptr<X> res2 = res; 

    a.setData(46); 
    res2->setData(46); 

    std::cout << res->getData() << std::endl; 

    return 0; 
}
