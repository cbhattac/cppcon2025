# Mark Overridden Functions with `override` or `final`

Always mark overridden virtual functions with `override` or `final` to improve code safety and clarity.

## Why is this important?
- Ensures the function is actually overriding a base class method.
- Helps catch errors due to signature mismatches or typos.
- Makes code easier to understand and maintain.

### Problem: Overridden function not marked
```cpp
class Base {
 public:
  virtual ~Base() = default;
  virtual void Foo() { puts("Base::Foo"); }
};

class Derived : public Base {
 public:
  void Foo() { puts("Derived::Foo"); }
};
```

### Fix: Use `override` keyword
```cpp
class Base {
 public:
  virtual ~Base() = default;
  virtual void Foo() { puts("Base::Foo"); }
};

class Derived : public Base {
 public:
  void Foo() override { puts("Derived::Foo"); }
};
```

#### Nuances
- Use `final` if you want to prevent further overrides in derived classes.
- If a function is not marked `override` and its signature changes, it may not override as intended, leading to subtle bugs.
- Some static analysis tools and compilers can warn if `override` is missing, but it's best practice to always include it.
