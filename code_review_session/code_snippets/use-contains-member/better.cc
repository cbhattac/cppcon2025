#include <iostream>
#include <set>

void PrintIfContains(const std::set<int>& s, int value) {
  if (s.contains(value)) {
    std::cout << "Found\n";
  }
}

int main() {
  std::set<int> s{1, 2, 3};
  PrintIfContains(s, 2);
}

// Found
