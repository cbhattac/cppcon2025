#include <stdio.h>

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
  const A& GetA() const { return a; }
  A a;
};

B GetB() {
  return {};
}

int main() {
  [[maybe_unused]] const auto& a = GetB().GetA();
  puts("===== After GetB().GetA() ======");
  // `a` has already been destroyed at this point, so using it is undefined
  // behavior.
}

/*
A()
~A()
===== After GetB().GetA() ======
*/

// GCC output:
/*
In function 'int main()':
error: possibly dangling reference to a temporary [-Werror=dangling-reference]
   [[maybe_unused]] const auto& a = GetB().GetA();
                                ^
note: 'B' temporary created here
   [[maybe_unused]] const auto& a = GetB().GetA();
                                    ~~~~^~
*/