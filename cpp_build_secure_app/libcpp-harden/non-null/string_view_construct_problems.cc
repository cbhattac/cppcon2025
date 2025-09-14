#include <iostream>
#include <string_view>

// The calls to string_view functions will all "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used it may crash with SIGSEGV.

void ProblemStringView(const char* p) {
  // Will flag if p is nullptr.
  std::string_view s{p};
  std::cout << s << '\n';
}

void ProblemStringView2(const char* p, size_t n) {
  // Will flag if p is nullptr and n != 0.
  std::string_view s{p, n};
  std::cout << s << '\n';
}

int main() {
  std::string_view sv;
  ProblemStringView(sv.data());
  ProblemStringView2(sv.data(), 1u);
}