#include <array>
#include <iostream>
#include <span>

void Print(std::span<const int> sp) {
  for (const auto elem : sp) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

// Callback from a C-library.
void UnsafeCallback(const int* arr, size_t n) {
  Print(std::span{arr, n});
}

int main() {
  const int arr[]{1, 2, 3, 4, 5};
  UnsafeCallback(arr, std::size(arr));
}

// 1 2 3 4 5

// With -Wunsafe-buffer-usage, this will produce:
/*
error: the two-parameter std::span construction is unsafe as it can introduce mismatch between buffer size and the bound information [-Werror,-Wunsafe-buffer-usage-in-container]
   Print(std::span{arr, n});
         ^
*/
