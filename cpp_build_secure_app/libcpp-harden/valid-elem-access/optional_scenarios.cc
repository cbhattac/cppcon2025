#include <iostream>
#include <optional>

// The calls to string functions will all "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used, then with clang `-std=c++20
// -stdlib=libc++ -O3` it runs and prints the following:
/*
*o: 0
o->operator(): 0x7ffd14d77ac8
*/

void ProblemOptional(std::optional<int> o) {
  // Will flag when called with empty optional.
  std::cout << "*o: " << *o << '\n';
  // Will flag when called with empty optional.
  std::cout << "o->operator(): " << (void*)(o.operator->()) << '\n';
}

int main() {
  ProblemOptional({});
}