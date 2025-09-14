#include <iostream>
#include <string>

struct Name {
  explicit Name(std::string s) : value(std::move(s)) {}
  std::string value;
};

struct Email {
  explicit Email(std::string s) : value(std::move(s)) {}
  std::string value;
};

void RegisterUser(const Name& name, const Email& email) {
  std::cout << "Name: " << name.value << ", Email: " << email.value << '\n';
}

int main() {
  // A little more difficult to swap arguments by mistake.
  RegisterUser(Name("Alice"), Email("alice@example.com"));
}

/*
Name: Alice, Email: alice@example.com
*/