#include <iostream>

class Foo {
 public:
  class PassKey {
    friend class Bar;
    PassKey() = default;
  };

  void SetSecret(int value, PassKey) { secret_ = value; }
  int GetSecret() const { return secret_; }

 private:
  int secret_ = 0;
};

class Bar {
 public:
  void ChangeFooSecret(Foo& foo, int value) {
    foo.SetSecret(value, Foo::PassKey{});
    // This will NOT COMPILE!!
    // foo.secret_ = 0;
  }
};

int main() {
  Foo foo;
  Bar bar;
  bar.ChangeFooSecret(foo, 42);
  std::cout << foo.GetSecret() << std::endl;
}

// 42
