#include <optional>

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
  std::optional<A> a_;
};

// B.cc
void B::DoSomething(A::WorkType type) {
  if (!a_) {
    a_.emplace();
  }
  a_->DoSomething(type);
}

// main.cc
bool ShouldCreateOptional(int param) {
  return param > 0;
}

bool ShouldCallDoSomething(int param) {
  return param % 2 == 0;
}

void Foo(int param) {
  std::optional<A> local_a;

  if (ShouldCreateOptional(param)) {
    local_a.emplace();
  }
  // Do some other stuff.
  if (local_a && ShouldCallDoSomething(param)) {
    local_a->DoSomething(A::WorkType::kType1);
  }
}

int main() {}
