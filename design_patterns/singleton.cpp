#include <atomic> 
#include <iostream> 
#include <thread>

class Singleton 
{ 
    public: 
    static Singleton& Instance() 
    { 
        static Singleton s; 
        return s; 
    }
   
    private: 
    Singleton() { std::cout << "Initialized" << std::endl; } 
    ~Singleton() = default; 

    Singleton(const Singleton&) = delete; 
    Singleton& operator=(const Singleton&) = delete; 
}; 

void foo()
{ 
    Singleton& s = Singleton::Instance();
} 

int main() 
{ 
    std::thread first(foo); 
    std::thread second(foo); 
    std::thread third(foo); 

    first.join(); 
    second.join(); 
    third.join(); 
} 

