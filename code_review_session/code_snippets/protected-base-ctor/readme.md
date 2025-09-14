# Make Base Class Constructor Protected

If a class is intended only to be used as a base class, its constructor should be protected. This prevents direct instantiation and enforces correct usage.

## Why is this important?
- Prevents accidental instantiation of base classes that are not meant to be used directly.
- Enforces design intent and improves code safety.

### Problem: Public base class constructor allows direct instantiation
```cpp
class Base {
 public:
  Base(int x) : x_(x) {}
  int GetX() const { return x_; }
 private:
  int x_;
};

class Derived : public Base {
 public:
  Derived(int x) : Base(x) {}
};

// Usage:
Base b(5);  // Should not be allowed if Base is only for inheritance.
```

### Fix: Make base class constructor protected
```cpp
class Base {
 protected:
  explicit Base(int x) : x_(x) {}
 public:
  int GetX() const { return x_; }
 private:
  int x_;
};

class Derived : public Base {
 public:
  explicit Derived(int x) : Base(x) {}
};

// Usage:
// Base b(5);  // Error: constructor is protected.
Derived d(10);
```

#### Nuances
- Use `explicit` for single-argument constructors to avoid implicit conversions.
- If you want to allow instantiation in tests, you can use friend test classes or factory functions.
- This pattern is common in abstract base classes and interface-like designs.
