#include <algorithm>
#include <iostream>
#include <vector>

// clang-tidy check: modernize-use-ranges
// Clang-C++ warning: none

// Using classic std algorithms with iterators.
void PrintSorted(std::vector<int> v) {
  std::sort(v.begin(), v.end());
  for (int x : v) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::vector<int> v = {3, 1, 2};
  PrintSorted(v);
}

// 1 2 3
// -checks=modernize-use-ranges
/*
warning: use a ranges version of this algorithm [modernize-use-ranges]
   std::sort(v.begin(), v.end());
   ^~~~~~~~~ ~~~~~~~~~  ~~~~~~~
   std::ranges::sort v
*/
