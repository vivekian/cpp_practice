#include <queue> 
#include <iostream> 
#include <thread>

std::queue<uint32_t> q; 

void reader()
{
   while(!q.empty()) 
   { 
       std::cout << q.front() << std::endl; 
       q.pop(); 
   }
} 

void writer()
{ 
    for (uint32_t i=10; i<10000000; ++i) { 
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


