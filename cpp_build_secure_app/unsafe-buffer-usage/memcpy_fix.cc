#include <algorithm>
#include <array>
#include <iostream>
#include <span>

// ONLY clang + x86-32 / x86-64
#define ASSERT(condition)            \
  do {                               \
    if (!(condition)) [[unlikely]] { \
      asm volatile("ud2");           \
    }                                \
  } while (0)

template <typename T, std::size_t DestExtent, std::size_t SrcExtent>
void MemCpySpan(std::span<T, DestExtent> destination,
                std::span<const T, SrcExtent> source) {
  ASSERT(destination.size() >= source.size());
  std::ranges::copy(source, destination.begin());
}

int main() {
  const char str[] = "Hello!!";
  char buffer[2 * std::size(str)]{};
  MemCpySpan(std::span{buffer}, std::span{str});
  std::cout << buffer;
}