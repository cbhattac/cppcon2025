#include <iostream>
#include <string>

// The calls to char_traits::copy will all "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used, this will work fine and print:
// elloo

int main() {
  std::string s("hello");
  std::string_view sv(s);
  std::string_view sub = sv.substr(1);
  // Will flag if sub overlaps with s.
  std::char_traits<char>::copy(s.data(), sub.data(), sub.size());
  std::cout << s << '\n';
}