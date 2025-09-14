#include <algorithm>
#include <iostream>
#include <span>

// clang-tidy check: none
// Clang-C++ warning: none
bool HasInterestingNumber(std::span<const int> sp) {
  for (const auto i : sp) {
    if (i % 3 == 0) {
      return true;
    }
  }
  return false;
}

int main() {
  constexpr std::array kArr{1, 2, 3, 4, 5};
  std::cout << std::boolalpha << HasInterestingNumber(kArr) << '\n';
}

// true