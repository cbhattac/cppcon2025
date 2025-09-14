#include <stdio.h>

#include <string>

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

class NamedPoint {
 public:
  NamedPoint(int x, int y, std::string name)
      : pt_(x, y), name_(std::move(name)) {
    puts("NamedPoint()");
  }
  ~NamedPoint() { puts("~NamedPoint()"); }
  const std::string& GetName() const { return name_; }
  const Point& GetPoint() const { return pt_; }
  Point& GetPoint() { return pt_; }

 private:
  Point pt_;
  const std::string name_;
};

void Foo(const Point& pt) {
  // Use it.
}

int main() {
  Foo(NamedPoint{10, 20, "My point"}.GetPoint());
}

// NamedPoint()
// ~NamedPoint()