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
  const A& GetA() const& { return a; }
  A GetA() && { return std::move(a); }
  A a;
};

B GetB() {
  return {};
}

int main() {
  [[maybe_unused]] const auto& a = GetB().GetA();
  puts("===== After GetB().GetA() ======");
  // `a` is a copy and will be destroyed here.
}

/*
A()
A(A&&)
~A()
===== After GetB().GetA() ======
~A()
*/