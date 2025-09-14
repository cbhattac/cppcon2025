#include <forward_list>
#include <iterator>  // for std::advance

int main() {
  std::forward_list<int> flist = {1, 2, 3};
  auto it = flist.begin();
  // This will fire the assert in libc++ because std::forward_list's iterator is
  // not bidirectional with
  // _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE. Otherwise, no
  // error.
  std::advance(it, -1);
}