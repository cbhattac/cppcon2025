#include <iostream>
#include <string>

class MyClass {
 public:
  MyClass(const std::string& s) : s_(s) {}
  void Print() const { std::cout << s_ << '\n'; }

 private:
  std::string_view s_;
};

std::string GetStr() {
  return "hello, how are you!";
}

int main() {
  MyClass m1{GetStr()};
  m1.Print();
  const std::string s{"hello"};
  MyClass m2{s};
  m2.Print();
}

/*
>5�Mt?5�Mtk1,�
hello
*/