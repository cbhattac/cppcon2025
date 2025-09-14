# std::unique_ptr: No need to call reset() for unique_ptr member variable in the destructor

`std::unique_ptr` automatically releases its resource when it goes out of scope. Explicitly calling `reset()` in the destructor is unnecessary and can be misleading.

## Why is this a problem?
- Redundant code in the destructor can confuse maintainers and suggest that `unique_ptr` does not clean up automatically.
- It can hide more important destructor logic.

## Example 1: Calling reset() in destructor
```cpp
class Foo {
 public:
  ~Foo() {
    ptr_.reset();  // Unnecessary
  }

 private:
  std::unique_ptr<int> ptr_ = std::make_unique<int>(42);
};
```
### Fix: Let unique_ptr clean up automatically
```cpp
class Foo {
 public:
  ~Foo() = default;

 private:
  std::unique_ptr<int> ptr_ = std::make_unique<int>(42);
};
```

## Nuance: Only add custom destructor logic if needed
If you need to perform additional cleanup, do so, but do not call `reset()` on smart pointers unless you have a specific reason.
