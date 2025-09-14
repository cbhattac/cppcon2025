#include <iostream>
#include <string>

void RegisterUser(const std::string& name, const std::string& email) {
  std::cout << "Name: " << name << ", Email: " << email << '\n';
}

int main() {
  // Easy to swap arguments by mistake.
  RegisterUser("alice@example.com", "Alice");
}

/*
Name: alice@example.com, Email: Alice
*/