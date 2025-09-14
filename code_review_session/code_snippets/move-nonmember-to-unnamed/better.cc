// header file: my_class.h
class MyClass {
 public:
  int DoSomething();
};

// source file: my_class.cc
namespace {
int CalculateResult(int a, int b) {
  return a + b;
}
}  // namespace

int MyClass::DoSomething() {
  // Use CalculateResult.
  return CalculateResult(10, 20);
}

// main file: main.cc
int main() {
  MyClass my_class;
  return my_class.DoSomething();
}