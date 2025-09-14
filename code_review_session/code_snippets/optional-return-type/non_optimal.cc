#include <iostream>
#include <string>

// clang-tidy check: none
// Clang-C++ warning: none
bool GetNameById(int id, std::string* name) {
  if (id == 42) {
    *name = "Chromium";
    return true;
  }
  return false;
}

int main() {
  std::string name;
  if (GetNameById(42, &name)) {
    std::cout << "Name: " << name << '\n';
  } else {
    std::cout << "Not found\n";
  }
}
