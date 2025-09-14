#include <functional>
#include <iostream>
#include <map>
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
  Base* CreateDerived1() { return Create<Derived1>(); }
  Base* CreateDerived2() { return Create<Derived2>(); }
  Base* GetObject(int i) const {
    auto it = m_.find(i);
    if (it == m_.end()) {
      return nullptr;
    }
    return it->second.get();
  }
  void RemoveFirst() { m_.erase(m_.begin()); }

 private:
  template <typename T>
  Base* Create() {
    auto p = std::make_unique<T>(++counter_);
    auto* ptr = p.get();
    m_.emplace(ptr->GetId(), std::move(p));
    return ptr;
  }

  int counter_ = 0;
  std::map<int, std::unique_ptr<Base>> m_;
};

class SomeManager {
 public:
  SomeManager(ObjectManager* o) : o_(o) {}
  void AddHandler(Base* p) {
    fns_.push_back([o = o_, id = p->GetId()] {
      auto* p = o->GetObject(id);
      if (p) {
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
  ObjectManager* o_;
  std::vector<std::function<void()>> fns_;
};

int main() {
  ObjectManager o;
  SomeManager s(&o);
  s.AddHandler(o.CreateDerived1());
  s.AddHandler(o.CreateDerived2());
  o.RemoveFirst();
  s.RunFunctions();
}

// Derived1::Foo()