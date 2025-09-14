#include <expected>
#include <iostream>
#include <string>

// clang-tidy check: none
// Clang-C++ warning: none
std::expected<int, std::string> ParseInt(const std::string& input) {
  try {
    return std::stoi(input);
  } catch (const std::exception& e) {
    return std::unexpected<std::string>(e.what());
  }
}

void TestParse(const std::string& str) {
  std::cout << str << ": ";
  if (const auto result = ParseInt(str)) {
    std::cout << "Parsed: " << *result << '\n';
  } else {
    std::cout << "Error: " << result.error() << '\n';
  }
}

int main() {
  TestParse("100");
  TestParse("100 and some");
  TestParse("hundred");
}

// 100: Parsed: 100
// 100 and some: Parsed: 100
// hundred: Error: stoi: no conversion