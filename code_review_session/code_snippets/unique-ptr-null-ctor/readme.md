# No need to use std::unique_ptr's null pointer constructor

`std::unique_ptr`'s default constructor already initializes the pointer to null. Explicitly passing `nullptr` is redundant and unnecessary.

## Why is this a problem?
- Redundant code can confuse readers and suggests that the default constructor behaves differently.
- It is less idiomatic and can be misleading to new developers.

## Example 1: Redundant nullptr constructor
```cpp
class Widget {};

class Foo {
 public:
  Foo() : ptr_(nullptr) {}
  // Other stuff.

 private:
  std::unique_ptr<Widget> ptr_;
  std::unique_ptr<Widget> ptr2_{nullptr};
};

int main() {
  [[maybe_unused]] std::unique_ptr<Widget> w{nullptr};

  [[maybe_unused]] Foo f;
}
```
### Fix: Use the default constructor
```cpp
#include <memory>

// clang-tidy check: none
// Clang-C++ warning: none
class Widget {};

class Foo {
 public:
  Foo() = default;
  // Other stuff.

 private:
  std::unique_ptr<Widget> ptr_;
  std::unique_ptr<Widget> ptr2_;
};

int main() {
  [[maybe_unused]] std::unique_ptr<Widget> w;

  [[maybe_unused]] Foo f;
}
```

## Nuance: Consistency and clarity
Prefer the default constructor for clarity and to follow common C++ idioms. Only use explicit initialization if you need to assign a non-null value at construction.
