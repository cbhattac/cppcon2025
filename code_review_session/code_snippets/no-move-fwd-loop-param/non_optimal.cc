#include <stdio.h>

#include <functional>
#include <string>
#include <type_traits>
#include <vector>

// clang-tidy check: bugprone-use-after-move
// Clang-C++ warning: none

template <typename... Args>
void CallAll(const std::vector<std::function<void(Args...)>>& funcs,
             Args&&... args) {
  for (const auto& func : funcs) {
    func(std::forward<Args>(args)...);
  }
}

void Func1(std::string s) {
  printf("Func1(%s)\n", s.c_str());
}

void Func2(std::string s) {
  printf("Func2(%s)\n", s.c_str());
}

int main() {
  std::vector<std::function<void(std::string)>> funcs{Func1, Func2};
  CallAll(funcs, std::string{"hello world"});
}

/*
Func1(hello world)
Func2()
*/

// --checks=bugprone-use-after-move
/*
warning: 'args' used after it was forwarded [bugprone-use-after-move]
     func(std::forward<Args>(args)...);
                             ^
note: forward occurred here
     func(std::forward<Args>(args)...);
          ^
note: the use happens in a later loop iteration than the forward
     func(std::forward<Args>(args)...);
                             ^
*/