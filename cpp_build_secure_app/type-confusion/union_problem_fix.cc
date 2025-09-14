#include <iostream>
#include <new>
#include <string>
#include <vector>

struct Wrapper {
  std::variant<std::monostate, std::string, std::vector<int>> u;

  void SetString(const std::string& str) { u = str; }
  void SetVector(std::vector<int> vv) { u = std::move(vv); }

  void Print() const { std::visit(Visitor{}, u); }

  struct Visitor {
    void operator()(const std::string& s) const {
      std::cout << "String: " << s << '\n';
    }
    void operator()(const std::vector<int>& v) const {
      std::cout << "Vector: ";
      for (const auto i : v) {
        std::cout << i << ' ';
      }
      std::cout << '\n';
    }
    void operator()(std::monostate) const { std::cout << "Unset\n"; }
  };
};

int main() {
  Wrapper w;
  w.Print();
  w.SetString("hello world, this is long");
  w.Print();
  w.SetVector({1, 2, 3});
  w.Print();
}

/*
Unset
String: hello world, this is long
Vector: 1 2 3 
*/