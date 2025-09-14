#include <stdint.h>

#include <iostream>

#include "base/numerics/clamped_math.h"

// NEEDS TO BE BUILT WITH CHROMIUM.

int main() {
  const int8_t a = 8;
  const int16_t b = 16;
  const auto c = a + b;
  const auto d = base::ClampAdd(a, b);
  std::cout << "Regular result: " << static_cast<int>(c) << '\n';
  std::cout << "Saturated result: " << static_cast<int>(d) << '\n';
}

/*
Regular result: 24
Saturated result: 24
*/
