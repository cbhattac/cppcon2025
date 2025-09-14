#include <memory>

// clang-tidy check: none
// Clang-C++ warning: none

class MyClass {
 public:
  void DoSomething() {}
  // Other stuff.
};

int main() {
  auto my_class = std::make_unique<MyClass>();
  my_class->DoSomething();
  // Use `my_class` to the end of scope.
}
