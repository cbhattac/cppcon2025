# Make Classes `final` If You Don't Want Inheritance

Marking a class as `final` prevents further inheritance. This is useful for classes that are not designed to be base classes, improving safety and performance.

## Why is this important?
- Prevents accidental or inappropriate inheritance.
- Makes design intent explicit.

### Problem: Class can be derived from unintentionally
```cpp
class Point {
 public:
  Point(int x, int y) : x_(x), y_(y) {}
  int GetX() const { return x_; }
  int GetY() const { return y_; }

  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }

 private:
  int x_ = 0;
  int y_ = 0;
};

class NamedPoint : public Point {
 public:
  NamedPoint(int x, int y, std::string name)
      : Point(x, y), name_(std::move(name)) {
    puts("NamedPoint()");
  }
  ~NamedPoint() { puts("~NamedPoint()"); }
  const std::string& GetName() const { return name_; }

 private:
  const std::string name_;
};
```

### Fix: Mark class as `final`
```cpp
class Point final {
 public:
  Point(int x, int y) : x_(x), y_(y) {}
  int GetX() const { return x_; }
  int GetY() const { return y_; }

  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }

 private:
  int x_ = 0;
  int y_ = 0;
};

// error: base 'Point' is marked 'final'
// class NamedPoint : public Point {
//                           ^
// class NamedPoint : public Point {
//  public:
//   NamedPoint(int x, int y, std::string name)
//       : Point(x, y), name_(std::move(name)) {
//     puts("NamedPoint()");
//   }
//   ~NamedPoint() { puts("~NamedPoint()"); }
//   const std::string& GetName() const { return name_; }

//  private:
//   const std::string name_;
// };
```

#### Nuances
- Marking a class as `final` also prevents virtual inheritance.
- Use `final` for classes that are not intended to be extended, such as utility or value types.
- If you want to prevent only some methods from being overridden, use `final` on those methods instead.
