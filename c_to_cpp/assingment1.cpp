// Convert this program to C++
// change to C++ io
// change to one line comments
// change defines of constants to const
// change array to vector<>
// inline any short function

#include <iostream> 
#include <vector> 

using namespace std; 

static const int N = 40; 

inline void sum(int &p, const vector<int>& d)
{
    p = 0; 

    for (const auto &i : d) { 
        p += i; 
    }
}

int main()
{
    vector<int>data(N); 
    int accum; 

    for (int i=0; i<N; ++i) { 
        data[i] = i; 
    }

    sum(accum, data); 

    cout << "sum is " << accum << endl; 
    return 0; 
} 
