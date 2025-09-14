#include <iostream>

void Foo(bool show, int val) {
  const int final_value = [&]() {
    if (show) {
      if (val == 1) {
        return 3;
      } else if (val <= 100) {
        return 4;
      }
      return 5;
    }
    if (val == 1) {
      return 6;
    }
    return 7;
  }();
  // Use `final_value`.
  std::cout << final_value << '\n';
}

int main() {
  Foo(/*show=*/true, 10);
}

// 4