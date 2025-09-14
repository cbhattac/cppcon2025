# std::unique_ptr: Use std::optional in case there is no need to forward declare the class

If you do not need to manage a polymorphic type or forward declare a class, prefer `std::optional<T>` over `std::unique_ptr<T>` for optional values. This avoids heap allocation and simplifies code.

## Why is this a problem?
- Using `std::unique_ptr` for optional values adds unnecessary heap allocation and indirection.
- `std::optional` is more efficient and idiomatic for value types.

## Example 1: Using unique_ptr for optional value
```cpp
class Bar {};

class Foo {
 public:
  Foo() = default;
  void EnsureBar() {
    if (!bar_) {
      bar_ = std::make_unique<Bar>();
    }
  }

 private:
  std::unique_ptr<Bar> bar_;
};
```
### Fix: Use std::optional for value types
```cpp
class Foo {
 public:
  Foo() = default;
  void EnsureBar() {
    if (!bar_) {
      bar_.emplace();
    }
  }

 private:
  std::optional<Bar> bar_;
};
```

## Nuance: Use unique_ptr for polymorphic or incomplete types
If you need to forward declare a class or manage polymorphic objects, `std::unique_ptr` is appropriate. Otherwise, prefer `std::optional` for value semantics and efficiency.
