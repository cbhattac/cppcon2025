# Make member functions static when appropriate

If a member function does not access any non-static member variables or functions, it should be declared static.

**Problem:**
```cpp
class Logger {
 public:
  void PrintHello() {
    std::cout << "Hello, world!" << std::endl;
  }
};
```

**Fix:**
```cpp
class Logger {
 public:
  static void PrintHello() {
    std::cout << "Hello, world!" << std::endl;
  }
};
```
