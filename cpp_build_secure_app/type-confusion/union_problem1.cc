#include <iostream>
#include <new>
#include <string>
#include <vector>

struct Wrapper {
  bool is_string_;
  union U {
    std::string s;
    std::vector<int> v;
    U() {}
    ~U() {}  // destruction managed manually
  } u;

  void SetString(const std::string& str) {
    new (&u.s) std::string(str);
    is_string_ = true;
  }
  void SetVector(std::vector<int> vv) {
    new (&u.v) std::vector<int>(std::move(vv));
    is_string_ = false;
  }
  ~Wrapper() {
    if (is_string_) {
      u.s.~basic_string();
    } else {
      u.v.~vector();
    }
  }
  void Print() const {
    if (is_string_) {
      std::cout << "String: " << u.s << '\n';
    } else {
      std::cout << "Vector: ";
      for (const auto i : u.v) {
        std::cout << i << ' ';
      }
      std::cout << '\n';
    }
  }
};

void Foo(Wrapper* w) {
  std::cout << std::hex << (void*)w << '\n';
}

int main() {
  Wrapper w;
  Foo(&w);
}

// Crashes at runtime (-O3):
/*
free(): invalid pointer
Program terminated with signal: SIGSEGV
*/