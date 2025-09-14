#include <string>

// clang-tidy check: none
// Clang-C++ warning: none
class Person {
 public:
  Person() = default;

  void Init(const std::string& name, int age) {
    name_ = name;
    age_ = age;
  }

  [[nodiscard]] bool IsValid() const { return !name_.empty() && age_ > 0; }

 private:
  std::string name_;
  int age_ = 0;
};

int main() {
  Person p; // Creates invalid object.
  p.Init("John Doe", 42);
}
