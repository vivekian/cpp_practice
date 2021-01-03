#include <condition_variable> 
#include <mutex> 
#include <queue> 
#include <string> 
#include <thread> 
#include <vector> 

using namespace std; 

namespace { 
    // buffer in which numbers are produced and consumed.
    queue<int> q; 
    // cnt keep tracks of the number being produced
    int cnt = 0; 
    // mutex lock which protects the queue and cnt
    mutex mtx;
    // condition variables to wait if queue is full or empty.
    condition_variable cvfull; 
    condition_variable cvempty; 
    // MAX value to which cnt will increment 
    const int MAX = 1000;
    // copy the items to out for verification
    vector<int> out; 
}


void producer(int loops) 
{
    for(int i=0;i<loops; ++i) 
    {
       unique_lock<mutex> lk(mtx); 

       while (q.size() == MAX) {
          cvempty.wait(lk);  
       }

       q.push(cnt); 
       ++cnt; 
       cvfull.notify_one(); 
       lk.unlock(); 
   } 
}

void consumer(int idx, int loops) 
{
    for (int i=0; i<loops; ++i) 
    {
       unique_lock<mutex> lk(mtx); 

       while (q.empty()) {
           cvfull.wait(lk); 
       }

       out.emplace_back(q.front()); 
       printf("%d: %d\n", idx, q.front()); 
       q.pop(); 
       cvempty.notify_one(); 
       lk.unlock();  
    } 
}

int main()
{
    vector<thread> cthreads, pthreads;  
    const int NUM_THREADS = 100; 
    static constexpr int numloops = MAX/NUM_THREADS;

    for (int i=0; i<NUM_THREADS; ++i) {
        pthreads.emplace_back(thread(producer, numloops));  
        cthreads.emplace_back(thread(consumer, i, numloops)); 
    }

    for (auto& t: pthreads) 
        t.join(); 

    for (auto& t: cthreads) 
        t.join(); 

    assert(q.empty());
    assert(out.size() == MAX);
    
    for (int i=0; i<MAX; ++i) {
       assert(i == out[i]);  
    }

    return 0; 
}
