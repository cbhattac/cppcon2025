#include <stdio.h>

#include <utility>

struct A {
  A(int, int) { puts("A(int, int)"); }
  ~A() { puts("~A()"); }
  A(const A&) { puts("A(const A&)"); }
  A(A&&) noexcept { puts("A(A&&)"); }
  A& operator=(const A&) {
    puts("A& operator=(const A&)");
    return *this;
  }
  A& operator=(A&&) noexcept {
    puts("A& operator=(A&&)");
    return *this;
  }
};

A Foo() {
  return {10, 10};
}

int main() {
  std::ignore = Foo();
}

// A(int, int)
// ~A()
