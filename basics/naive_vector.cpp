#include <algorithm> 
#include <utility> 
#include <unistd.h>

template<typename T> 
class NaiveVector {
  int* ptr_;
  size_t size_;

 public:
  NaiveVector() : ptr_(nullptr), size_(0){};
  ~NaiveVector() { delete[] ptr_; }
  NaiveVector(const NaiveVector& rhs) {
   if (&rhs != this) {  
    delete[] ptr_; 
    ptr_ = new T(rhs.size);  
    size_ = rhs.size; 
    // copy items in the container. 
    std::copy(rhs.ptr_, rhs.ptr_ + size_, ptr_);
   }
  } 

  void swap(NaiveVector& rhs) { 
    std::swap(rhs.ptr_, this->ptr_); 
    std::swap(rhs.size_, this->size_); 
  }

  NaiveVector& operator=(const NaiveVector& rhs) { 
    // this invokes the copy constructor 
    NaiveVector copy = rhs; 
    swap(copy); 
  } 
};

