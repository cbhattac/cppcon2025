#include <iostream>

// clang-tidy check: none
// Clang-C++ warning: none
void Foo(bool show, int val) {
  int final_value = 0;
  if (show) {
    if (val == 1) {
      final_value = 3;
    } else if (val <= 100) {
      final_value = 4;
    } else {
      final_value = 5;
    }
  } else {
    if (val == 1) {
      final_value = 6;
    } else {
      final_value = 7;
    }
  }
  // Use `final_value`.
  std::cout << final_value << '\n';
}

int main() {
  Foo(/*show=*/true, 10);
}

// 4