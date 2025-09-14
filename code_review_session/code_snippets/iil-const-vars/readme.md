# Use immediately invoked lambdas to get const variables

Immediately invoked lambdas (IILs) allow you to initialize `const` variables with complex logic, ensuring immutability and clarity.

## Nuance 1: Complex initialization

```cpp
void Foo(bool show, int val) {
  int final_value = 0;
  if (show) {
    if (val == 1) {
      final_value = 3;
    } else if (val <= 100) {
      final_value = 4;
    } else {
      final_value = 5;
    }
  } else {
    if (val == 1) {
      final_value = 6;
    } else {
      final_value = 7;
    }
  }
  // Use `final_value`.
  std::cout << final_value << '\n';
}
```

**Fix:**
```cpp
void Foo(bool show, int val) {
  const int final_value = [&]() {
    if (show) {
      if (val == 1) {
        return 3;
      } else if (val <= 100) {
        return 4;
      }
      return 5;
    }
    if (val == 1) {
      return 6;
    }
    return 7;
  }();
  // Use `final_value`.
  std::cout << final_value << '\n';
}
```

## Nuance 2: Ensuring constness for computed values

IILs make it easy to create `const` variables from computations or function calls, which cannot be done with `constexpr` if the computation is not constant-evaluable at compile time.
