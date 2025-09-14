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