#include <limits.h>
#include <iostream>

// DOES NOT COMPILE!
void SignedIntegerOverflow() {
  constexpr int a = INT_MAX;
  constexpr int b = a + 1;  // Undefined behavior: signed integer overflow
  std::cout << "SignedIntegerOverflow: a = " << a << ", b = " << b << '\n';
}

// DOES NOT COMPILE!
void DivisionByZero() {
  const int a = 10;
  const int b = 0;
  const int c = a / b;
  std::cout << "DivisionByZero: c = " << c << '\n';
}

// DOES NOT COMPILE!
void ModuloByZero() {
  const int a = 10;
  const int b = 0;
  const int c = a % b;
  std::cout << "ModuloByZero: c = " << c << '\n';
}

// DOES NOT COMPILE!
void ShiftOperations() {
  const int a = 1;
  const int b = -1;
  const int c = a << b;
  std::cout << "ShiftOperations: c = " << c << '\n';
}

// DOES NOT COMPILE!
void IntegerDivisionOverflow() {
  const int a = INT_MIN;
  const int b = -1;
  constexpr int c = a / b;
  std::cout << "IntegerDivisionOverflow: c = " << c << '\n';
}

// DOES NOT COMPILE!
void NaNPropagation() {
  const double a = NAN;
  constexpr double b = a + 1;
  std::cout << "NaNPropagation: b = " << b << '\n';
}

int main() {
  SignedIntegerOverflow();
}