#include <iostream>
#include <string>

// clang-tidy check: none
// Clang-C++ warning: none
bool ParseInt(const std::string& input, int* value, std::string* error) {
  try {
    *value = std::stoi(input);
    return true;
  } catch (const std::exception& e) {
    *error = e.what();
    return false;
  }
}

void TestParse(const std::string& str) {
  std::cout << str << ": ";
  int value = 0;
  std::string error;
  if (ParseInt(str, &value, &error)) {
    std::cout << "Parsed: " << value << '\n';
  } else {
    std::cout << "Error: " << error << '\n';
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