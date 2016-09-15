
#include <iostream> 
#include <thread> 

void do_some_work_and_join()
{ 
    std::cout << "do some work and join" << std::endl; 
} 

void do_some_work_and_detach()
{ 
    std::cout << "do some work and detach" << std::endl; 
} 

void launch_and_join() 
{ 
    // creating a thread is as simple as creating an object 
    std::thread thread1(do_some_work_and_join);
    thread1.join();
}

void launch_and_detach()
{ 
    std::thread thread1(do_some_work_and_detach);
    thread1.detach();
}

int main(int argc, char* argv[]) 
{
    launch_and_join();
    launch_and_detach(); 
    return 0;
} 


