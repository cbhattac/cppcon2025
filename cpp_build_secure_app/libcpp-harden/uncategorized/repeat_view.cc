#include <ranges>
#include <string_view>
#include <tuple>

// C++23

void Test1() {
  // repeat_view<int, int>
  // Bound is int, not unreachable_sentinel_t
  // Pass a negative bound to trigger assert
  [[maybe_unused]] std::ranges::repeat_view<int, int> rv(
      42, -5);  // Assertion fires: bound < 0
}

void Test2() {
  int value = 10;
  [[maybe_unused]] std::ranges::repeat_view<int, int> rv(
      std::move(value),
      -3);  // Assertion fires: bound < 0
}

void Test3() {
  // Piecewise construct with negative bound
  [[maybe_unused]] std::ranges::repeat_view<int, int> rv(
      std::piecewise_construct, std::make_tuple(99),
      std::make_tuple(-1)  // Assertion fires: bound < 0
  );
}

int main(int argc, char** argv) {
  const auto name = argc > 1 ? std::string_view{argv[1]} : std::string_view{};
  if (name == "Test1") {
    Test1();
  } else if (name == "Test2") {
    Test2();
  } else if (name == "Test3") {
    Test3();
  }
  return 0;
}