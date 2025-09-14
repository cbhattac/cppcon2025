#include <iostream>

// clang-tidy check: readability-convert-member-functions-to-static
// Clang-C++ warning: none
class Logger {
 public:
  void PrintHello() { std::cout << "Hello, world!\n"; }
};

int main() {
  Logger logger;
  logger.PrintHello();
}

// Hello, world!

// -checks=readability-convert-member-functions-to-static
/*
warning: method 'PrintHello' can be made static [readability-convert-member-functions-to-static]
   void PrintHello() { std::cout << "Hello, world!\n"; }
        ^
   static 
*/