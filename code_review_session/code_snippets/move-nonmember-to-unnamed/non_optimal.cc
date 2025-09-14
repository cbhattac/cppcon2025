// header file: my_class.h
// clang-tidy check: none
// Clang-C++ warning: none

class MyClass {
 public:
  int DoSomething();

 private:
  static int CalculateResult(int a, int b);
};

// source file: my_class.cc
int MyClass::DoSomething() {
  // Use CalculateResult.
  return CalculateResult(10, 20);
}

int MyClass::CalculateResult(int a, int b) {
  return a + b;
}

// main file: main.cc
int main() {
  MyClass my_class;
  return my_class.DoSomething();
}
