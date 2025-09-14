#include <iostream>

void ProblemSum() {
  float sum = 0;
  for (size_t i = 0; i < 1e8; ++i) {
    sum += 1.f;
  }
  std::cout << "ProblemSum: " << sum << '\n';
}

void KahanSum() {
  float sum = 0.0f;
  float c = 0.0f;  // A running compensation for lost low-order bits.
  const float term = 1.0f;
  for (size_t i = 0; i < 1e8; ++i) {
    float y = term - c;  // y = next term - compensation.
    float t = sum + y;   // t = sum + y
    c = (t - sum) - y;   // c = (t - sum) - y, this is the lost part
    sum = t;             // sum becomes the new sum.
  }
  std::cout << "Kahan summation: " << sum << '\n';
}

int main() {
  ProblemSum();
  KahanSum();
}

/*
ProblemSum: 1.67772e+07
Kahan summation: 1e+08
*/