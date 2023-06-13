#include <iostream>
#include <utility>

template <typename T>
class UniquePtr {
 private:
  T* m_ptr;

 public:
  // constructor
  explicit UniquePtr(T* ptr = nullptr) : m_ptr(ptr) {}
  // destructor
  ~UniquePtr() {
    delete m_ptr;
    m_ptr = nullptr;
  }
  // disable the copy constructor
  UniquePtr(const UniquePtr& rhs) = delete;
  // disable the assignment operator
  UniquePtr& operator=(UniquePtr& rhs) = delete;
  // move constructor
  UniquePtr(UniquePtr&& rhs) { m_ptr = std::exchange(rhs.m_ptr, nullptr); }
  // move assignment operator
  UniquePtr& operator=(UniquePtr&& rhs) noexcept {
    if (&rhs != this) {
      delete m_ptr;
      m_ptr = std::exchange(rhs.m_ptr, nullptr);
    }
    return *this;
  }
  // get() function
  T* get() { return m_ptr; }
  // reset() function
  void reset(T* ptr) {
    if (m_ptr) delete m_ptr;
    m_ptr = ptr;
  }
};

int main() { 
  UniquePtr<int> up(new int(42)); 
  UniquePtr<int> foo(std::move(up)); 
  std::cout << up.get() << std::endl; 
  std::cout << foo.get() << std::endl; 
  UniquePtr<int> bar(nullptr);
  bar = std::move(foo);  
  std::cout << bar.get() << std::endl; 
  return 0; 
} 

