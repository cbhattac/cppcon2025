#include <memory>

// clang-tidy check: none
// Clang-C++ warning: none

struct A {
  // Some stuff.
};

class B {
 public:
  ~B() {
    // Do some stuff.
    a_.reset();
    // No code after this.
  }
  // Functions related to creation of `a_`.

 private:
  std::unique_ptr<A> a_;
};

int main() {
  [[maybe_unused]] B b;
}
