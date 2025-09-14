#include <string>

// The calls to string functions will all "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used, this will work fine.

void ProblemString(std::string s) {
  // Will flag when called with first > last.
  s.erase(s.end(), s.begin());
}

int main() {
  std::string s("hello");
  ProblemString(s);
}