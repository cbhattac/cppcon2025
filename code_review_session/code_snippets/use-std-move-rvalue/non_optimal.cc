// TODO: Not manually validated.

#include <string>

// clang-tidy check: none
// Clang-C++ warning: none
void Foo(std::string str) {
  std::string copy = str;  // Inefficient copy.
  // Use `copy`.
  std::ignore = copy;
}

int main() {
  Foo("example");
}
