#include <string>
#include <utility>
#include <vector>

bool IsInteresting(const std::string& s) {
  return s.length() > 3u;
}

std::vector<std::string> GetStringVec(std::string s) {
  std::vector<std::string> vec;
  if (IsInteresting(s)) {
    vec.push_back(s);
    vec.push_back(std::move(s));
  } else {
    vec.push_back(std::move(s));
  }
  return vec;
}

int main() {
  std::ignore = GetStringVec("Hello world!!");
}