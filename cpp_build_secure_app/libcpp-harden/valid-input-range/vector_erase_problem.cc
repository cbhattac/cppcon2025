#include <vector>

// The calls to vector erase will all "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used, this will work fine.

void ProblemVector(std::vector<int> v) {
  // Will flag when called with first > last.
  v.erase(v.end(), v.begin());
}

int main() {
  std::vector<int> v;
  v.push_back(10);
  ProblemVector(v);
}