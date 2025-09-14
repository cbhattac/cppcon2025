#include <memory>

// clang-tidy check: none
// Clang-C++ warning: none
class Widget {};

class Foo {
 public:
  Foo() : ptr_(nullptr) {}
  // Other stuff.

 private:
  std::unique_ptr<Widget> ptr_;
  std::unique_ptr<Widget> ptr2_{nullptr};
};

int main() {
  [[maybe_unused]] std::unique_ptr<Widget> w{nullptr};

  [[maybe_unused]] Foo f;
}
