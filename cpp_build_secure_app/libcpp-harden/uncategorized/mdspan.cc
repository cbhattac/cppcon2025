#include <limits>
#include <mdspan>

// C++23.

int main() {
  // Pick two large extents whose product is greater than size_t max
  const size_t e1 = std::numeric_limits<size_t>::max();
  const size_t e2 = 2u;

  // Create an mdspan with those extents
  int data[] = {0};
  std::mdspan<int, std::dextents<size_t, 2>> m(data, e1, e2);
  // This will trigger the assert in size(), due to overflow
  [[maybe_unused]] const auto s = m.size();  // <--- assert fires here!
}