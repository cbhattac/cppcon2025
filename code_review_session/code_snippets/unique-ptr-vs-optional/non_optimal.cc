#include <memory>

// clang-tidy check: none
// Clang-C++ warning: none

// A.h
struct A {
  enum class WorkType { kType1, kType2 };
  void DoSomething(WorkType) {}
};

// B.h.
class B {
 public:
  // Will need to included A header to get `A::WorkType`.
  void DoSomething(A::WorkType type);

 private:
  std::unique_ptr<A> a_;
};

// B.cc
void B::DoSomething(A::WorkType type) {
  if (!a_) {
    a_ = std::make_unique<A>();
  }
  a_->DoSomething(type);
}

// main.cc
bool ShouldCreateUniquePtr(int param) {
  return param > 0;
}

bool ShouldCallDoSomething(int param) {
  return param % 2 == 0;
}

void Foo(int param) {
  std::unique_ptr<A> local_a;

  if (ShouldCreateUniquePtr(param)) {
    local_a = std::make_unique<A>();
  }
  // Do some other stuff.
  if (local_a && ShouldCallDoSomething(param)) {
    local_a->DoSomething(A::WorkType::kType1);
  }
}

int main() {}
