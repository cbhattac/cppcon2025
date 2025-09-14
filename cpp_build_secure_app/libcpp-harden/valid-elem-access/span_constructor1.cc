#include <array>
#include <span>
#include <utility>

int main() {
  constexpr std::array kArr{10, 20, 30, 40, 50, 60};

  // ❌ This line will cause the program to abort with an assertion failure.
  // on using _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE

  // We declare a span that MUST have 5 elements (`std::span<int, 5>`).
  // However, we then try to construct it with a different count (3).
  // This violates the span's static extent contract.
  std::span<const int, 5> my_span(kArr.begin(), 3);
  std::ignore = my_span;

  // Code below this line will not be reached in a debug build.
  return 0;
}
