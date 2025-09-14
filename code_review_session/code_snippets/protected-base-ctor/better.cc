#include <iostream>

class Base {
 protected:
  explicit Base(int x) : x_(x) {}
  ~Base() = default;
  // Also add other special member functions if necessary.
 public:
  int GetX() const { return x_; }

 private:
  const int x_;
};

class Derived : public Base {
 public:
  explicit Derived(int x) : Base(x) {}
};

int main() {
  // Base b(5);  // Error: constructor is protected.
  const Derived d(10);
  std::cout << d.GetX() << '\n';
}

// 10
