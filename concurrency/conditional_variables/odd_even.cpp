// write code to interleave two threads to print odd and even numbers.  

#include <condition_variable> 
#include <iostream> 
#include <mutex> 
#include <thread>

using namespace std; 

condition_variable cond; 
mutex mut; 

namespace { 
    const int MAX_ELEMS = 100;
    int ctrOdd = 1; 
    int ctrEven = 0; 
} 

void odd_thread() 
{
    while (ctrOdd < MAX_ELEMS) {      
        unique_lock<mutex> lk(mut); 
        cond.wait(lk, [] { return ((ctrOdd - ctrEven) == 1); });
        cout << ctrOdd << endl; 
        ctrOdd += 2; 
        cond.notify_one(); 
        lk.unlock(); 
    }
}

void even_thread() 
{ 
    while (ctrEven < MAX_ELEMS) { 
        unique_lock<mutex> lk(mut); 
        cond.wait(lk, [] { return ((ctrOdd - ctrEven) == 3); }); 
        ctrEven += 2; 
        cout << ctrEven << endl; 
        cond.notify_one(); 
        lk.unlock(); 
    } 
}

int main() 
{ 
    thread t1(odd_thread); 
    thread t2(even_thread); 

    t2.join(); 
    t1.join(); 

    return 0; 
}
