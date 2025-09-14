#include <expected>
#include <iostream>

// The calls to string functions will all "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used, then with clang `-std=c++23
// -stdlib=libc++ -O3` it runs and prints the following:
/*
*e: 1
e->operator(): 0x7fffc626f4b8
e.error(): 0
*/

void ProblemExpected(std::expected<int, int> e) {
  // Will flag when called with "error" object.
  std::cout << "*e: " << *e << '\n';
  // Will flag when called with "error" object.
  std::cout << "e->operator(): " << (void*)e.operator->() << '\n';
}

void ProblemUnexpected(std::expected<int, int> e) {
  // Will flag when called with "success" object.
  std::cout << "e.error(): " << e.error() << '\n';
}

int main() {
  ProblemExpected(std::unexpected{1});
  ProblemUnexpected({});
}
