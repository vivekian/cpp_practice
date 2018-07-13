#include <condition_variable>
#include <iostream> 
#include <mutex>
#include <thread> 

using namespace std; 

void prep_work() 
{
   printf("prep work\n");  
}

void main_work() 
{
   std::this_thread::sleep_for(100ms); 
   printf("main work\n");  
}

int main()
{
    bool ready = false; 
    mutex ready_mutex; 
    condition_variable cv; 

    thread thread_b([&]() { 
            prep_work(); 
            {
                lock_guard<mutex> lk(ready_mutex); 
                ready = true; 
            }
            cv.notify_one();    
            main_work(); 
    });


    unique_lock<mutex> ul(ready_mutex); 
    cv.wait(ul, [&ready]() { return ready;});
    printf("no more waiting\n"); 
    thread_b.join();
    return 0;  
}
