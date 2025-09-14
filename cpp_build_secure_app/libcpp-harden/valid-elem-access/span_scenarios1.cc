#include <array>
#include <span>
#include <utility>
#include <vector>

void CrashFirst() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span s(vec);
  // Expected crash: _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(__count <= size(),
  // "span<T, N>::first(count): count out of range");
  std::ignore = s.first(7);  // 7 > s.size() (5)
}

void CrashLast() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span s(vec);
  // Expected crash: _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(__count <= size(),
  // "span<T, N>::last(count): count out of range");
  std::ignore = s.last(7);  // 7 > s.size() (5)
}

void CrashSubspanInvalidOffset() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span s(vec);
  // Expected crash: _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(__offset <= size(),
  // "span<T, N>::subspan(offset, count): offset out of range");
  std::ignore = s.subspan(6);  // 6 > s.size() (5)
}

void CrashSubspanInvalidCount() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span s(vec);
  // Expected crash: _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(__count <= size() -
  // __offset, "span<T, N>::subspan(offset, count): offset + count out of
  // range");
  std::ignore = s.subspan(3, 4);  // 3 + 4 = 7; 7 > s.size() (5)
}

void CrashOperatorBracket() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span s(vec);
  // Expected crash: _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(__idx < size(),
  // "span<T, N>::operator[](index): index out of range");
  std::ignore = s[5];  // 5 >= s.size() (5)
}

void CrashFront() {
  const std::vector<int> vec;
  const std::span s(vec);
  // Expected crash: _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(!empty(), "span<T,
  // N>::front() on empty span");
  std::ignore = s.front();
}

void CrashBack() {
  const std::vector<int> vec;
  const std::span s(vec);
  // Expected crash: _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(!empty(), "span<T,
  // N>::back() on empty span");
  std::ignore = s.back();
}

int main() {
  // Each of these functions will cause the program to abort when built with
  // -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE
  CrashFirst();
  CrashLast();
  CrashSubspanInvalidOffset();
  CrashSubspanInvalidCount();
  CrashOperatorBracket();
  CrashFront();
  CrashBack();
}
