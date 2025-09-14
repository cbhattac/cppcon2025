# Prefer contains() member over std::find for associative containers

C++20 introduced the `contains()` member function for associative containers like `std::set`, `std::map`, and `std::unordered_set`. It is clearer and more efficient than using `std::find` to check for existence.

## Why is this important?
- `contains()` is more readable and expresses intent directly.
- It can be more efficient than `std::find` because it does not construct an iterator.
- Reduces the chance of errors and improves code clarity.

### Example 1: Checking for existence in a set
```cpp
// Problematic: using std::find
std::set<int> s{1, 2, 3};
if (std::find(s.begin(), s.end(), 2) != s.end()) {
  // found
}
```
```cpp
// Fix: use contains()
std::set<int> s{1, 2, 3};
if (s.contains(2)) {
  // found
}
```

### Nuance: Pre-C++20 code
If you are targeting pre-C++20, `contains()` is not available, so `std::find` or `count` must be used.

### Nuance: Use with maps
`contains()` works for keys in maps, but not for values. For value lookup, you still need to use algorithms.
