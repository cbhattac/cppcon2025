#include <iostream>
#include <optional>
#include <string>

// clang-tidy check: none
// Clang-C++ warning: none

class MyClass final {
 public:
  MyClass(int v) : int_value_(v) {}
  MyClass(std::string&& s) : str_value_(std::move(s)) {}

  bool HasIntValue() const { return !!int_value_; }
  bool HasStringValue() const { return !!str_value_; }

  const int* GetInt() const;
  const std::string* GetStr() const;

 private:
  std::optional<int> int_value_;
  std::optional<std::string> str_value_;
};

const int* MyClass::GetInt() const {
  return int_value_ ? &*int_value_ : nullptr;
}

const std::string* MyClass::GetStr() const {
  return str_value_ ? &*str_value_ : nullptr;
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
}

/*
String: Hello
Int: 10
*/
