# Use `std::monostate` for an Explicit Empty State in `std::variant`

When a `std::variant` needs an explicit empty or default state, use `std::monostate` instead of initializing with a "dummy" value.

## Problems with dummy default values
- Using a value like `0` or `""` as a default is not always meaningful.
- Can lead to confusion and subtle bugs.
- No way to distinguish between a real value and a placeholder.

### Example: Using a dummy default value
```cpp
// clang-tidy check: none
// Clang-C++ warning: none
std::variant<int, std::string> v; // 0 is default
```

#### Fix: Use `std::monostate`
```cpp
std::variant<std::monostate, int, std::string> v;
// v is now in the monostate (empty) state
```

## Nuances
- `std::monostate` is a type with a single value, used to represent "empty".
- Makes intent clear and code more robust.
- Use `std::holds_alternative<std::monostate>(v)` to check for the empty state.
- Avoids overloading a real value as a placeholder.
