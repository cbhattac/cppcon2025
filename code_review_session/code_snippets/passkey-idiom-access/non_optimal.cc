#include <iostream>

// clang-tidy check: none
// Clang-C++ warning: none

class Bar;

class Foo {
 public:
  int GetSecret() const { return secret_; }

 private:
  friend class Bar;

  void SetSecret(int value) { secret_ = value; }

  int secret_ = 0;
};

class Bar {
 public:
  void ChangeFooSecret(Foo& foo, int value) {
    foo.SetSecret(value);  // Allowed due to friendship.
    // Also allowed due to friendship!!!!
    foo.secret_ = 10;
  }
};

int main() {
  Foo foo;
  Bar bar;
  bar.ChangeFooSecret(foo, 42);
  std::cout << foo.GetSecret() << '\n';
}

// 10