#include <stdio.h>

#include <memory>

class ResourceWrapper {
 public:
  [[nodiscard]] bool IsValid() const { return is_valid_; }

 private:
  bool is_valid_ = true;
};

class [[nodiscard]] ErrorInfo {
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

[[nodiscard]] std::unique_ptr<A> CreateA() {
  return std::make_unique<A>();
}

void ProcessResource(const ResourceWrapper& resource) {
  if (!resource.IsValid()) {
    return;
  }
  // This might be incorrect if the resource is not valid.
  puts("Processing resource...");
}

int main() {
  ResourceWrapper resource;
  ProcessResource(resource);
  [[maybe_unused]] const auto error = GetError();
  [[maybe_unused]] const auto a = CreateA();
  puts("==== After CreateA() ====");
}

/*
Processing resource...
A()
==== After CreateA() ====
~A()
*/
