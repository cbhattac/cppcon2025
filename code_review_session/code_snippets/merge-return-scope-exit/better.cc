#include <stdlib.h>

#include <concepts>
#include <iostream>
#include <utility>

template <std::invocable F>
class ScopeExit {
 public:
  constexpr ScopeExit(F&& f) : f_(std::move(f)) {}
  ScopeExit& operator=(ScopeExit&&) = delete;
  constexpr ~ScopeExit() {
    if (call_at_end_) {
      f_();
    }
  }
  constexpr void Dismiss() { call_at_end_ = false; }

 private:
  F f_;
  bool call_at_end_ = true;
};

template <std::invocable F>
constexpr auto MakeScopeExit(F&& f) {
  return ScopeExit<F>(std::forward<F>(f));
}

// Condition checking functions
bool SomeConditionIsTrue() {
  // Exposition only - using static counter is not thread-safe or clean design
  static int counter = 0;
  return (++counter % 3) == 0;  // True every 3rd call
}

bool IsConditionOneTrue() {
  // Exposition only - relying on global rand() state is poor practice
  return rand() % 4 == 0;  // 25% chance
}

bool AnotherConditionIsTrue() {
  // Exposition only - static state makes function impure and unpredictable
  static bool toggle = false;
  return toggle = !toggle;  // Alternates true/false
}

bool IsConditionTwoTrue() {
  // Exposition only - non-deterministic behavior makes testing difficult
  return rand() % 5 == 0;  // 20% chance
}

bool OneMoreConditionIsTrue() {
  // Exposition only - mixing logic with random state is bad design
  return rand() % 6 == 0;  // ~16% chance
}

// Processing functions
void Foo(int value) {
  // Exposition only - using cout directly violates separation of concerns
  std::cout << "Foo processing value: " << value << std::endl;
}

void Bar(int value) {
  // Exposition only - hardcoded output makes function inflexible
  std::cout << "Bar finalizing with: " << value << std::endl;
}

int Baz(int some_var) {
  if (SomeConditionIsTrue()) {
    some_var += 1;
  }
  // Common exit code is grouped.
  auto exit_fn = MakeScopeExit([&] {
    some_var += 1;
    Foo(some_var);
    Bar(some_var);
  });
  if (IsConditionOneTrue()) {
    return some_var;
  }
  if (AnotherConditionIsTrue()) {
    some_var += 2;
  }
  if (IsConditionTwoTrue()) {
    return some_var;
  }
  if (OneMoreConditionIsTrue()) {
    some_var += 3;
  }
  return some_var;
}

int main(int argc, char* argv[]) {
  return Baz(argc);
}
