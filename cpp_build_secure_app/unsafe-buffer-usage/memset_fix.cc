#include <algorithm>
#include <print>
#include <span>

// C++23
void Print(std::span<int, 4> sp) {
  std::println("{} {} {} {}", sp[0], sp[1], sp[2], sp[3]);
}

int main() {
  int arr[4]{};
  // Attempt to set each element in array 1.
  std::ranges::fill(arr, 1);
  Print(arr);
}

// 1 1 1 1
