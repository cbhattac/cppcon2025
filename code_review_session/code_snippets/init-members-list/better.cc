#include <string>

class Person {
 public:
  Person(const std::string& name, int age) : name_(name), age_(age) {}

  // To remove `-Wunused-private-field` error.
  int age() const { return age_; }

 private:
  std::string name_;
  int age_ = 0;
};

class MyClass {
 public:
  MyClass() : member_a_(10), member_b_(member_a_ + 1) {}

  // To remove `-Wunused-private-field` error.
  int member_b() const { return member_b_; }

 private:
  // Declared first, but initialized second in the list.
  int member_a_ = 0;
  // Declared second, but initialized first in the list.
  int member_b_ = 0;
};

int main() {}
