#include <iostream> 
using namespace std; 

class A 
{
    private: 
        int x; 
}; 

void updateA (A *pA)
{ 
    return;
}

int main() 
{ 
    A a;
    const A &b = a;   
    updateA(const_cast<A*>(&b));
    return 0;
}
