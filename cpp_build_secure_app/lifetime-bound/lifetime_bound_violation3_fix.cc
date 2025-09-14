#include <iostream>
#include <string>

class MyClass {
 public:
  MyClass(std::string str) : str_(std::move(str)) {}
  const std::string& str() const [[clang::lifetimebound]] { return str_; }

 private:
  std::string str_;
};

int main() {
  MyClass m("hello");
  std::cout << m.str() << '\n';
  // clang-format off
  /*
  error: temporary bound to local reference 's' will be destroyed at the end of the full-expression [-Werror,-Wdangling]
      const auto& s = MyClass{"world"}.str();
                      ^~~~~~~~~~~~~~~~
  */
  // clang-format on
  // const auto& s = MyClass{"world"}.str();
  // std::cout << s << '\n';
}

/*
hello
*/
