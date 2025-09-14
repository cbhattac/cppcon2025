#include <stdio.h>

#include <functional>
#include <string>
#include <type_traits>
#include <vector>

template <typename... Args>
void CallAll(const std::vector<std::function<void(const Args&...)>>& funcs,
             Args&&... args) {
  for (const auto& func : funcs) {
    func(args...);
  }
}

void Func1(const std::string& s) {
  printf("Func1(%s)\n", s.c_str());
}

void Func2(const std::string& s) {
  printf("Func2(%s)\n", s.c_str());
}

int main() {
  std::vector<std::function<void(const std::string&)>> funcs{Func1, Func2};
  CallAll(funcs, std::string{"hello world"});
}

/*
Func1(hello world)
Func2(hello world)
*/