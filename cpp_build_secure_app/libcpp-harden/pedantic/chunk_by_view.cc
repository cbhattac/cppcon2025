#include <iostream>
#include <ranges>
#include <vector>

// C++23.

int main() {
  std::vector<int> v = {1, 1, 2, 2, 3};
  auto view =
      std::ranges::chunk_by_view(v, [](int a, int b) { return a == b; });
  auto it = view.begin();
  // Try to decrement at the beginning (this should fire the assertion in
  // libc++)
  --it;  // This will trigger the assertion if assertions are enabled
  std::cout << "This line will not be reached if assertions are enabled!\n";
}