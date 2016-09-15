#include <iostream>
#include <thread>

using namespace std; 

// RAII class to join threads once completed. 
// In case exception is thrown class guarantees that thread will be joined.
class ScopedThread
{ 
    private: 
        thread t; 

    public: 
        explicit ScopedThread(thread  _t): t(move(_t))
        {}

        ~ScopedThread()
        { 
            t.join();
        }

        ScopedThread(ScopedThread const &)=delete;
        ScopedThread& operator=(ScopedThread const &)=delete;
};

// compiler will optimize and precompute sum
long add_nums(long x, long y) 
{ 
    return x + y;
}

void do_some_work()
{ 
    unsigned i = 0; 
    long sum = 0; 

    for (; i < 10000000 ; i++) 
        sum = add_nums(i, sum);

    cout << sum << endl;
}    

int main(int argc, char* argv[]) 
{ 
    ScopedThread st({thread(do_some_work)}); 
    return 0;
} 
