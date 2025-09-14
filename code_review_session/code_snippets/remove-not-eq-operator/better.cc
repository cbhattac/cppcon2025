#include <iostream>
#include <string>

struct A {
  std::string a;
  std::string b;
  int c = 0;
  bool d = false;

  bool operator==(const A& rhs) const noexcept = default;
};

int main() {
  A a{"hello", "world", 10, false};
  A b{"hello", "world", 10, false};
  std::cout << std::boolalpha << (a != b) << '\n';  // false
}

// false