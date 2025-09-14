#include <algorithm>
#include <initializer_list>
#include <iostream>

// The calls to string functions will all "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used, then with clang `-std=c++20
// -stdlib=libc++ -O3` each may crash with SIGSEGV.

void ProblemMinMax() {
  std::initializer_list<int> l{};
  // Will flag for empty range being passed.
  const auto [min, max] = std::ranges::minmax(l);
  std::cout << "l: min: " << min << ", max: " << max << '\n';
}

void ProblemMin() {
  std::initializer_list<int> l{};
  // Will flag for empty range being passed.
  const auto min = std::ranges::min(l);
  std::cout << "min: " << min << '\n';
}

void ProblemMax() {
  std::initializer_list<int> l{};
  // Will flag for empty range being passed.
  const auto max = std::ranges::max(l);
  std::cout << "max: " << max << '\n';
}

int main() {
  ProblemMinMax();
  ProblemMin();
  ProblemMax();
}
