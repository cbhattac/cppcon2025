# Ensure that multiple std::moves are not made on a single variable

After moving from a variable, its state is valid but unspecified. Using `std::move` on the same variable multiple times can lead to undefined or unexpected behavior, as the contents may be empty or otherwise unusable after the first move.

## Example 1: Multiple moves from the same variable
```cpp
std::string s = "hello";
std::vector<std::string> v;
v.push_back(std::move(s));
v.push_back(std::move(s));  // UB: s has been moved from already.
```

### Fix:
```cpp
std::string s = "hello";
std::vector<std::string> v;
v.push_back(std::move(s));
// Do not use s after it has been moved from.
```

## Nuance: If you need to use the variable again, reassign it before moving again.

## Example 2: Reassign before move
```cpp
std::string s = "hello";
v.push_back(std::move(s));
s = "world";
v.push_back(std::move(s));
```
