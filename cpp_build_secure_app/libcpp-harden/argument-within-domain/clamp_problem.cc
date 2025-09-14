#include <algorithm>
#include <iostream>

// The call to std::clamp functions will all "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used, this will work fine and print:
// 1

int main() {
  // Will flag when hi < lo.
  const auto v = std::clamp(10, 2, 1);
  std::cout << v << '\n';
}