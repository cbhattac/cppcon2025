#include <span>
#include <utility>
#include <vector>

int main() {
  const std::vector vec{1, 2, 3};

  // ❌ This line will cause the program to abort with an assertion failure.
  // on using _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE

  // Expected crash: _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(ranges::size(__r) ==
  // _Extent, "size mismatch in span's constructor (range)");
  std::span<const int, 5> fixed_span(vec);  // arr.size() (3) != _Extent (5)
  std::ignore = fixed_span;
}
