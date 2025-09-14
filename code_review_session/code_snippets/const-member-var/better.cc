#include <stdio.h>

enum class SomeEnum;

struct SomeClass {
  // Won't change this after constructor.
  const SomeEnum e;

  SomeEnum GetE() const { return e; }
};

enum class SomeEnum {
   kA,
   kB,
   kC
};

int main() {
  SomeClass s{SomeEnum::kB};
  printf("%d\n", static_cast<int>(s.GetE()));
}
