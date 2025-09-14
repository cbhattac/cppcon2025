#include <iostream>

class Logger {
 public:
  static void PrintHello() { std::cout << "Hello, world!\n"; }
};

int main() {
  Logger::PrintHello();
}
