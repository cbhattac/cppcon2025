#include <iostream>
#include <memory>

#include "base/memory/raw_ptr.h"

class SomeClass {
 public:
  SomeClass(int* p) : p_(p) {}
  int GetSum(int i) const { return i + *p_; }

 private:
  raw_ptr<int> p_ = nullptr;
};

int main() {
  char c = '\0';
  std::cin >> c;
  std::cout << c << '\n';
  std::unique_ptr<SomeClass> p;
  {
    int i = 20;
    p = std::make_unique<SomeClass>(&i);
  }
  {
    int j = 20;
    std::cout << p->GetSum(j) << '\n';
  }
  {
    auto pi = std::make_unique<int>(30);
    p = std::make_unique<SomeClass>(pi.get());
    std::cout << p->GetSum(*pi) << '\n';
  }
  std::cout << p->GetSum(40) << '\n';
}
