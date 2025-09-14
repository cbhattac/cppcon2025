#include <compare>
#include <iostream>
#include <string>

template <typename TagType, typename Type>
class MyStrongAlias {
 public:
  constexpr explicit MyStrongAlias(Type&& v) : v_(std::move(v)) {}

  constexpr Type& operator*() { return v_; }
  constexpr const Type& operator*() const { return v_; }

  constexpr auto operator<=>(const MyStrongAlias& lhs,
                             const MyStrongAlias& rhs) noexcept = default;

 private:
  Type v_;
};

using Name = MyStrongAlias<struct NameTag, std::string>;
using Email = MyStrongAlias<struct EmailTag, std::string>;

void RegisterUser(const Name& name, const Email& email) {
  std::cout << "Name: " << *name << ", Email: " << *email << '\n';
}

int main() {
  // A little more difficult to swap arguments by mistake.
  RegisterUser(Name("Alice"), Email("alice@example.com"));
}

/*
Name: Alice, Email: alice@example.com
*/