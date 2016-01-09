#include <algorithm>
#include <iostream>
#include <random> 
#include <vector> 

using namespace std; 

// This simple example generates 50 numbers randomly between 1 to MAX_NUMS and 
// then returns the first number encountered between 40 to 60. The idea is to to use modern 
// c++11 features. 

int main()
{ 
    vector<int> v;
    const uint32_t MAX_NUMS = 50;  
    
    //uniformly distributed random number generator that produces non-deterministic numbers. 
    random_device rd; 
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < MAX_NUMS; i++)
        v.push_back(dist(mt)); 

    for (auto i: v) 
        cout << i << " ";

    cout << endl << endl; 

    // use lambdas to select the first number between 40 and 60.
    auto selected = find_if(v.begin(), v.end(), 
                           [](int val) { return (val >= 40 && val <= 60); });
    
    if (selected == v.end())
        cout << "no suitable candidate found" << endl; 

    cout << *selected << endl;  
    
    return 0;
} 
