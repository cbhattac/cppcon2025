# Prefer `std::visit` Over `std::get_if` for `std::variant`

`std::visit` is more idiomatic and less error-prone than manually checking each alternative with `std::get_if`.

## Problems with `std::get_if`
- Verbose and repetitive code.
- Easy to forget to handle a type, leading to bugs.
- Harder to maintain as the variant grows.

### Example: Using `std::get_if`
```cpp
// clang-tidy check: none
// Clang-C++ warning: none
if (auto p = std::get_if<int>(&v)) {
  // ...
} else if (auto q = std::get_if<std::string>(&v)) {
  // ...
}
```

#### Fix: Use `std::visit`
```cpp
std::visit([](const auto& val) {
  // ...
}, v);
```

## Nuances
- `std::visit` ensures all alternatives are handled.
- Lambdas can be overloaded for custom handling of each type.
- Easier to extend and maintain.
- Less error-prone for variants with many types.
