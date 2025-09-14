#include <iostream>
#include <regex>

// The calls to string functions will all "trap" when
// _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE is used. If
// _LIBCPP_HARDENING_MODE is not used, then with clang `-std=c++20
// -stdlib=libc++ -O3` this code will work fine and print:
/*
Length: 0
Position: 0
str: 
match[0]: 
prefix: 
suffix: 
*/

int main() {
  std::cmatch match;
  // All these calls will flag since match is not yet ready.
  std::cout << "Length: " << match.length() << '\n';
  std::cout << "Position: " << match.position() << '\n';
  std::cout << "str: " << match.str() << '\n';
  std::cout << "match[0]: " << match[0] << '\n';
  std::cout << "prefix: " << match.prefix() << '\n';
  std::cout << "suffix: " << match.suffix() << '\n';
}