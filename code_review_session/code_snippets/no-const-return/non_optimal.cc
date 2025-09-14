#include <stdio.h>

#include <utility>
#include <vector>

struct A {
  A(int a, int b) { printf("A(%d, %d)\n", a, b); }
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

const A Foo() {
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
  }
  {
    // This code does not compile because Foo() returns a const A.
    // Foo() = A{10, 20};
  }
}

/*
A(10, 10)
A(const A&)
~A()
~A()
==========
A(20, 30)
A(10, 10)
A& operator=(const A&)
~A()
~A()
*/