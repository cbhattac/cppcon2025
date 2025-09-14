#include <iostream>
#include <string>
#include <variant>

// clang-tidy check: none
// Clang-C++ warning: none

class MyClass final {
 public:
  MyClass(int v) : value_(v) {}
  MyClass(std::string&& s) : value_(std::move(s)) {}

  bool HasIntValue() const;
  bool HasStringValue() const;

  const int* GetInt() const;
  const std::string* GetStr() const;

 private:
  std::variant<int, std::string> value_;
};

bool MyClass::HasIntValue() const {
  return std::holds_alternative<int>(value_);
}

bool MyClass::HasStringValue() const {
  return std::holds_alternative<std::string>(value_);
}

const int* MyClass::GetInt() const {
  return std::get_if<int>(&value_);
}

const std::string* MyClass::GetStr() const {
  return std::get_if<std::string>(&value_);
}

void Print(const MyClass& c) {
  if (c.HasIntValue()) {
    std::cout << "Int: " << *c.GetInt() << '\n';
  } else {
    std::cout << "String: " << *c.GetStr() << '\n';
  }
}

int main() {
  const MyClass c1("Hello");
  const MyClass c2(10);
  Print(c1);
  Print(c2);
  std::variant<int, std::string> v = 42;
  if (auto p = std::get_if<int>(&v)) {
    std::cout << *p << '\n';
  } else if (auto q = std::get_if<std::string>(&v)) {
    std::cout << *q << '\n';
  }
  return 0;
}

/*
String: Hello
Int: 10
42
*/