#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> GetNameById(int id) {
  if (id == 42) {
    return "Denver";
  }
  return std::nullopt;
}

int main() {
  if (const auto name = GetNameById(42)) {
    std::cout << "Name: " << *name << '\n';
  } else {
    std::cout << "Not found\n";
  }
}
