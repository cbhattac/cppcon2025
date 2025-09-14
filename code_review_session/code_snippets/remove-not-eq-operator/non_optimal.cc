#include <iostream>
#include <string>

// clang-tidy check: none
// Clang-C++ warning: none
struct A {
  std::string a;
  std::string b;
  int c = 0;
  bool d = false;

  bool operator==(const A& rhs) const {
    return a == rhs.a && b == rhs.b && c == rhs.c && d == rhs.d;
  }

  bool operator!=(const A& rhs) const { return !(*this == rhs); }
};

int main() {
  A a{"hello", "world", 10, false};
  A b{"hello", "world", 10, false};
  std::cout << std::boolalpha << (a != b) << '\n';  // false
}

// false