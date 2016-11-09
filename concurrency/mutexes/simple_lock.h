#include <atomic> 

class SimpleLock
{ 
    public:
        SimpleLock() {} 
        ~SimpleLock() 
        { 
            flag.clear(); 
        } 
  
        void lock() 
        { 
            while(flag.test_and_set() == true); 
        } 

        void unlock() 
        { 
            flag.clear(); 
        }   
    
    private: 
        std::atomic_flag flag;
};  
