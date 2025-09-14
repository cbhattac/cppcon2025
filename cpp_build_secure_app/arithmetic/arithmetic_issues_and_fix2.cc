#include <stdint.h>

#include <iostream>
#include <limits>
#include <numeric>

// !!! NEEDS C++26 !!!

void TestCasting() {
  std::cout << "Demonstrating saturate_cast\n";
  std::cout << "-------------------------------------------\n";
  const int16_t large_value = 200;  // Fits in int16_t, but not int8_t
  const int16_t small_value = 50;   // Fits in both

  const auto standard_cast_result = static_cast<int8_t>(large_value);
  std::cout << "Value to cast: " << large_value << "\n";
  std::cout << "Standard cast to int8_t: "
            << static_cast<int>(standard_cast_result) << " (Truncated)\n";

  const auto sat_cast_result = std::saturate_cast<int8_t>(large_value);
  std::cout << "saturate_cast to int8_t: " << static_cast<int>(sat_cast_result)
            << " (Clamped to INT8_MAX)\n\n";

  std::cout << "Value to cast: " << small_value << "\n";
  std::cout << "saturate_cast to int8_t: "
            << static_cast<int>(std::saturate_cast<int8_t>(small_value))
            << " (No clamping)\n";
}

int main() {
  TestCasting();
}

/*
Demonstrating saturate_cast
-------------------------------------------
Value to cast: 200
Standard cast to int8_t: -56 (Truncated)
saturate_cast to int8_t: 127 (Clamped to INT8_MAX)

Value to cast: 50
saturate_cast to int8_t: 50 (No clamping)
*/