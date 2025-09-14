#include <iostream>
#include <string>

class MyClass {
 public:
  MyClass(std::string str) : str_(std::move(str)) {}
  const std::string& str() const { return str_; }

 private:
  std::string str_;
};

int main() {
  MyClass m("hello");
  std::cout << m.str() << '\n';
  const auto& s = MyClass{"world"}.str();
  std::cout << s << '\n';
}

/*
hello
world
*/

// Fails to compile on GCC with -Werror=dangling-pointer
/*
In function 'int main()':
<source>:16:34: note: unnamed temporary defined here
   const auto& s = MyClass{"world"}.str();
                                  ^
*/
