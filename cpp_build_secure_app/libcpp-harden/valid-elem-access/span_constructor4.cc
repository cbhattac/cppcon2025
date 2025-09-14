#include <span>
#include <utility>
#include <vector>

int main() {
  const std::vector<int> vec = {10, 20, 30, 40};
  std::span<const int> dynamic_span(vec);  // dynamic_extent

  // ❌ This line will cause the program to abort with an assertion failure.
  // on using _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE

  // Expected crash: _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(_Extent ==
  // __other.size(), "size mismatch in span's constructor (other span)");
  std::span<const int, 2> fixed_span_from_dynamic(
      dynamic_span);  // _Extent (2) != __other.size() (4)
  std::ignore = fixed_span_from_dynamic;
}
