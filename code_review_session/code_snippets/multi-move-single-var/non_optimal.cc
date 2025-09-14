#include <string>
#include <utility>
#include <vector>

// clang-tidy check: bugprone-use-after-move
// Clang-C++ warning: none

bool IsInteresting(const std::string& s) {
  return s.length() > 3u;
}

std::vector<std::string> GetStringVec(std::string s) {
  std::vector<std::string> vec;
  vec.push_back(std::move(s));
  if (IsInteresting(s)) {
    vec.push_back(std::move(s));
  }
  return vec;
}

int main() {
  std::ignore = GetStringVec("Hello world!!");
}

// clang-tidy check: bugprone-use-after-move
/*
warning: 's' used after it was moved [bugprone-use-after-move]
   if (IsInteresting(s)) {
                     ^
note: move occurred here
   vec.push_back(std::move(s));
       ^
*/