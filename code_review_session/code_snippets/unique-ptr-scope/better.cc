#include <memory>

class MyClass {
 public:
  void DoSomething() {}
  // Other stuff.
};

int main() {
  MyClass my_class;
  my_class.DoSomething();
  // Use `my_class` to the end of scope.
}