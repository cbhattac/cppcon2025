#include <memory>

struct A {
  // Some stuff.
};

class B {
 public:
  // Functions related to creation of `a_`.

  void Reset() {
    a_.reset();
  }

 private:
  std::unique_ptr<A> a_;
};

void Foo() {
  auto a = std::make_unique<A>();
  // Use.
  a.reset();
  // Other stuff 
}

int main() {
}