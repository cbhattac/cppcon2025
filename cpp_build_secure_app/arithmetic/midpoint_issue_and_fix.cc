#include <stdint.h>

#include <iostream>
#include <limits>
#include <numeric>

void CheckMid(int a, int b) {
  const auto naive_mid = (a + b) / 2;  // UB if a + b overflows
  // Safe midpoint (C++20)
  const auto safe_mid = std::midpoint(a, b);
  std::cout << "a = " << a << '\n';
  std::cout << "b = " << b << '\n';
  std::cout << "naive_mid = " << naive_mid
            << " (undefined behavior possible)\n";
  std::cout << "std::midpoint = " << safe_mid << " (well-defined)\n";
}

int main() {
  const auto a = std::numeric_limits<int>::max();
  const auto b = std::numeric_limits<int>::max();
  CheckMid(a, b);
}

/*
a = 2147483647
b = 2147483647
naive_mid = -1 (undefined behavior possible)
std::midpoint = 2147483647 (well-defined)
*/