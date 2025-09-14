#include <forward_list>
#include <ranges>

int main() {
  std::forward_list<int> l{1, 2, 3, 4};
  auto start_it = l.begin();
  // This will fire the assert in libc++ because std::forward_list's iterator is
  // not bidirectional with
  // _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE. Otherwise, no
  // error.
  std::ranges::advance(start_it, -1, l.end());
}