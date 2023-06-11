#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector v = {9, 8, 1, 2, 3, 5, 7};
  // count of numbers divisible by 2.
  auto cnt = std::count_if(begin(v), end(v), [](int x) { return !(x % 2); });
  std::cout << cnt << std::endl;
  auto itr = std::find_if(begin(v), end(v), [](int x) { return x == 3; });
  std::cout << *itr << std::endl;
  std::string s = "hello";
  std::vector<char> dest;
  std::copy(s.begin(), s.end(), std::back_inserter(dest));
  assert(dest.size() == 5);
  return 0;
}
