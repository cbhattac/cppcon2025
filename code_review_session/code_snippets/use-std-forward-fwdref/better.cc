#include <stdio.h>

#include <memory>
#include <string>
#include <tuple>

class MyClass {
 public:
  MyClass(const char* str) : s_(str) { puts("MyClass(const char*)"); }
  MyClass(const std::string& str) : s_(str) {
    puts("MyClass(const std::string&)");
  }
  MyClass(std::string&& str) : s_(std::move(str)) {
    puts("MyClass(std::string&&)");
  }

 private:
  std::string s_;
};

template <typename T, typename... Args>
std::unique_ptr<T> Create(Args&&... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

int main() {
  // const char[6].
  std::ignore = Create<MyClass>("hello");
  // prvalue: std::string&&.
  std::ignore = Create<MyClass>(std::string{"hello"});
  std::string s{"hello"};
  // lvalue: std::string&.
  std::ignore = Create<MyClass>(s);
  // xvalue: std::string&&.
  std::ignore = Create<MyClass>(std::move(s));
}

/*
MyClass(const char*)
MyClass(std::string&&)
MyClass(const std::string&)
MyClass(std::string&&)
*/