#include <iostream>

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

int main() {
  const Point p{20, 30};
  p.Print();
  return 0;
}

// (20, 30)
