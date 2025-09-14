#include <iostream>
#include <string>
#include <variant>

class MyClass final {
 public:
  MyClass(int v) : value_(v) {}
  MyClass(std::string&& s) : value_(std::move(s)) {}

  template <typename Visitor>
  void Visit(Visitor&& v) const {
    std::visit(v, value_);
  }

 private:
  std::variant<int, std::string> value_;
};

template <class... Ts>
struct Overloaded : Ts... {
  using Ts::operator()...;
};

// Seems necessary for GCC for C++20.
template <class... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

void Print(const MyClass& c) {
  c.Visit(Overloaded(
      [](int v) { std::cout << "Int: " << v << '\n'; },
      [](const std::string& s) { std::cout << "String: " << s << '\n'; }));
}

int main() {
  const MyClass c1("Hello");
  const MyClass c2(10);
  Print(c1);
  Print(c2);
  std::variant<int, std::string> v = 42;
  std::visit([](const auto& val) { std::cout << val << '\n'; }, v);
  return 0;
}

/*
String: Hello
Int: 10
42
*/