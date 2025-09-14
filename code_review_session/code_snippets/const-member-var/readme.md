# Consider making member variable const

Making member variables `const` ensures they are initialized at construction and cannot be modified later, which can prevent bugs and improve code safety.

**Problem:**
```cpp
class Person {
 public:
  Person(const std::string& name) : name_(name) {}
  void SetId(int id) { id_ = id; }
  int GetId() const { return id_; }
  std::string GetName() const { return name_; }

 private:
  int id_;
  std::string name_;
};
```

**Fix:**
```cpp
class Person {
 public:
  Person(const std::string& name, int id) : id_(id), name_(name) {}
  int GetId() const { return id_; }
  std::string GetName() const { return name_; }

 private:
  const int id_;
  std::string name_;
};
```
