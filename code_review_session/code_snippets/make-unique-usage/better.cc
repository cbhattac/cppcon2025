#include <memory>
#include <tuple>

struct Widget1 {
  Widget1(int) {}
  // Other stuff.
};

struct Widget2 {
  Widget2(int) {}
  // Other stuff.
};

void Foo(std::unique_ptr<Widget1> w1, std::unique_ptr<Widget2> w2) {
  std::ignore = w1;
  std::ignore = w2;
}

int main() {
  Foo(std::make_unique<Widget1>(1), std::make_unique<Widget2>(2));
}