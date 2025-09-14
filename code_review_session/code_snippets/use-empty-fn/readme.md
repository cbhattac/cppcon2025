# Prefer empty() over size() == 0 for containers

Checking if a container is empty using `size() == 0` is less clear and may be less efficient than using the `empty()` member function, which is designed for this purpose.

## Problem: Using size() == 0
```cpp
if (v.size() == 0) {
  // ...
}
```

## Fix: Use empty()
```cpp
if (v.empty()) {
  // ...
}
```

### Nuances
- `empty()` is more readable and clearly expresses intent.
- For some containers, `empty()` may be more efficient than `size()`.
- Using `empty()` avoids potential confusion with signed/unsigned comparison warnings.
- Consistent use of `empty()` improves code clarity and maintainability.
