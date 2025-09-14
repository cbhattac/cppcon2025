#include <forward_list>
#include <iterator>
#include <ranges>
#include <vector>

int main() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  // To fire the assertion, use a forward iterator, which cannot go backwards!
  auto fit = v.begin();
  std::ranges::advance(
      fit,
      -1);  // This is OK for random-access/bidirectional, but would not fire

  // To truly fire the assertion, let's use a forward iterator (e.g.,
  // std::forward_list)
  std::forward_list<int> fl = {1, 2, 3, 4, 5};
  auto fl_it = fl.begin();

  // This will fire the assert in libc++ because std::forward_list's iterator is
  // not bidirectional with
  // _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE. Otherwise, no
  // error.
  std::ranges::advance(fl_it, -1);  // std::forward_list<int>::iterator is a
                                    // forward iterator, not bidirectional!
}
