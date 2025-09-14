# Make member functions const when appropriate

If a member function does not modify the state of the object, it should be marked as const.

**Problem:**
```cpp
class Point {
 public:
  Point() = default;
  Point(int x, int y) : x(x), y(y) {}

  int GetX() { return x; }
  int GetY() { return y; }

  void Print() { std::cout << "(" << x << ", " << y << ")\n"; }

 private:
  int x = 0;
  int y = 0;
};
```

**Fix:**
```cpp
class Point {
 public:
  Point() = default;
  Point(int x, int y) : x(x), y(y) {}

  int GetX() const { return x; }
  int GetY() const { return y; }

  void Print() const { std::cout << "(" << x << ", " << y << ")\n"; }

 private:
  int x = 0;
  int y = 0;
};
```
