#include <tuple>

// clang-tidy check: none
// Clang-C++ warning: none
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