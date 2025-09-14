#include <stdlib.h>

#include <iostream>

// clang-tidy check: none
// Clang-C++ warning: none

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
  if (IsConditionOneTrue()) {
    some_var += 1;
    Foo(some_var);
    Bar(some_var);
    return some_var;
  }
  if (AnotherConditionIsTrue()) {
    some_var += 2;
  }
  if (IsConditionTwoTrue()) {
    some_var += 1;
    Foo(some_var);
    Bar(some_var);
    return some_var;
  }
  if (OneMoreConditionIsTrue()) {
    some_var += 3;
  }
  some_var += 1;
  Foo(some_var);
  Bar(some_var);
  return some_var;
}

int main(int argc, char* argv[]) {
  return Baz(argc);
}
