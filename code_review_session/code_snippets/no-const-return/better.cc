#include <stdio.h>

#include <utility>
#include <vector>

struct A {
  A(int a, int b) { printf("A(%d, %d)\n", a, b); }
  ~A() { puts("~A()"); }
  A(const A&) { puts("A(const A&)"); }
  A(A&&) noexcept { puts("A(A&&)"); }
  A& operator=(const A&) & {
    puts("A& operator=(const A&)");
    return *this;
  }
  A& operator=(A&&) & noexcept {
    puts("A& operator=(A&&)");
    return *this;
  }
};

A Foo() {
  return {10, 10};
}

int main() {
  {
    std::vector<A> vec;
    vec.push_back(Foo());
  }
  puts("==========");
  {
    A a{20, 30};
    a = Foo();
    // All this code will compile and run correctly.
    // A a2{10, 20};
    // a = a2;
    // a = std::move(a2);
    // const A a3{30, 40};
    // a = a3;
  }
  {
    // Will not compile.
    // Foo() = A{10, 20};
  }
}

/*
A(10, 10)
A(A&&)
~A()
~A()
==========
A(20, 30)
A(10, 10)
A& operator=(A&&)
~A()
~A()
*/