#include <unistd.h>

#include <algorithm>
#include <utility>

template <typename T>
class NaiveVector {
  int* ptr_ = nullptr;
  size_t size_ = 0;
  size_t cap_ = 0; 

  void destroy_n_elements(T* p, size_t n) {
    for (size_t i = 0; i < n; ++i) {
      p[i].~T();
    }
  }

 public:
  NaiveVector() : ptr_(nullptr), size_(0){};

  ~NaiveVector() {
    destroy_n_elements(ptr_, size_);
    delete[] ptr_;
  }

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

  void reserve(size_t c) { 
    if (c < cap_) { 
      return; 
    }
     
    // allocate new memory
    auto new_ptr = new T[c * sizeof(T)]; 
    // std::copy old data into new memory 
    for (size_t i=0; i<size_; ++i) { 
      new_ptr[i] = ptr_[i]; 
    } 
    // free up old memory  
    destroy_n_elements(ptr_, size_); 
    delete[] ptr_; 
    cap_ = c; 
  } 
};

