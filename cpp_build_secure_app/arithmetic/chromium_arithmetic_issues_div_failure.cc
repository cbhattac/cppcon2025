#include <stdint.h>

#include <iostream>
#include <numeric>

#include "base/numerics/checked_math.h"
#include "base/numerics/clamped_math.h"

// NEEDS TO BE BUILT WITH CHROMIUM.

void Print(std::string_view op_name,
           int a,
           int b,
           int sat_result,
           int checked_result,
           bool ok) {
  std::cout << "Operation: " << op_name << " on (" << a << ", " << b << ")\n";
  std::cout << "-------------------------------------------\n";
  std::cout << "Saturated result: " << sat_result << '\n';
  std::cout << "Checked result: " << checked_result << '\n';
  if (ok) {
    std::cout << "Checked version (checked): " << checked_result << '\n';
  } else {
    std::cout << "Checked version (checked): fail\n";
  }
}

void TestDivision(int8_t a, int8_t b) {
  // Runtime crash. Division by zero.
  // const auto standard_div_result = a / b;
  // Runtime crash. Division by zero.
  const auto sat_div = base::ClampDiv(a, b);
  int8_t checked_result = 0;
  const auto ok = base::CheckDiv(a, b).AssignIfValid(&checked_result);
  Print("div", a, b, sat_div, checked_result, ok);
}

int main() {
  TestDivision(20, 0);
}

/*
Operation: div on (20, 0)
-------------------------------------------
Saturated result: 127
Checked result: 0
Checked version (checked): fail
*/
