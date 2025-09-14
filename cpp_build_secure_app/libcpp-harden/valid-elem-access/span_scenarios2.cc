#include <array>
#include <span>
#include <string_view>
#include <utility>
#include <vector>

void FirstFixedCountCrash() {
  const std::vector vec{10, 20, 30};
  const std::span my_span{vec};
  // This violates the assertion:
  // _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(_Count <= size(),
  // "span<T>::first<Count>(): Count out of range");
  // The following line will cause the assertion failure and terminate the
  // program.
  [[maybe_unused]] const auto v = my_span.first<4>();
}

void LastFixedCountCrash() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span my_span{vec};
  // This violates the assertion:
  // _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(_Count <= size(),
  // "span<T>::last<Count>(): Count out of range");
  // The following line will cause the assertion failure and terminate the
  // program.
  [[maybe_unused]] const auto v = my_span.last<6>();
}

void FirstDynamicCountCrash() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span my_span{vec};
  // This violates the assertion:
  // _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(__count <= size(),
  // "span<T>::first(count): count out of range");
  [[maybe_unused]] const auto v = my_span.first(6);
}

void LastDynamicCountCrash() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span my_span{vec};
  // This violates the assertion:
  // _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(__count <= size(),
  // "span<T>::last(count): count out of range");
  [[maybe_unused]] const auto v = my_span.last(6);
}

void SubspanFixedOffsetCountCrashOffset() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span my_span{vec};
  // This violates the assertion:
  // _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(_Offset <= size(),
  // "span<T>::subspan<Offset, Count>(): Offset out of range");
  [[maybe_unused]] const auto v = my_span.subspan<6>();
}

void SubspanFixedOffsetCountCrashOffsetPlusCount() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span my_span{vec};
  // This violates the assertion:
  // _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(_Count == dynamic_extent || _Count <=
  // size() - _Offset,
  //                                      "span<T>::subspan<Offset, Count>():
  //                                      Offset + Count out of range");
  [[maybe_unused]] const auto v = my_span.subspan<4, 3>();
}

void SubspanDynamicOffsetCountCrashOffset() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span my_span{vec};
  // This violates the assertion:
  // _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(__offset <= size(),
  // "span<T>::subspan(offset, count): offset out of range");
  [[maybe_unused]] const auto v = my_span.subspan(6);
}

void SubspanDynamicOffsetCountCrashOffsetPlusCount() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span my_span{vec};
  // This violates the assertion:
  // _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(__count <= size() - __offset,
  // "span<T>::subspan(offset, count): offset + count out of range");
  [[maybe_unused]] const auto v = my_span.subspan(1, 5);
}

void OperatorSquareBracketsCrash() {
  const std::vector vec{1, 2, 3, 4, 5};
  const std::span my_span{vec};
  // This violates the assertion:
  // _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(__idx < size(),
  // "span<T>::operator[](index): index out of range");
  [[maybe_unused]] const int value = my_span[5];
}

void FrontCrash() {
  const std::vector<int> vec;
  const std::span my_span{vec};
  // This violates the assertion:
  // _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(!empty(), "span<T>::front() on empty
  // span");
  [[maybe_unused]] const int value = my_span.front();
}

void BackCrash() {
  const std::vector<int> vec;
  const std::span my_span{vec};
  // This violates the assertion:
  // _LIBCPP_ASSERT_VALID_ELEMENT_ACCESS(!empty(), "span<T>::back() on empty
  // span");
  [[maybe_unused]] const int value = my_span.back();
}

int main(int argc, char* argv[]) {
  // Each of these functions will cause the program to abort when built with
  // -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE
  // Example usage: span_scenarios2.exe FirstFixedCountCrash
  const std::string_view opt = argc > 1 ? argv[1] : std::string_view{};
  if (opt == "FirstFixedCountCrash") {
    FirstFixedCountCrash();
  } else if (opt == "LastFixedCountCrash") {
    LastFixedCountCrash();
  } else if (opt == "FirstDynamicCountCrash") {
    FirstDynamicCountCrash();
  } else if (opt == "LastDynamicCountCrash") {
    LastDynamicCountCrash();
  } else if (opt == "SubspanFixedOffsetCountCrashOffset") {
    SubspanFixedOffsetCountCrashOffset();
  } else if (opt == "SubspanFixedOffsetCountCrashOffsetPlusCount") {
    SubspanFixedOffsetCountCrashOffsetPlusCount();
  } else if (opt == "SubspanDynamicOffsetCountCrashOffset") {
    SubspanDynamicOffsetCountCrashOffset();
  } else if (opt == "SubspanDynamicOffsetCountCrashOffsetPlusCount") {
    SubspanDynamicOffsetCountCrashOffsetPlusCount();
  } else if (opt == "OperatorSquareBracketsCrash") {
    OperatorSquareBracketsCrash();
  } else if (opt == "FrontCrash") {
    FrontCrash();
  } else if (opt == "BackCrash") {
    BackCrash();
  }
}
