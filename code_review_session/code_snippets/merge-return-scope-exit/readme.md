<!-- TODO: Update to better example -->

# Merge return paths using scope-exit

If common code is called before each return statement, move the common code into a scope-exit construct (such as a lambda or RAII object) to ensure it is always executed.

**Problem:**
```cpp
std::string Process(bool flag) {
  std::cout << "Start processing\n";
  if (flag) {
    std::cout << "Cleanup\n";
    return "Flag true";
  }
  std::cout << "Cleanup\n";
  return "Flag false";
}
```

**Fix:**
```cpp
std::string Process(bool flag) {
  std::cout << "Start processing\n";
  struct ScopeExit {
    ~ScopeExit() { std::cout << "Cleanup\n"; }
  } scope_exit;
  if (flag) {
    return "Flag true";
  }
  return "Flag false";
}
```
