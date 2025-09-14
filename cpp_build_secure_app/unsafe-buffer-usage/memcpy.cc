#include <memory.h>

#include <array>
#include <iostream>

int main() {
  const char str[] = "Hello!!";
  char buffer[2 * std::size(str)]{};
  memcpy(buffer, str, std::size(str));
  std::cout << buffer << '\n';
}

// -Wunsafe-buffer-usage
/*
error: function 'memcpy' is unsafe [-Werror,-Wunsafe-buffer-usage-in-libc-call]
   memcpy(buffer, str, std::size(str));
   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/