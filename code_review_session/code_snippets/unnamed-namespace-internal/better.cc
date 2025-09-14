// better.cc
#include <iostream>

namespace {
void InternalFunction() {
  std::cout << "Internal function (unnamed namespace)\n";
}

int internal_var = 42;
}  // namespace

int main() {
  InternalFunction();
  std::cout << "internal_var: " << internal_var << "\n";
  return 0;
}
