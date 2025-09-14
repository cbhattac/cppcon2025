// TODO: Not manually validated.

#include <string>

void Foo(std::string str) {
  std::string copy = std::move(str);  // Efficient move.
  // Use `copy`.
  std::ignore = copy;
}

int main() {
  Foo("example");
}
