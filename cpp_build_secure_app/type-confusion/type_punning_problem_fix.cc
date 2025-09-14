#include <bit>
#include <iostream>

union U {
  int n;
  float f;
};

consteval float TestUnion2(int n) {
  return std::bit_cast<float>(n);
}

int main() {
  constexpr float f = TestUnion2(10);
  std::cout << f << '\n';
}

/*
1.4013e-44
*/