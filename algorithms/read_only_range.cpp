#include <algorithm>
#include <iostream>
#include <vector>

int main() { 
  std::vector v = {9, 8, 1, 2, 3, 5, 7};
  // count of numbers divisible by 2.  
  auto cnt = std::count_if(begin(v), end(v), [](int x) { return !(x % 2); }); 
  std::cout << cnt << std::endl; 
  return 0; 
}
