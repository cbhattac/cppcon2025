#include <iostream>

// clang-tidy check: readability-make-member-function-const
// Clang-C++ warning: none
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

int main() {
  Point p{20, 30};
  p.Print();
  return 0;
}

// (20, 30)

// -checks=readability-make-member-function-const
/*
warning: method 'GetX' can be made const [readability-make-member-function-const]
   int GetX() { return x; }
       ^
              const
warning: method 'GetY' can be made const [readability-make-member-function-const]
   int GetY() { return y; }
       ^
              const
method 'Print' can be made const [readability-make-member-function-const]
   void Print() { std::cout << "(" << x << ", " << y << ")\n"; }
        ^
                const
*/
