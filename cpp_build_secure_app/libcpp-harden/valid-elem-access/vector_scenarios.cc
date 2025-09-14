#include <iostream>
#include <vector>

void ProblemVector(std::vector<int> v) {
  // Will fire when called on empty vector.
  const auto f = v.front();
  std::cout << f << '\n';

  // Will fire when called on empty vector.
  const auto b = v.back();
  std::cout << b << '\n';

  // Will fire when called on empty vector.
  v.pop_back();

  v.push_back(1);
  v.push_back(2);
  // Will fire when called with index out of range.
  std::cout << v[2] << '\n';

  // Will fire when called with end().
  auto it = v.erase(v.end());
  std::cout << (it != v.end()) << '\n';
}

int main() {
  ProblemVector({});
}
