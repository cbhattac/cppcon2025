#include <stdckdint.h>
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
           int sat_result,
           bool ckd_overflow,
           int ckd_result) {
  std::cout << "Operation: " << op_name << " on (" << a << ", " << b << ")\n";
  std::cout << "-------------------------------------------\n";
  std::cout << "Standard C++ (" << a << " " << op_name << " " << b
            << "): " << standard_result << "\n";
  std::cout << "Saturated version (sat): " << sat_result << '\n';
  std::cout << "Checked version (ckd): " << ckd_result;
  if (ckd_overflow) {
    std::cout << " (Overflow Detected)\n\n";
  } else {
    std::cout << " (No Overflow)\n\n";
  }
}

void TestAdd() {
  const int8_t a = 120;
  const int8_t b = 10;
  const auto standard_sum = a + b;
  const auto sat_sum = std::add_sat(a, b);
  int8_t ckd_sum = 0;
  const bool overflow = ckd_add(&ckd_sum, a, b);
  Print("add", a, b, standard_sum, sat_sum, overflow, ckd_sum);
}

void TestSubstract() {
  const int8_t c = -120;
  const int8_t d = 10;
  const auto standard_diff = c - d;
  const auto sat_diff = std::sub_sat(c, d);
  int8_t ckd_diff = 0;
  const bool overflow = ckd_sub(&ckd_diff, c, d);
  Print("sub", c, d, standard_diff, sat_diff, overflow, ckd_diff);
}

void TestMultiply() {
  const int8_t e = 20;
  const int8_t f = 10;
  const auto standard_prod = e * f;
  const auto sat_prod = std::mul_sat(e, f);
  int8_t ckd_prod = 0;
  const bool overflow = ckd_mul(&ckd_prod, e, f);
  Print("mul", e, f, standard_prod, sat_prod, overflow, ckd_prod);
}

int main() {
  // We use int8_t for easy demonstration of overflow/underflow
  // The range of int8_t is -128 to 127
  const auto max_val = std::numeric_limits<int8_t>::max();
  const auto min_val = std::numeric_limits<int8_t>::min();

  std::cout << "Demonstrating Saturated vs. Standard vs. Checked Arithmetic on "
               "int8_t\n";
  std::cout << "Max value: " << static_cast<int>(max_val) << "\n";
  std::cout << "Min value: " << static_cast<int>(min_val) << "\n\n";

  TestAdd();
  TestSubstract();
  TestMultiply();
}

/*
Demonstrating Saturated vs. Standard vs. Checked Arithmetic on int8_t
Max value: 127
Min value: -128

Operation: add on (120, 10)
-------------------------------------------
Standard C++ (120 add 10): 130
Saturated version (sat): 127
Checked version (ckd): -126 (Overflow Detected)

Operation: sub on (-120, 10)
-------------------------------------------
Standard C++ (-120 sub 10): -130
Saturated version (sat): -128
Checked version (ckd): 126 (Overflow Detected)

Operation: mul on (20, 10)
-------------------------------------------
Standard C++ (20 mul 10): 200
Saturated version (sat): 127
Checked version (ckd): -56 (Overflow Detected)
*/
