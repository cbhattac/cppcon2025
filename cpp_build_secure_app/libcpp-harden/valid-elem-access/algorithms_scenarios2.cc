#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <random>
#include <vector>

// The calls to string functions will all "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used, then with clang `-std=c++20
// -stdlib=libc++ -O3` it may crash with SIGSEGV.

int main() {
  const auto in = {1, 2, 3, 4, 5, 6};
  std::vector<int> out;
  auto gen = std::mt19937{std::random_device{}()};
  // Passing negative sample size will flag.
  std::ranges::sample(in, std::back_inserter(out), -1, gen);
}