# std::unique_ptr: use reset() instead of assigning = nullptr

When you want to release the resource managed by a `std::unique_ptr`, prefer calling `reset()` over assigning `nullptr` directly. This is more idiomatic and makes the intent explicit.

## Why is this a problem?
- Assigning `nullptr` is less explicit and can be confusing in code reviews.
- `reset()` clearly communicates the intent to release the resource.

## Example 1: Assigning nullptr
```cpp
struct A {
  // Some stuff.
};

class B {
 public:
  // Functions related to creation of `a_`.

  void Reset() { a_ = nullptr; }

 private:
  std::unique_ptr<A> a_;
};

void Foo() {
  auto a = std::make_unique<A>();
  // Use `a`.
  a = nullptr;
  // Other stuff
}
```
### Fix: Use reset()
```cpp
class B {
 public:
  // Functions related to creation of `a_`.

  void Reset() {
    a_.reset();
  }

 private:
  std::unique_ptr<A> a_;
};

void Foo() {
  auto a = std::make_unique<A>();
  // Use.
  a.reset();
  // Other stuff 
}
```

## Nuance: reset() can also assign a new pointer
You can use `reset(new_ptr)` to assign a new resource, or `reset()` to release the current one. This is more flexible and idiomatic than assignment.
