#include <iostream> 

using namespace std; 

struct ControlBlock { 
  // ref counting
  size_t ref_cnt = 0;  
  // custom deleters 
}; 

template <typename T> 
class SharedPointer { 
  private:
    T* ptr_; 
    ControlBlock* blk_; 
  public: 

  // constructor 
  // args -> pointer to T 
  SharedPointer (T* ptr): ptr_(ptr) { 
    blk_ = new ControlBlock; 
    blk_->ref_cnt++; 
  } 
  
  // destructor 
  ~SharedPointer() { 
    // decrement ref_cnt
    blk_->ref_cnt--;  
    // if ref_cnt = 0, free ptr_ and release blk_ 
    if (blk_->ref_cnt == 0) { 
      delete ptr_; 
      delete blk_;  
    }  
  } 

  // SharePointer<int> pb(pa); 
  // copy constructor 
  SharedPointer(const SharedPointer<T>& rhs) { 
    this->ptr_ = rhs.ptr_; 
    this->blk_ = rhs.blk_; 
    blk_->ref_cnt++; 
  } 
  
  // assignment operator 
  SharedPointer& operator=(const SharedPointer<T>& rhs) { 
    if (rhs != this) { 
      release(); 
      this->ptr_ = rhs.ptr_; 
      this->blk_ = rhs.blk_; 
      blk_->ref_cnt++; 
    } 
    return *this; 
  } 

  // move constructor 
  SharedPointer(SharedPointer&& rhs) { 
    this->ptr_ = rhs.ptr_; 
    this->blk->ref_cnt_ = 1; 
    rhs.ptr_ = nullptr; 
    rhs.blk_cnt->ref_cnt = 0; 
  } 

  // move assignment operator 
 
  // get(); 
  T* get() { 
    return ptr_; 
  } 

  // release(); 
  T* release() { 
    blk_->ref_cnt = 0; 
    auto ret = ptr_; 
    delete ptr_; 
    return ret; 
  }

  void reset(T* newPtr=nullptr) { 
    release(); 
    ptr_ = newPtr; 
    blk_->ref_cnt = 1; 
  } 
}; 

int main() { 
  SharedPointer<int> pa(new int(2)); 
  std::cout << *pa.get() << std::endl; 
  SharedPointer<int> pb = pa; 
  std::cout << *pb.get() << std::endl; 
  return 0; 
} 
