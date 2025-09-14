#include <algorithm>
#include <iostream>
#include <set>

// clang-tidy check: readability-container-contains
// Clang-C++ warning: none
void PrintIfContains(const std::set<int>& s, int value) {
  if (std::find(s.begin(), s.end(), value) != s.end()) {
    std::cout << "Found\n";
  }
}

void PrintIfContains2(const std::set<int>& s, int value) {
  if (std::ranges::find(s, value) != s.end()) {
    std::cout << "Found\n";
  }
}

void PrintIfContains3(const std::set<int>& s, int value) {
  if (s.find(value) != s.end()) {
    std::cout << "Found\n";
  }
}

int main() {
  std::set<int> s{1, 2, 3};
  PrintIfContains(s, 2);
  PrintIfContains2(s, 2);
  PrintIfContains3(s, 2);
}

/*
Found
Found
Found
*/

// -checks=readability-container-contains
/*
warning: use 'contains' to check for membership [readability-container-contains]
   if (s.find(value) != s.end()) {
         ^~~~        ~~~~~~~~~~
         contains
*/