#include <memory>

// clang-tidy check: none
// Clang-C++ warning: none
class Widget {};

class Foo {
 public:
  Foo() = default;
  // Other stuff.

 private:
  std::unique_ptr<Widget> ptr_;
  std::unique_ptr<Widget> ptr2_;
};

int main() {
  [[maybe_unused]] std::unique_ptr<Widget> w;

  [[maybe_unused]] Foo f;
}
