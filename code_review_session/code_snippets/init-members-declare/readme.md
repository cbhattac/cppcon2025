### Class: Initialize all members, preferably when they are declared

Uninitialized members can lead to undefined behavior. Prefer initializing members at the point of declaration.

```cpp
class Person {
 public:
  Person(const std::string& name) {
    name_ = name;
    age_ = 0;
  }

 private:
  std::string name_;
  int age_;
};
```

**Fix:**

```cpp
class Person {
 public:
  Person(const std::string& name) : name_(name) {}

 private:
  std::string name_;
  int age_ = 0;
};
```

### Clang-tidy check: `cppcoreguidelines-pro-type-member-init`:

```cpp
struct Size {
  Size() {
    width = 0;
    // height = 0;
  }

  int width;
  int height;
};
```
When built with `cppcoreguidelines-pro-type-member-init` we get the following warning:
```
warning: constructor does not initialize these fields: height [cppcoreguidelines-pro-type-member-init]
   Size() {
   ^
     width = 0;
     // height = 0;
   }
 
   int width;
   int height;
```

