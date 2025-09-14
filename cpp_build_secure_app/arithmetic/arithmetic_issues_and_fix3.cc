#include <stdint.h>

#include <iostream>
#include <limits>
#include <numeric>

// !!! NEEDS C++26 !!!

int main() {
  // We use int8_t for easy demonstration of overflow/underflow
  // The range of std::int8_t is -128 to 127
  const auto max_val = std::numeric_limits<int8_t>::max();
  const auto min_val = std::numeric_limits<int8_t>::min();

  std::cout << "Demonstrating Saturated vs. Standard vs. Checked Arithmetic on "
               "int8_t\n";
  std::cout << "Max value: " << static_cast<int>(max_val) << "\n";
  std::cout << "Min value: " << static_cast<int>(min_val) << "\n\n";

  // Note: Standard signed integer division overflow is undefined behavior.
  std::cout << "Operation: div_sat on (INT_MIN, -1)\n";
  std::cout << "-------------------------------------------\n";
  const int8_t standard_div_op1 = min_val;
  const int8_t standard_div_op2 = -1;
  // Standard division (undefined behavior)
  const auto standard_div_result = standard_div_op1 / standard_div_op2;
  std::cout << "Standard C++ (Undefined Behavior): standard_div_result: "
            << standard_div_result << '\n';
  const auto sat_div_result = std::div_sat(standard_div_op1, standard_div_op2);
  std::cout << "Saturated version (div_sat): "
            << static_cast<int>(sat_div_result) << "\n\n";
}

/*
Demonstrating Saturated vs. Standard vs. Checked Arithmetic on int8_t
Max value: 127
Min value: -128

Operation: div_sat on (INT_MIN, -1)
-------------------------------------------
Standard C++ (Undefined Behavior): standard_div_result: 128
Saturated version (div_sat): 127
*/