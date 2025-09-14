Class: ensure that appropriate special member functions are generated and not getting suppressed.

## Problem:
```cpp
struct B {
  B() { puts("B()"); }
  ~B() { puts("~B()"); }
  A a;
};
```
This suppress move operators.

## Fix: 1
The following lets compiler generate move operators.
```cpp
struct B {
  B() { puts("B()"); }
  A a;
};
```
## Fix: 2
In the following we are explicitly adding defaults.
```cpp
struct B {
  B() { puts("B()"); }
  ~B() { puts("~B()"); };
  B(const B&) = default;
  B(B&&) noexcept = default;
  B& operator=(const B&) = default;
  B& operator=(B&&) noexcept = default;
  A a;
};
```
