#include <iostream>
#include <string>
#include <variant>

// clang-tidy check: none
// Clang-C++ warning: none

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
  void operator()(int v) const {
    if (v != 0) {  // 0 is "unset".
      std::cout << "int: " << v << '\n';
    }
  }
  void operator()(const std::string& s) const {
    std::cout << "str: " << s << '\n';
  }
  void operator()(const NoDefaultConstructor& n) const {
    std::cout << "NoDefault: " << n.value << '\n';
  }
};

template <typename T>
  requires IsVariantV<T>
void TestVariant(const T& v) {
  std::visit(Visitor{}, v);
}

int main() {
  std::variant<int, std::string> v;
  TestVariant(v);
  v.emplace<std::string>("hello");
  TestVariant(v);

  // Does not compile
  // std::variant<NoDefaultConstructor, std::string> v3;
  std::variant<std::string, NoDefaultConstructor> v2;
  TestVariant(v2);
  v2.emplace<NoDefaultConstructor>(10);
  TestVariant(v2);
}

/*
str: hello
str:
NoDefault: 10
*/