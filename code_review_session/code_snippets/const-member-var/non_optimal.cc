#include <stdio.h>

enum class SomeEnum;

// clang-tidy check: none
// Clang-C++ warning: cppcoreguidelines-pro-type-member-init
struct SomeClass {
  // Won't change this after constructor.
  SomeEnum e;

  SomeEnum GetE() const { return e; }
};

int main() {
  SomeClass s;
  printf("%d\n", static_cast<int>(s.GetE()));
}

// 1953334856

/* Fails with GCC
In member function 'SomeEnum SomeClass::GetE() const',
    inlined from 'int main()':
error: 's.SomeClass::e' is used uninitialized [-Werror=uninitialized]
   SomeEnum GetE() const { return e; }
                                  ^
In function 'int main()':
note: 's' declared here
   SomeClass s;
             ^
*/

// -checks=-*,cppcoreguidelines-pro-type-member-init
/*
warning: uninitialized record type: 's' [cppcoreguidelines-pro-type-member-init]
   SomeClass s;
   ^
              {}
*/