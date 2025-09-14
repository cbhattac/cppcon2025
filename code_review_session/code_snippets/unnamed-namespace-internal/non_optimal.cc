// non_optimal.cc
#include <iostream>

// clang-tidy check: misc-use-anonymous-namespace
// Clang-C++ warning: none
static void InternalFunction() {
  std::cout << "Internal function (static)\n";
}

static int internal_var = 42;

int main() {
  InternalFunction();
  std::cout << "internal_var: " << internal_var << "\n";
  return 0;
}
