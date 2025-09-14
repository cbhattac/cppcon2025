#include <iostream>
#include <string>

// The calls to string functions will all "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used it may crash with SIGSEGV.

void ProblemString(const char* p) {
  // Will flag if p is nullptr.
  std::string s{p};
  std::cout << s << '\n';
}

void ProblemString2(const char* p, size_t n) {
  // Will flag if p is nullptr and n != 0.
  std::string s{p, n};
  std::cout << s << '\n';
}

int main() {
  std::string_view sv;
  ProblemString(sv.data());
  ProblemString2(sv.data(), 1u);
}