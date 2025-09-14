# Prefer std::make_unique for std::unique_ptr construction

C++14 introduced `std::make_unique` to simplify and make safer the construction of `std::unique_ptr`. Prefer using it over direct use of `new` with the `unique_ptr` constructor.

## Why is this important?
- `std::make_unique` is exception-safe and prevents memory leaks.
- It is more concise and less error-prone.
- Avoids repeating the type name, improving readability and maintainability.

### Example 1: Constructing a unique_ptr
```cpp
// Problematic: using new with unique_ptr
std::unique_ptr<std::vector<int>> ptr(new std::vector<int>{1, 2, 3});
```
```cpp
// Fix: use std::make_unique
auto ptr = std::make_unique<std::vector<int>>(std::initializer_list<int>{1, 2, 3});
```

### Nuance: Exception safety
`std::make_unique` guarantees that no memory is leaked if an exception is thrown during construction.

### Nuance: Type deduction
`std::make_unique` allows type deduction, making code less verbose and easier to refactor.

### Nuance: Custom deleters
If you need a custom deleter, you must still use the constructor form, as `make_unique` does not support custom deleters.
