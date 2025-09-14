#include <array>
#include <iostream>
#include <span>

void Print(std::span<const int> sp) {
  for (const auto elem : sp) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

template <typename T>
auto MakeSpan(const T* arr, size_t n) {
#pragma clang unsafe_buffer_usage begin
  return std::span{arr, n};
#pragma clang unsafe_buffer_usage end
}

// Callback from a C-library.
[[clang::unsafe_buffer_usage]] void UnsafeCallback(const int* arr, size_t n) {
  Print(MakeSpan(arr, n));
}

int main() {
  const int arr[]{1, 2, 3, 4, 5};
#pragma clang unsafe_buffer_usage begin
  UnsafeCallback(arr, std::size(arr));
#pragma clang unsafe_buffer_usage end
}

// 1 2 3 4 5
