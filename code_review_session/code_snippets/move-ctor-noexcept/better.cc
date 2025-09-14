#include <stdio.h>

#include <vector>

struct A final {
  A(int a) : a_(a) { printf("A(%d)\n", a_); }
  ~A() { puts("~A()"); }
  A(const A& rhs) : a_(rhs.a_) { printf("A(const A&): %d\n", a_); }
  A(A&& rhs) noexcept : a_(rhs.a_) { printf("A(A&&): %d\n", a_); }
  A& operator=(const A& rhs) {
    a_ = rhs.a_;
    printf("A& operator=(const A&): %d\n", a_);
    return *this;
  }
  A& operator=(A&& rhs) noexcept {
    a_ = rhs.a_;
    printf("A& operator=(A&&): %d\n", a_);
    return *this;
  }
  int a_ = 0;
};

int main() {
  std::vector<A> vec;
  // Don't consider `reserve` for the moment.
  for (int i = 0; i < 4; ++i) {
    vec.emplace_back(i);
  }
}

/*
A(0)
A(1)
A(A&&): 0
~A()
A(2)
A(A&&): 0
A(A&&): 1
~A()
~A()
A(3)
~A()
~A()
~A()
~A()
*/
