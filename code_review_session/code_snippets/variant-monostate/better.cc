#include <iostream>
#include <string>
#include <variant>

template <typename T>
struct IsVariant : std::false_type {};

template <typename... Args>
struct IsVariant<std::variant<Args...>> : std::true_type {};

template <typename T>
inline constexpr bool IsVariantV = IsVariant<T>::value;

struct NoDefaultConstructor {
  explicit NoDefaultConstructor(int i) : value(i) {}
  int value;
};

struct Visitor {
  void operator()(int v) const { std::cout << "int: " << v << '\n'; }
  void operator()(const std::string& s) const {
    std::cout << "str: " << s << '\n';
  }
  void operator()(const NoDefaultConstructor& n) const {
    std::cout << "NoDefault: " << n.value << '\n';
  }
  void operator()(std::monostate) const { std::cout << "Unset\n"; }
};

template <typename T>
  requires IsVariantV<T>
void TestVariant(const T& v) {
  std::visit(Visitor{}, v);
}

int main() {
  std::variant<std::monostate, int, std::string> v;
  TestVariant(v);
  v.emplace<std::string>("hello");
  TestVariant(v);

  std::variant<std::monostate, NoDefaultConstructor, std::string> v2;
  TestVariant(v2);
  v2.emplace<NoDefaultConstructor>(10);
  TestVariant(v2);
}

/*
Unset
str: hello
Unset
NoDefault: 10
*/