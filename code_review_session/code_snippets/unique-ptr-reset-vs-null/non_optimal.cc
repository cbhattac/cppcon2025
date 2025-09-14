#include <memory>

// clang-tidy check: none
// Clang-C++ warning: none
struct A {
  // Some stuff.
};

class B {
 public:
  // Functions related to creation of `a_`.

  void Reset() { a_ = nullptr; }

 private:
  std::unique_ptr<A> a_;
};

void Foo() {
  auto a = std::make_unique<A>();
  // Use `a`.
  a = nullptr;
  // Other stuff
}

int main() {}