#include <iostream> 
#include <thread> 
#include "simple_lock.h" 

using namespace std; 

namespace { 
    SimpleLock lck; 
} 

void thread1() 
{ 
    lck.lock(); 
    cout << "thread 1\n"; 
    lck.unlock();
} 

void thread2() 
{ 
    lck.lock(); 
    cout << "thread 2\n";
    lck.unlock();
} 

int main()
{ 
    std::thread t1(thread1); 
    std::thread t2(thread2); 

    t1.join(); 
    t2.join(); 
    return 0; 
} 
