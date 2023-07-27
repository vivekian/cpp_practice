// write your own memory allocator based on K&R
// there are multiple approaches to be discussed in general:
//    variable sized block allocation, fixed sized blocks (buddy allocator or
//    memory pool) also consider slab allocation techniques which pre-allocate
//    objects and dish them out. how to do error handling? what kind of approach
//    to be used for finding the right block of memory?
//      first fit, best fit, or
//    can we assume that this is a fixed size of memory block.
//    API discussion
//      void* malloc(size_t size)
//      void free(void* ptr)

#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

#include <iostream>

typedef struct block { 
  struct block* next; 
  ssize_t size; 
} block;  

class Allocator {
  size_t size_;
  block* head_;

 public:
  Allocator(size_t size) : size_(size) {}
  ~Allocator() { 
  } 

  int mem_init() {
    head_ = static_cast<block*>(mmap(nullptr, size_, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
                -1, 0));
    if (head_ == MAP_FAILED) { 
      std::cerr << "memory allocation failed"; 
      return -1; 
    } 
  
    // initialize the first block 
    head_->size = size_ - sizeof(block); 
    head_->next = nullptr; 
    return 0;
  }

  void* alloc(size_t size) {
    // iterate the free block list and find the first block which fits the required size 
    //    required_size = size + sizeof(block) 
    //    split the block: 
    //       the original block's size is reduced to the remaining size 
    //       create a new block which will hold the size of the required size 
    //    return the allocated memory 
    // no block is available, return nullptr
    block* curr = head_; 
    block* prev = nullptr; 
    ssize_t required_size = size + sizeof(block); 
    
    while (curr) { 
      if (curr->size >= required_size) { 
        if (curr->size == required_size) { 
          prev->next = curr->next; 
          return (curr+1); 
        } 
        curr->size -= required_size; 
        char* ptr = reinterpret_cast<char*>(curr) + sizeof(block) + curr->size; 
        block* newblock = reinterpret_cast<block*>(ptr); 
        newblock->size = size; 
        return (newblock+1); 
      } 
      prev = curr; 
      curr = curr->next;  
    }

    return nullptr; 
  }

  block* find_free_block(block* freeblock) { 
  } 

  
  void free(void* ptr) { 
    // access the header of the block by decrementing 1 
    // find where the block is in the free list 
    //    edge case 1: start of the free list 
    //    edge case 2: end of the free list 
    // insert the block in the free list 
    //    the previous block's pointer should point to the new block 
    //    freed block's pointer should point to the next free block 
    // coalescing: 
    //    check previous ngbr - if contagious then combine 
    //    check next ngbr -if contagious then combine
    block* freeblock = static_cast<block*>(ptr) - 1; 
    block* curr = head_; 
    block* prev = nullptr; 
  } 
};

int main() { 
  Allocator allocator(4096); 
  allocator.mem_init(); 
  void* p1 = allocator.alloc(100); 
  void* p2 = allocator.alloc(100); 
  void* p3 = allocator.alloc(100); 

  std::cout << static_cast<char*>(p2) - static_cast<char*>(p1) << std::endl; 

  return 0; 
} 
