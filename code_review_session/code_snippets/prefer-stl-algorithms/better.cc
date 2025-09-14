#include <algorithm>
#include <iostream>
#include <span>

bool HasInterestingNumber(std::span<const int> sp) {
  return std::ranges::any_of(sp, [](const auto i) { return i % 3 == 0; });
}

int main() {
  constexpr std::array kArr{1, 2, 3, 4, 5};
  std::cout << std::boolalpha << HasInterestingNumber(kArr) << '\n';
}

// true