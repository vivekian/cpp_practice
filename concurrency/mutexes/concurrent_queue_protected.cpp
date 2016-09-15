#include <queue> 
#include <iostream> 
#include <thread>
#include <mutex> 

std::mutex queue_mutex; 

std::queue<uint32_t> q; 

void reader()
{
   while(!q.empty()) 
   { 
       std::lock_guard<std::mutex> lg(queue_mutex);     // lock implicitely  
       std::cout << q.front() << std::endl; 
       q.pop(); 
       // lock is release implicitely on destruction
   }
} 

void writer()
{ 
    for (uint32_t i=10; i<10000; ++i) { 
        std::lock_guard<std::mutex> lg(queue_mutex);   // lock implicitely
        q.emplace(i); 
    }
} 

void launch_reader_and_writer() 
{ 
    std::thread wr(writer);
    std::thread rd(reader);

    wr.join(); 
    rd.join(); 
}

int main(int argc, char* argv[]) 
{
    for (uint32_t i=0; i<10; ++i) 
        q.emplace(i); 

    launch_reader_and_writer(); 
    return 0;
} 


