#include <iostream>
#include <ranges>
#include <vector>

// Use std::ranges algorithms for clarity and safety.
void PrintSorted(std::vector<int> v) {
  std::ranges::sort(v);
  for (int x : v) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::vector<int> v = {3, 1, 2};
  PrintSorted(v);
}
