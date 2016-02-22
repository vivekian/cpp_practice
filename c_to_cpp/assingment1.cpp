// Convert this program to C++
// change to C++ io
// change to one line comments
// change defines of constants to const
// change array to vector<>
// inline any short function

#include <iostream> 
#include <vector> 

using namespace std; 

// N points to the number of elements to be summed
static const int N = 40; 

// result - result of adding all the integers
// data - vector of input data to be summed
inline void sum(int &result, const vector<int>& data)
{
    result = 0; 

    // iterate data vector and each element to result
    for (const auto &i : data) { 
        result += i; 
    }
}

int main()
{
    // create data vector on stack with N elements
    vector<int>data(N); 
    int accum; 

    // initialize data vector
    for (int i=0; i<N; ++i) { 
        data[i] = i; 
    }

    sum(accum, data); 

    cout << "sum is " << accum << endl; 
    return 0; 
} 
