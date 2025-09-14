Move non-member, static functions out of the class into unnamed namespace in the .cc file.

```cpp
// Problem: Non-static member function that does not access class members.
class MyClass {
 public:
  int DoSomething();

 private:
  static int CalculateResult(int a, int b);
};

// source file: my_class.cc
int MyClass::DoSomething() {
  // Use CalculateResult.
  return CalculateResult(10, 20);
}

int MyClass::CalculateResult(int a, int b) {
  return a + b;
}
```

```cpp
// Fix: Move function to unnamed namespace in .cc file.
// header file: my_class.h
class MyClass {
 public:
  int DoSomething();
};

// source file: my_class.cc
namespace {
int CalculateResult(int a, int b) {
  return a + b;
}
}  // namespace

int MyClass::DoSomething() {
  // Use CalculateResult.
  return CalculateResult(10, 20);
}
```
