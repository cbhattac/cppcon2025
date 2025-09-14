#include <stdint.h>

#include <iostream>
#include <numeric>

#include "base/numerics/safe_conversions.h"

// NEEDS TO BE BUILT WITH CHROMIUM.

void TestCasting() {
  std::cout << "Demonstrating base::saturated_cast\n";
  std::cout << "-------------------------------------------\n";
  const int16_t large_value = 200;  // Fits in int16_t, but not int8_t
  const int16_t small_value = 50;   // Fits in both

  const auto standard_cast_result = static_cast<int8_t>(large_value);
  std::cout << "Value to cast: " << large_value << "\n";
  std::cout << "Standard cast to int8_t: "
            << static_cast<int>(standard_cast_result) << " (Truncated)\n";

  const auto sat_cast_result = base::saturated_cast<int8_t>(large_value);
  std::cout << "base::saturated_cast to int8_t: " << static_cast<int>(sat_cast_result)
            << " (Clamped to INT8_MAX)\n\n";

  std::cout << "Value to cast: " << small_value << "\n";
  std::cout << "base::saturated_cast to int8_t: "
            << static_cast<int>(base::saturated_cast<int8_t>(small_value))
            << " (No clamping)\n";
}

int main() {
  TestCasting();
}

/*
Demonstrating base::saturated_cast
-------------------------------------------
Value to cast: 200
Standard cast to int8_t: -56 (Truncated)
base::saturated_cast to int8_t: 127 (Clamped to INT8_MAX)

Value to cast: 50
base::saturated_cast to int8_t: 50 (No clamping)
*/