#include <iostream>
#include <thread>

using namespace std; 

// RAII class to join threads once completed. 
// In case exception is thrown class guarantees that thread will be joined.
class ThreadGuard
{ 
    private: 
        thread &t; 

    public: 
        ThreadGuard(thread& _t): t(_t)
        {}

        ~ThreadGuard()
        { 
            if (t.joinable()) { 
                t.join();
            }
        }

        ThreadGuard(ThreadGuard const &)=delete;
        ThreadGuard& operator=(ThreadGuard const &)=delete;
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
    thread t(do_some_work);
    ThreadGuard tg(t); 
    return 0;
} 
