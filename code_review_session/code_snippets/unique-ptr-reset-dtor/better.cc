#include <memory>

struct A {
  // Some stuff.
};

class B {
 public:
  ~B() {
    // Do some stuff.
  }
  // Functions related to creation of `a_`.

 private:
  std::unique_ptr<A> a_;
};

int main() {
  [[maybe_unused]] B b;
}
