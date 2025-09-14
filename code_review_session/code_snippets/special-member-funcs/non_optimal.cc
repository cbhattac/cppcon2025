#include <stdio.h>

#include <utility>

// clang-tidy check: cppcoreguidelines-special-member-functions
// Clang-C++ warning: none
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
  ~B() { puts("~B()"); }
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
A(const A&)
=== After move ===
~B()
~A()
~B()
~A()
*/

// -checks=cppcoreguidelines-special-member-functions
/*
warning: class 'B' defines a non-default destructor but does not define a copy constructor, a copy assignment operator, a move constructor or a move assignment operator [cppcoreguidelines-special-member-functions]
 struct B {
        ^
*/