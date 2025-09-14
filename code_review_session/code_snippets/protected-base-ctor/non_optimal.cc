#include <iostream>

// clang-tidy check: none
// Clang-C++ warning: none

class Base {
 public:
  explicit Base(int x) : x_(x) {}
  int GetX() const { return x_; }

 private:
  const int x_;
};

class Derived : public Base {
 public:
  explicit Derived(int x) : Base(x) {}
};

int main() {
  const Base b(5);
  std::cout << b.GetX() << '\n';
}

// 5