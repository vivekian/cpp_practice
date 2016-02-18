#include <iostream> 
#include <string> 

using namespace std; 

template <class summable> 
summable sum(const summable arr[], int size, const summable s = 0) 
{ 
    summable result = s; 

    for (int i=0; i<size; ++i) { 
        result += arr[i]; 
    }

    return result; 
}

int main() 
{ 
    int a[] = {1,2,3,4,5}; 
    double b[] = {1.22, 2.41, 4.5, 7.1, 8.8};

    cout << sum(a, 5, 0) << endl;
    cout << sum(b, 5, 0.0) << endl;

    return 0;  
}
