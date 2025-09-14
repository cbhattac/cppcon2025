# Return non-trivial read-only member variables as const reference

Returning a non-trivial member variable (like std::string) by value can be inefficient. Prefer returning a const reference to that member.

**Problem:**
```cpp
class Book {
 public:
  Book(std::string title) : title_(std::move(title)) {}
  std::string GetTitle() const { return title_; }
 private:
  std::string title_;
};
```

**Fix:**
```cpp
class Book {
 public:
  Book(std::string title) : title_(std::move(title)) {}
  const std::string& GetTitle() const { return title_; }
 private:
  std::string title_;
};
```

**Problem with returning reference**
```cpp
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
```

**Fix**
```cpp
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
```