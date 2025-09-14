#include <limits.h>
#include <math.h>

#include <iostream>

void SignedIntegerOverflow() {
  int a = INT_MAX;
  int b = a + 1;
  std::cout << "SignedIntegerOverflow: a = " << a << ", b = " << b << '\n';
}

void DivisionByZero() {
  int a = 10;
  int b = 0;
  const int c = a / b;
  std::cout << "DivisionByZero: c = " << c << '\n';
}

void ModuloByZero() {
  int a = 10;
  int b = 0;
  const int c = a % b;
  std::cout << "ModuloByZero: c = " << c << '\n';
}

void ShiftOperations() {
  int a = 1;
  int b = -1;
  const int c = a << b;
  std::cout << "ShiftOperations: c = " << c << '\n';
}

void IntegerDivisionOverflow() {
  const int a = INT_MIN;
  const int b = -1;
  const int c = a / b;
  std::cout << "IntegerDivisionOverflow: c = " << c << '\n';
}

void NaNPropagation() {
  const double a = NAN;
  const double b = a + 1;
  std::cout << "NaNPropagation: b = " << b << '\n';
}

int main() {
  SignedIntegerOverflow();
  IntegerDivisionOverflow();
  NaNPropagation();
}

/*
SignedIntegerOverflow: a = 2147483647, b = -2147483648
IntegerDivisionOverflow: c = 564301937
NaNPropagation: b = nan
*/