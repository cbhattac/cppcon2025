# Use std::forward for forwarding references

When writing a function template that takes a forwarding (universal) reference, use `std::forward<T>(arg)` to perfectly forward the argument. This preserves the value category (lvalue/rvalue) and avoids unnecessary copies or moves.

If you use `std::move` or a cast, you may break perfect forwarding and cause subtle bugs or inefficiencies.

## Example 1: Not using std::forward
```cpp
template <typename T>
void ForwardingSink(T&& arg) {
  std::string s = static_cast<std::string&&>(arg);  // Not correct for all cases.
  (void)s;
}
```

### Fix:
```cpp
template <typename T>
void ForwardingSink(T&& arg) {
  std::string s = std::forward<T>(arg);
  (void)s;
}
```

## Nuance: Using `std::move(arg)` always casts to rvalue, which is incorrect for lvalues. Only `std::forward<T>(arg)` preserves the correct value category.

## Example 2: Using std::move instead of std::forward
```cpp
template <typename T>
void ForwardingSink(T&& arg) {
  std::string s = std::move(arg);  // Wrong for lvalues.
  (void)s;
}
```

### Fix:
```cpp
template <typename T>
void ForwardingSink(T&& arg) {
  std::string s = std::forward<T>(arg);
  (void)s;
}
```
