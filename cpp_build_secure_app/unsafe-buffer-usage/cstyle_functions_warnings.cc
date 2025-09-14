#include <memory.h>
#include <stdio.h>
#include <string.h>

// Each function used below will raise
// `-Werror,-Wunsafe-buffer-usage-in-libc-call` when built with
// `-Wunsafe-buffer-usage`.
void TestUnsafeFunctions() {
  char buffer[64];
  char source[64] = "source";
  char destination[64];
  FILE* file = nullptr;

  // Unsafe memory functions
  memcpy(destination, source,
         sizeof(source));  // expected-warning{{function 'memcpy' is unsafe}}
  memset(
      destination, 0,
      sizeof(destination));  // expected-warning{{function 'memset' is unsafe}}
  memmove(destination, source,
          sizeof(source));  // expected-warning{{function 'memmove' is unsafe}}
  strcpy(destination,
         source);  // expected-warning{{function 'strcpy' is unsafe}}
  [[maybe_unused]] const auto l =
      strlen(source);  // expected-warning{{function 'strlen' is unsafe}}

  // Unsafe I/O functions
  fprintf(file, "Test %s",
          source);  // expected-warning{{function 'fprintf' is unsafe}}
  printf("Test %s", source);  // expected-warning{{function 'printf' is unsafe}}
  sprintf(buffer, "Test %s",
          source);  // expected-warning{{function 'sprintf' is unsafe}}
  snprintf(buffer, sizeof(buffer), "Test %s",
           source);  // expected-warning{{function 'snprintf' is unsafe}}
  vsnprintf(buffer, sizeof(buffer), "Test %s",
            nullptr);  // expected-warning{{function 'vsnprintf' is unsafe}}

  // Unsafe parsing functions
  sscanf(source, "%s",
         buffer);  // expected-warning{{function 'sscanf' is unsafe}}
}

int main() {}
