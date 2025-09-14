#include <algorithm>
#include <iostream>
#include <vector>

// The calls to pop_heap will "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used, this will work fine.

int main() {
  std::vector<int> v;
  std::ranges::make_heap(v);
  // Will flag when called with empty range.
  std::ranges::pop_heap(v);
}