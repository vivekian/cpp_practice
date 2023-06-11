#include <iostream> 

template<class T> 
void double_each_element(T& arr) { 
  for (unsigned long i=0; i<arr.size(); ++i) { 
    arr.at(i) *= 2; 
  } 
} 

template<class Container, class Predicate> 
int count_if(const Container& container, Predicate pred) { 
  int cnt = 0; 
  for (auto&& elt : container) { 
    if (pred(elt)) { 
      ++cnt; 
    } 
  } 
  return cnt; 
} 

int main() { 
  std::vector<int> veci = {1, 2, 3, 4}; 
  const std::vector<int> veci_double = {2, 4, 6, 8};
  double_each_element(veci); 
  assert(veci == veci_double); 
  assert(count_if(veci, [](int x) { return x == 2; }) == 1); 
  return 0; 
} 
