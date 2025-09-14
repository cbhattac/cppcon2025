#include <algorithm>
#include <iostream>
#include <vector>

void RemoveOdd(std::vector<int>& v) {
  std::erase_if(v, [](int x) { return x % 2 != 0; });
}

void RemoveNumber(std::vector<int>& v, int number) {
  std::erase(v, number);
}

int main() {
  std::vector<int> v{1, 2, 3, 4, 5};
  RemoveOdd(v);
  RemoveNumber(v, 2);
  for (int x : v) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}

// 4
