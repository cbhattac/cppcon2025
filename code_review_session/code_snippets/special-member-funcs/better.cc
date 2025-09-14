#include <stdio.h>

#include <utility>

struct A {
  A() { puts("A()"); }
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

struct B {
  B() { puts("B()"); }
  A a;
};

int main() {
  B b;
  puts("=== Before move ===");
  [[maybe_unused]] B b2 = std::move(b);
  puts("=== After move ===");
  return 0;
}

/*
A()
B()
=== Before move ===
A(A&&)
=== After move ===
~A()
~A()
*/