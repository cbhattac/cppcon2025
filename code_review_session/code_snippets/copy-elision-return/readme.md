# Prefer copy elision when returning values

Returning local variables by value can sometimes prevent copy elision, leading to unnecessary copies. Prefer returning values directly to enable copy elision.

**Problem:**
```cpp
std::string MakeString() {
  std::string s = "hello world";
  return s;
}
```

**Fix:**
```cpp
std::string MakeString() {
  return "hello world";
}
```
