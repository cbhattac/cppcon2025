#include <iostream>

union U {
  int n;
  float f;
};

consteval float TestUnion1(int n) {
  U u{.n = n};
  return u.f;
}

int main() {
  // DOES NOT COMPILE!!
  constexpr float f = TestUnion1(10);
  std::cout << f << '\n';
}

/*
error: constexpr variable 'f' must be initialized by a constant expression
   constexpr float f = TestUnion1(10);
                   ^   ~~~~~~~~~~~~~~
note: read of member 'f' of union with active member 'n' is not allowed in a constant expression
   return u.f;
*/