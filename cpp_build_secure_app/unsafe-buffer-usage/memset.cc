#include <memory.h>

#include <print>
#include <span>

// C++23
void Print(std::span<int, 4> sp) {
  std::println("{} {} {} {}", sp[0], sp[1], sp[2], sp[3]);
}

int main() {
  int arr[4]{};
  // Attempt to set each element in array 1.
  memset(arr, 1, sizeof(arr));
  Print(arr);
}

// 16843009 16843009 16843009 16843009
// -Wunsafe-buffer-usage
/*
error: function 'memset' is unsafe [-Werror,-Wunsafe-buffer-usage-in-libc-call]
 memset(arr, 1, sizeof(arr));
 ^~~~~~~~~~~~~~~~~~~~~~~~~~~
*/