# Prefer STL algorithms over custom loops

C++ STL algorithms are expressive, less error-prone, and often more efficient than hand-written loops. Prefer using them whenever possible.

## Why is this important?
- STL algorithms are well-tested and optimized.
- They make code more readable and declarative.
- Reduce the risk of off-by-one and other common loop errors.

### Example 1: Counting even numbers
```cpp
// Problematic: manual loop
bool CountInterestingNumbers(std::span<const int> sp) {
  int count = 0;
  for (const auto i : sp) {
    if (i % 3 == 0) {
      ++count;
    }
  }
  return count;
}
```
```cpp
// Fix: use std::ranges::count_if
bool CountInterestingNumbers(std::span<const int> sp) {
  return std::ranges::count_if(sp, [](const auto i) { return i % 3 == 0; });
}
```

### Nuance: Custom logic
STL algorithms can take lambdas for custom logic, making them flexible for many use cases.

### Nuance: Early exit
Some algorithms (like `std::ranges::find_if`) can short-circuit, while manual loops may not be as clear about this intent.

### Nuance: Readability
Algorithms like `std::ranges::all_of`, `std::ranges::any_of`, and `std::ranges::none_of` can make intent much clearer than custom loops.
