### Class: Ensure a class is initialized in its constructor, instead of deferring to constructor + init function

Deferring initialization to a separate function can lead to partially initialized objects and bugs.

```cpp
class Person {
 public:
  Person() = default;
  void Init(const std::string& name, int age) {
    name_ = name;
    age_ = age;
  }

 private:
  std::string name_;
  int age_;
};

int main() {
  Person p;
  p.Init("AI", 42);
}
```

**Fix:**

```cpp
class Person {
 public:
  Person(const std::string& name, int age) : name_(name), age_(age) {}

 private:
  std::string name_;
  int age_;
};

int main() {
  Person p("AI", 42);
}
```
