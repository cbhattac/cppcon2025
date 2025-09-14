# No need to use std::unique_ptr if the variable is created at the start of scope and destroyed at the end of scope

In many cases, developers use `std::unique_ptr` for local variables that are created at the beginning of a scope and destroyed at the end. This is unnecessary and adds complexity, as a plain object or value is sufficient and more efficient.

## Why is this a problem?
- Using `std::unique_ptr` for local variables that do not require dynamic lifetime management adds heap allocation overhead and reduces code clarity.
- It can make code harder to read and maintain, and may introduce unnecessary indirection.

## Example: Unnecessary use of std::unique_ptr
```cpp
class MyClass {
 public:
  void DoSomething() {}
  // Other stuff.
};
```
```cpp
int main() {
  auto my_class = std::make_unique<MyClass>();
  my_class->DoSomething();
  // Use `my_class` to the end of scope.
}
```
### Fix: Use a plain value
```cpp
int main() {
  MyClass my_class;
  my_class.DoSomething();
  // Use `my_class` to the end of scope.
}
```

## Nuance: Only use smart pointers when ownership or dynamic lifetime is required
If you need to transfer ownership or manage lifetime beyond the current scope, then `std::unique_ptr` is appropriate. Otherwise, prefer stack variables for clarity and performance.
