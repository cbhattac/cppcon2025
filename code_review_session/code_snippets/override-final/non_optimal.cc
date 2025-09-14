#include <stdio.h>

// clang-tidy check: modernize-use-override
// Clang-C++ warning: -Wsuggest-override

class Base {
 public:
  virtual ~Base() = default;
  virtual void Foo() { puts("Base::Foo"); }
};

class Derived : public Base {
 public:
  void Foo() { puts("Derived::Foo"); }
};

int main() {}

// With the `-Wsuggest-override` warning enabled, this code will generate a warning
/*
error: 'Foo' overrides a member function but is not marked 'override' [-Werror,-Wsuggest-override]
   void Foo() { puts("Derived::Foo"); }
        ^
note: overridden virtual function is here
   virtual void Foo() { puts("Base::Foo"); }
                ^
*/
// With -checks=modernize-use-override
/*
warning: annotate this function with 'override' or (rarely) 'final' [modernize-use-override]
   void Foo() { puts("Derived::Foo"); }
        ^
              override
*/