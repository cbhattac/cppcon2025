#include <stdio.h>

#include <memory>

// clang-tidy check: bugprone-unused-return-value,modernize-use-nodiscard
// Clang-C++ warning: none
class ResourceWrapper {
 public:
  bool IsValid() const { return is_valid_; }

 private:
  bool is_valid_ = true;
};

class ErrorInfo {
  // Class stuff.
};

ErrorInfo GetError() {
  // Fill in the error with all info.
  return ErrorInfo{};
}

struct A {
  A() { puts("A()"); }
  ~A() { puts("~A()"); }
  A(const A&) { puts("A(const A&)"); }
  A(A&&) noexcept { puts("A(A&&)"); }
  A& operator=(const A&) {
    puts("A& operator=(const A&)");
    return *this;
  }
  A& operator=(A&&) noexcept {
    puts("A& operator=(A&&)");
    return *this;
  }
};

std::unique_ptr<A> CreateA() {
  return std::make_unique<A>();
}

void ProcessResource(const ResourceWrapper& resource) {
  resource.IsValid();

  // This might be incorrect if the resource is not valid.
  puts("Processing resource...\n");
}

int main() {
  ResourceWrapper resource;
  ProcessResource(resource);
  GetError();
  CreateA();
  puts("==== After CreateA() ====");
}

/*
Processing resource...
A()
~A()
==== After CreateA() ====
*/

/* When [modernize-use-nodiscard] is used it shows the following:
warning: function 'IsValid' should be marked [[nodiscard]]
[modernize-use-nodiscard] bool IsValid() const { return is_valid_; }
   ^
   [[nodiscard]]
*/
