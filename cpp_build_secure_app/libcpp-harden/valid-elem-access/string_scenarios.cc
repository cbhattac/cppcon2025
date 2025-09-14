#include <iostream>
#include <string>

// The calls to string functions will all "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used, then with clang `-std=c++20
// -stdlib=libc++ -O3` it runs and prints the following:
/*
s.front():
s.back():
s[3]:
(it != s.end()): 0
*/

void ProblemString(std::string s) {
  // Will fire when called on empty string.
  const auto f = s.front();
  std::cout << "s.front(): " << f << '\n';
  // Will fire when called on empty string.
  const auto b = s.back();
  std::cout << "s.back(): " << b << '\n';
  // Will fire when called on empty string.
  s.pop_back();
  s += "ab";
  //  Will fire when called with index out of range.
  std::cout << "s[3]: " << s[3] << '\n';
  //  Will fire when called with end().
  auto it = s.erase(s.end());
  std::cout << "(it != s.end()): " << (it != s.end()) << '\n';
}

int main() {
  ProblemString({});
}
