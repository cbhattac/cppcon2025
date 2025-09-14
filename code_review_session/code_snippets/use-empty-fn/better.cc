// TODO: Not manually validated.

#include <vector>

void Check(const std::vector<int>& v) {
  if (v.empty()) {
    // Do something.
  }
}

int main() {
  std::vector<int> v;
  Check(v);
}
