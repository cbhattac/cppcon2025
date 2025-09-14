// TODO: Not manually validated.

#include <vector>

// clang-tidy check: readability-container-size-empty
// Clang-C++ warning: none
void Check(const std::vector<int>& v) {
  if (v.size() == 0u) {
    // Do something.
  }
}

int main() {
  std::vector<int> v;
  Check(v);
}

// -checks=readability-container-size-empty
/*
warning: the 'empty' method should be used to check for emptiness instead of 'size' [readability-container-size-empty]
   if (v.size() == 0u) {
       ^~~~~~~~~~~~~~
       v.empty()
*/
