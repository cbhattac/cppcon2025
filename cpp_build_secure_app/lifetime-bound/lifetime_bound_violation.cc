#include <iostream>
#include <string>

std::string_view GetOrDefault(std::string_view str, std::string_view key) {
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
  const auto v2 = GetOrDefault(GetStr(), "hello|");
  std::cout << v2 << '\n';
}

/*
world
c�Q29��a longer string
*/