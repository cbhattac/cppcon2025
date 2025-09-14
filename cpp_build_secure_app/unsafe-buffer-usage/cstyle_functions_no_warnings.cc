#include <stdio.h>
#include <string.h>

// These will not raise warnings when built with `-Wunsafe-buffer-usage`.
void TestUnsafeFunctions(char* p) {
  [[maybe_unused]] const auto l = strlen("hello");  // no warn
  printf("%s%d", "hello", *p);                      // no warn
}

int main() {}