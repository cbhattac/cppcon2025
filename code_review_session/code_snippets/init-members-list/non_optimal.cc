#include <string>

// clang-tidy check: none
// Clang-C++ warning: none
class Person {
 public:
  Person(const std::string& name, int age) {
    name_ = name;
    age_ = age;
  }

 private:
  std::string name_;
  int age_ = 0;
};

class MyClass {
 public:
  MyClass() {
    member_b_ = member_a_ + 1;
    member_a_ = 10;
  }

 private:
  // Declared first, but initialized second in the list.
  int member_a_ = 0;
  // Declared second, but initialized first in the list.
  int member_b_ = 0;
};

int main() {}
