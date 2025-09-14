# Prefer `std::variant` Over Unions or Multiple Variables

`std::variant` provides type safety and better semantics compared to unions or keeping multiple variables for alternative types.

## Problems with unions or multiple variables
- No type safety: accessing the wrong member is undefined behavior.
- Cannot store non-trivial types (e.g., `std::string`) safely in a union.
- Manual tracking of active member is error-prone.
- Hard to extend and maintain.

### Example: Using a union
```cpp
// clang-tidy check: none
// Clang-C++ warning: none
union Value {
  int i;
  double d;
  char str[16];
};
Value v;
v.i = 42;
// ...
std::strcpy(v.str, "hello");
// ...
```

#### Fix: Use `std::variant`
```cpp
std::variant<int, double, std::string> v = 42;
v = std::string("hello");
```

## Nuances
- `std::variant` can hold any type, including non-trivial types.
- Type-safe access via `std::get` or `std::get_if`.
- You can use `std::visit` for generic operations.
- No need to manually track which member is active.
- Unions are only safe for trivial types and require manual management.
