#include <iostream>
#include <string>

// clang-tidy check: none
// Clang-C++ warning: none
class Book {
 public:
  Book(std::string title) : title_(std::move(title)) {}
  std::string GetTitle() const { return title_; }

 private:
  std::string title_;
};

int main() {
  const Book b{"C++ Best Practices"};
  std::cout << b.GetTitle() << '\n';
}

// C++ Best Practices
