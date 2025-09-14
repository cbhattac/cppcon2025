#include <array>
#include <iostream>

void Print(const int* arr, size_t len) {
  for (size_t i = 0; i <= len; ++i) {
    std::cout << arr[i] << ' ';
  }
  std::cout << '\n';
}

int main() {
  const int arr[]{1, 2, 3, 4, 5};
  Print(arr, std::size(arr));
}

// Output with clang (-O3):
// 1 2 3 4 5 392233686

// Output with GCC (-O3):
1 2 3 4 5 0 

// With -Wunsafe-buffer-usage
/*
error: unsafe buffer access [-Werror,-Wunsafe-buffer-usage]
     std::cout << arr[i] << ' ';
                  ^~~
*/