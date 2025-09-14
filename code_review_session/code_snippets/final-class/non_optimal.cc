#include <stdio.h>

#include <memory>
#include <string>

// clang-tidy check: none
// Clang-C++ warning: none
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

void Foo(std::unique_ptr<Point> pt) {
  // Use it.
}

int main() {
  Foo(std::make_unique<NamedPoint>(10, 20, "My point"));
  // `NamedPoint` destructor not called.
}

// NamedPoint