#include <iostream>
#include <string>

std::string_view GetOrDefault(std::string_view str [[clang::lifetimebound]],
                              std::string_view key) {
  if (str.starts_with(key)) {
    return str.substr(key.size());
  }
  return std::string_view{};
}

std::string GetStr() {
  return "hello|world|and a longer string";
}

int main() {
  const auto v1 = GetOrDefault("hello|world", "hello|");
  std::cout << v1 << '\n';
  /*
  error: object backing the pointer will be destroyed at the end of the
  full-expression [-Werror,-Wdangling-gsl] const auto v2 =
  GetOrDefault(GetStr(), "hello|");
                                ^~~~~~~~
  */
  // const auto v2 = GetOrDefault(GetStr(), "hello|");
  // std::cout << v2 << '\n';
}

/*
world
*/