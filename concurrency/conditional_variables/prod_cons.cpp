#include <condition_variable> 
#include <iostream> 
#include <mutex> 
#include <queue> 
#include <thread>

using namespace std; 

condition_variable cond; 
mutex mut; 
queue<int> q; 

namespace { 
    const int MAX_ELEMS = 10000;
    int i = 0;

    bool more_data_to_produce()
    { 
        return (i < MAX_ELEMS); 
    }

    int get_next_data() 
    {
        return ++i; 
    }
} 

void producer_thread() 
{ 
    while (more_data_to_produce()) { 
        auto x = get_next_data(); 
        lock_guard<mutex> lk(mut); 
        q.push(x); 
        cond.notify_one();              // notify the other thread that data is available. 
    }
}

void consumer_thread() 
{ 
    while (true) { 
        unique_lock<mutex> lk(mut);     // unique_lock is used to be able to unlock implicitely

        // this is how wait() works - wait first executes the lambda function to
        // see if its satisfied, then it returns and execution proceeds. If it 
        // not satisfied, then it unlocks the mutex and puts the thread in blocked state. 
        // when its notified by the other thread, it wakes up and tries again. 
        cond.wait(lk, [] { return !q.empty();});
        
        auto x = q.front(); 
        q.pop(); 
        lk.unlock(); 
       
        cout << x << endl; 

        if (x == MAX_ELEMS)
            break; 
    } 
}

int main() 
{ 
    thread t1(producer_thread); 
    thread t2(consumer_thread); 

    t1.join(); 
    t2.join(); 

    return 0; 
}
