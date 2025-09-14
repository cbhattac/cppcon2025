## Keep only == and remove !=.

## Problem:
```cpp
struct A {
  std::string a;
  std::string b;
  int c = 0;
  bool d = false;

  bool operator==(const A& rhs) const {
    return a == rhs.a && b == rhs.b && c == rhs.c && d == rhs.d;
  }

  bool operator!=(const A& rhs) const { return !(*this == rhs); }
};
```
## Fix 1:
C++20 compiler will generate `!=` from `==`.
```cpp
struct A {
  std::string a;
  std::string b;
  int c = 0;
  bool d = false;

  bool operator==(const A& rhs) const {
    return a == rhs.a && b == rhs.b && c == rhs.c && d == rhs.d;
  }
};
```
## Fix 2:
Since all member variables are being used for comparison, we can C++20's defaulted version.
```cpp
struct A {
  std::string a;
  std::string b;
  int c = 0;
  bool d = false;

  bool operator==(const A& rhs) const noexcept = default;
};
```

