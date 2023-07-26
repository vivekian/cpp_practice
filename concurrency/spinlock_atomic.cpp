#include <iostream> 
#include <memory> 
#include <thread> 

/* When it comes down to it, the primary reason for using lock-free data structures is to enable maximum concurrency. With lock-based containers, there’s always the poten- tial for one thread to have to block and wait for another to complete its operation before the first thread can proceed; preventing concurrency through mutual exclu- sion is the entire purpose of a mutex lock. With a lock-free data structure, some thread makes progress with every step. With a wait-free data structure, every thread can make forward progress, regardless of what the other threads are doing; there’s no need for waiting. This is a desirable property to have but hard to achieve. It’s all too easy to end up writing what’s essentially a spin lock. */ 

class AtomicSpinLock { 
  std::atomic_flag flag; 
  public: 
  AtomicSpinLock(): flag(false) {} 
  
  void lock() { 
    while(flag.test_and_set(std::memory_order_acquire)); 
  }

  void unlock() { 
    flag.clear(std::memory_order_release); 
  }  
};

typedef struct data { 
  bool ready = true; 
  AtomicSpinLock spin_lock; 
} data; 

namespace { 
  data d; 
}

void foo() { 
  d.spin_lock.lock(); 
  std::cout << "foo" << std::endl; 
  d.spin_lock.unlock(); 
} 

void bar() { 
  d.spin_lock.lock(); 
  std::cout << "bar" << std::endl; 
  d.spin_lock.unlock(); 
} 

int main() { 
  std::thread t2(bar); 
  std::thread t1(foo); 
  t1.join(); 
  t2.join(); 
} 
