# Use std::move for rvalues which are not forwarding reference

When returning a local variable from a function, use `std::move` to indicate that the value can be moved, unless the return type is a forwarding reference. This helps avoid unnecessary copies and makes the intent explicit.

If you do not use `std::move`, the compiler may still optimize via NRVO (Named Return Value Optimization), but this is not guaranteed in all cases, and explicit `std::move` is clearer for rvalues.

## Example 1: Not using std::move
```cpp
std::string MakeString() {
  std::string s = "hello";
  return s;  // NRVO may apply, but explicit move is better for rvalues.
}
```

### Fix:
```cpp
std::string MakeString() {
  std::string s = "hello";
  return std::move(s);  // Explicit move for rvalue.
}
```

## Nuance: NRVO may eliminate the copy, but if the function returns a conditional or from a loop, NRVO may not apply. Explicit move is safer for rvalues.

## Example 2: Conditional return
```cpp
std::string MakeString(bool flag) {
  std::string s = "foo";
  if (flag) return s;
  return s + "bar";
}
```

### Fix:
```cpp
std::string MakeString(bool flag) {
  std::string s = "foo";
  if (flag) return std::move(s);
  return s + "bar";
}
```
