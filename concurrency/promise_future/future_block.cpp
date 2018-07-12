#include <chrono> 
#include <future> 
#include <iostream> 
#include <string> 
#include <thread> 
#include <vector>

using namespace std; 
using namespace chrono;

int main()
{
    promise<int> p1, p2; 
    future<int> f1 = p1.get_future(); 
    future<int> f2 = p2.get_future(); 

    p1.set_value(42); 
    assert(f1.get() == 42); 

    thread t([&p2]() { 
        this_thread::sleep_for(100ms);
        p2.set_value(43); 
    });

    auto start_time = system_clock::now(); 
    assert(f2.get() == 43); 
    auto elapsed = system_clock::now(); 

    printf("f2.get() took %dms\n", 
            static_cast<int>(duration_cast<milliseconds>(elapsed-start_time).count()));

    t.join();
    return 0;  
}
