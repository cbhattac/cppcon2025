#include <algorithm>
#include <iostream>
#include <vector>

void RemoveOdd(std::vector<int>& v) {
  v.erase(std::remove_if(v.begin(), v.end(), [](int x) { return x % 2 != 0; }),
          v.end());
}

void RemoveNumber(std::vector<int>& v, int number) {
  v.erase(std::remove(v.begin(), v.end(), number), v.end());
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