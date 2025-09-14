#include <stdio.h>

class Base {
 public:
  virtual ~Base() = default;
  virtual void Foo() { puts("Base::Foo"); }
};

class Derived : public Base {
 public:
  void Foo() override { puts("Derived::Foo"); }
};

int main() {}