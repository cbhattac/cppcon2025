#include <memory>
#include <tuple>

// clang-tidy check: modernize-make-unique
// Clang-C++ warning: none

struct Widget1 {
  Widget1(int) {}
  // Other stuff.
};

struct Widget2 {
  Widget2(int) {}
  // Other stuff.
};

void Foo(std::unique_ptr<Widget1> w1, std::unique_ptr<Widget2> w2) {
  std::ignore = w1;
  std::ignore = w2;
}

int main() {
  Foo(std::unique_ptr<Widget1>{new Widget1{1}},
      std::unique_ptr<Widget2>{new Widget2{2}});
}

/*
warning: use std::make_unique instead [modernize-make-unique]
   Foo(std::unique_ptr<Widget1>{new Widget1{1}},
       ^~~~~~~~~~~~~~~         ~~~~~~~~~~~~~ ~~
       std::make_unique        (             )
warning: use std::make_unique instead [modernize-make-unique]
       std::unique_ptr<Widget2>{new Widget2{2}});
       ^~~~~~~~~~~~~~~         ~~~~~~~~~~~~~ ~~
       std::make_unique        (             )
*/