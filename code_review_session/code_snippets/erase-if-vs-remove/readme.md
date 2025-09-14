# Prefer std::erase_if over erase/remove idiom

The erase/remove idiom is a common C++ pattern for removing elements from containers, but since C++20, `std::erase_if` provides a more concise and less error-prone alternative for standard containers.

## Why is this important?
- The erase/remove idiom is verbose and easy to misuse (e.g., forgetting to call erase).
- `std::erase_if` is more readable and less error-prone.
- Using `std::erase_if` can help avoid subtle bugs and makes intent clearer.

### Example 1: Removing odd numbers from a vector
```cpp
// Problematic: erase/remove idiom
std::vector<int> v{1, 2, 3, 4, 5};
v.erase(std::remove_if(v.begin(), v.end(), [](int x) { return x % 2 != 0; }), v.end());
```
```cpp
// Fix: use std::erase_if
std::vector<int> v{1, 2, 3, 4, 5};
std::erase_if(v, [](int x) { return x % 2 != 0; });
```

### Nuance: Custom containers or pre-C++20
If you are using a custom container or pre-C++20, `std::erase_if` may not be available, so the erase/remove idiom is still necessary.

### Nuance: Consistency and intent
Using `std::erase_if` makes the code's intent explicit and consistent across codebases that use C++20 or later.
