#include <functional>
#include <iostream>
#include <map>
#include <memory>

struct MyClass {
  MyClass() { std::cout << "MyClass()\n"; }
  ~MyClass() { std::cout << "~MyClass()\n"; }

  void Foo(std::function<void()> fn) {
    std::cout << "MyClass::Foo before fn\n";
    fn();
    std::cout << "MyClass::Foo after fn\n";
  }
};

struct ObjectManager {
 public:
  int AddObject() {
    const auto id = ++counter_;
    m_.emplace(id, std::make_shared<MyClass>());
    return id;
  }
  void Remove(int id) { m_.erase(id); }
  void CallFooOnObject(int id, std::function<void()> fn) {
    auto it = m_.find(id);
    if (it != m_.end()) {
      it->second->Foo(fn);
    }
  }

 private:
  int counter_ = 0;
  std::map<int, std::shared_ptr<MyClass>> m_;
};

int main() {
  ObjectManager o;
  const auto id = o.AddObject();
  o.CallFooOnObject(id, [id, po = &o]() { po->Remove(id); });
}

/*
MyClass()
MyClass::Foo before fn
~MyClass()
MyClass::Foo after fn
*/