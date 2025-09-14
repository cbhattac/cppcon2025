#include <iostream>
#include <string>

class MyClass {
 public:
  MyClass(std::string str) : str_(std::move(str)) {}
  const std::string& str() const& { return str_; }
  std::string str() && { return std::move(str_); }

 private:
  std::string str_;
};

int main() {
  MyClass m("hello");
  std::cout << m.str() << '\n';
  const auto& s = MyClass{"world"}.str();
  std::cout << s << '\n';
}

/*
hello
world
*/
