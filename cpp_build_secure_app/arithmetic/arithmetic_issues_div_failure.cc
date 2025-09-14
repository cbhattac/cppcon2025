#include <stdint.h>

#include <iostream>
#include <limits>
#include <numeric>
#include <string_view>

// !!! NEEDS C++26 !!!

void Print(std::string_view op_name,
           int a,
           int b,
           int standard_result,
           int sat_result) {
  std::cout << "Operation: " << op_name << " on (" << a << ", " << b << ")\n";
  std::cout << "-------------------------------------------\n";
  std::cout << "Standard C++ (" << a << " " << op_name << " " << b
            << "): " << standard_result << "\n";
  std::cout << "Saturated version (sat): " << sat_result << '\n';
}

void TestDivision(int8_t a, int8_t b) {
  // Runtime crash. Division by zero.
  const auto standard_div_result = a / b;
  // Runtime crash. Division by zero.
  const auto sat_div = std::div_sat(a, b);
  Print("div", a, b, standard_div_result, sat_div);
}

int main() {
  TestDivision(20, 0);
}

// FAILS AT RUNTIME. Division by zero.