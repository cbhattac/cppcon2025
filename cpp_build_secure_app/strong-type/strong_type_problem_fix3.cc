#include <compare>
#include <iostream>
#include <string>

struct NameEmail {
  std::string name;
  std::string email;
};

void RegisterUser(const NameEmail& v) {
  std::cout << "Name: " << v.name << ", Email: " << v.email << '\n';
}

int main() {
  // A little more difficult to swap arguments by mistake.
  RegisterUser({.name = "Alice", .email = "alice@example.com"});
}

/*
Name: Alice, Email: alice@example.com
*/