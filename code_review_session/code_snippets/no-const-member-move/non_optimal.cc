#include <stdio.h>

#include <utility>

enum class MyEnum { kA, kB, kC };

const char* ToString(MyEnum e) {
  switch (e) {
    case MyEnum::kA:
      return "kA";
    case MyEnum::kB:
      return "kB";
    case MyEnum::kC:
      return "kC";
  }
}

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
  B(const B&) { puts("B(const B&)"); }
  B(B&&) noexcept { puts("B(B&&)"); }
  B& operator=(const B&) {
    puts("B& operator=(const B&)");
    return *this;
  }
  B& operator=(B&&) noexcept {
    puts("B& operator=(B&&)");
    return *this;
  }
};

struct C {
  C(MyEnum e) : e(e) {}
  void Print() const { printf("C::Print(): e=%s\n", ToString(e)); }
  const MyEnum e;
  A a;
  const B b;
};

int main() {
  C c(MyEnum::kB);
  puts("============");
  C c1 = c;
  c1.Print();
  puts("============");
  [[maybe_unused]] C c2 = std::move(c1);
  c2.Print();
  puts("============");
}

/*
A()
B()
============
A(const A&)
B(const B&)
C::Print(): e=kB
============
A(A&&)
B(const B&)
C::Print(): e=kB
============
~B()
~A()
~B()
~A()
~B()
~A()
*/
