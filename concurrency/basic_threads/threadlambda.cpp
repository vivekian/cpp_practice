
#include <iostream> 
#include <thread> 

void do_some_work_and_join()
{ 
    std::cout << "do some work and join" << std::endl; 
} 

void launch_and_join() 
{ 
    std::thread thread1( [] {
        do_some_work_and_join();
    });
    thread1.join();
}

int main(int argc, char* argv[]) 
{
    launch_and_join();
    return 0;
} 


