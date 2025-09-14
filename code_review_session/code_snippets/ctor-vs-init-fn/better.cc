#include <string>

class Person {
 public:
  Person(const std::string& name, int age) : name_(name), age_(age) {}

  [[nodiscard]] bool IsValid() const { return !name_.empty() && age_ > 0; }

 private:
  std::string name_;
  int age_ = 0;
};

int main() {
  // Valid object created.
  [[maybe_unused]] Person p("John Doe", 42);
}
