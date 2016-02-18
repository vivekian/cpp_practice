#include <iostream> 
#include <cassert> 

using namespace std; 

template <typename T> 
inline void swap(const T& a, const T& b)
{ 
    T tmp = a; 
    a = b; 
    b = tmp; 
}

int main() 
{ 
    int a = 5, b =3; 
    swap(a,b); 
    assert ((a == 3) && (b == 5)); 
    
    double ad = 2.3, bd = 4.4; 
    swap(ad,bd);
    assert((ad == 4.4) && (bd == 2.3));

    return 0; 
}
