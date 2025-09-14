#include <functional>
#include <iostream>
#include <memory>
#include <vector>

class Base {
 public:
  virtual ~Base() = default;
  int GetId() const { return id_; }
  virtual void Foo() = 0;

 protected:
  Base(int id) : id_(id) {}
  const int id_;
};

class Derived1 final : public Base {
 public:
  Derived1(int i) : Base(i) {}
  void Foo() final { std::cout << "Derived1::Foo()\n"; }
};

class Derived2 final : public Base {
 public:
  Derived2(int i) : Base(i) {}
  void Foo() final { std::cout << "Derived2::Foo()\n"; }
};

class ObjectManager {
 public:
  std::weak_ptr<Base> CreateDerived1() { return Create<Derived1>(); }
  std::weak_ptr<Base> CreateDerived2() { return Create<Derived2>(); }
  void RemoveFirst() { vec_.erase(vec_.begin()); }

 private:
  template <typename T>
  std::weak_ptr<Base> Create() {
    auto p = std::make_shared<T>(++counter_);
    vec_.push_back(p);
    return p;
  }

  int counter_ = 0;
  std::vector<std::shared_ptr<Base>> vec_;
};

class SomeManager {
 public:
  void AddHandler(std::weak_ptr<Base> p) {
    fns_.push_back([wp = p] {
      if (auto p = wp.lock()) {
        p->Foo();
      }
    });
  }

  void RunFunctions() {
    for (auto&& f : fns_) {
      f();
    }
  }

 private:
  std::vector<std::function<void()>> fns_;
};

int main() {
  ObjectManager o;
  SomeManager s;
  s.AddHandler(o.CreateDerived1());
  s.AddHandler(o.CreateDerived2());
  o.RemoveFirst();
  s.RunFunctions();
}

// Derived2::Foo()