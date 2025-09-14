#include <iostream>
#include <string>

class MyClass {
 public:
  MyClass(const std::string& s [[clang::lifetimebound]]) : s_(s) {}
  void Print() const { std::cout << s_ << '\n'; }

 private:
  std::string_view s_;
};

std::string GetStr() {
  return "hello, how are you!";
}

int main() {
  /*
  error: temporary whose address is used as value of local variable 'm1' will be
  destroyed at the end of the full-expression [-Werror,-Wdangling] MyClass
  m1{GetStr()};
                ^~~~~~~~
  */
  // MyClass m1{GetStr()};
  // m1.Print();
  const std::string s{"hello"};
  MyClass m2{s};
  m2.Print();
}

/*
hello
*/