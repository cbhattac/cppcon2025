### Use `<=>` (spaceship operator) for comparisons.

Before C++20, defining all comparison operators for a class was verbose and error-prone. The C++20 spaceship operator (`<=>`) simplifies this by allowing the compiler to generate all six comparison operators (`==`, `!=`, `<`, `<=`, `>`, `>=`) from a single definition.

The spaceship operator returns a value of a comparison category type (`std::strong_ordering`, `std::weak_ordering`, or `std::partial_ordering`) which is then used by the compiler to deduce the other comparison operators. For simple class members, `default` can be used to let the compiler generate the operator.

#### Manually defining all comparison operators is verbose and error-prone.

```cpp
#include <tuple>

class Point {
 public:
  Point(int x, int y) : x_(x), y_(y) {}

  bool operator==(const Point& other) const {
    return x_ == other.x_ && y_ == other.y_;
  }
  bool operator<(const Point& other) const {
    return std::tie(x_, y_) < std::tie(other.x_, other.y_);
  }
  bool operator<=(const Point& other) const { return !(*this > other); }
  bool operator>(const Point& other) const { return other < *this; }
  bool operator>=(const Point& other) const { return !(*this < other); }

 private:
  int x_ = 0;
  int y_ = 0;
};

int main() {
  const Point p1(1, 2);
  const Point p2(3, 4);

  // Use the comparison operators.
  std::ignore = (p1 == p2);
  std::ignore = (p1 != p2);
  std::ignore = (p1 < p2);
  std::ignore = (p1 <= p2);
  std::ignore = (p1 > p2);
  std::ignore = (p1 >= p2);
}
```

#### Fix approach:
```cpp
#include <tuple>

class Point {
 public:
  Point(int x, int y) : x_(x), y_(y) {}
  auto operator<=>(const Point&) const noexcept = default;

 private:
  int x_ = 0;
  int y_ = 0;
};

int main() {
  const Point p1(1, 2);
  const Point p2(3, 4);

  // Use the comparison operators.
  std::ignore = (p1 == p2);
  std::ignore = (p1 != p2);
  std::ignore = (p1 < p2);
  std::ignore = (p1 <= p2);
  std::ignore = (p1 > p2);
  std::ignore = (p1 >= p2);
}
```

