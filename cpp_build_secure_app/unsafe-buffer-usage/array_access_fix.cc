#include <array>
#include <iostream>
#include <span>

void Print(std::span<const int> sp) {
  for (const auto elem : sp) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main() {
  const int arr[]{1, 2, 3, 4, 5};
  Print(arr);
}

// Output:
// 1 2 3 4 5
