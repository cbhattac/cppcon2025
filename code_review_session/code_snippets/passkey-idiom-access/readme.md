# Use PassKey Idiom to Control Access Instead of Friendship

The PassKey idiom is a technique to restrict access to certain class member functions without making another class a friend. This avoids exposing all private members and provides more granular control.

## Why is this important?
- Friendship exposes all private/protected members to the friend class, which can break encapsulation and make maintenance harder.
- PassKey allows you to grant access only to specific functions, not the entire class.
- It improves code clarity and maintainability.

### Problem: Using `friend` exposes too much
```cpp
class Foo {
 public:
  void SetSecret(int value) { secret_ = value; }
  int GetSecret() const { return secret_; }
 private:
  int secret_ = 0;
  friend class Bar;  // Bar can access all private members of Foo.
};

class Bar {
 public:
  void ChangeFooSecret(Foo& foo, int value) {
    foo.SetSecret(value);  // Allowed due to friendship.
  }
};
```

### Fix: Use PassKey idiom for fine-grained access
```cpp
class Foo {
 public:
  class PassKey {
   private:
    friend class Bar;
    PassKey() = default;
  };

  void SetSecret(int value, PassKey) { secret_ = value; }
  int GetSecret() const { return secret_; }
 private:
  int secret_ = 0;
};

class Bar {
 public:
  void ChangeFooSecret(Foo& foo, int value) {
    foo.SetSecret(value, Foo::PassKey{});
  }
};
```

#### Nuances
- You can have multiple PassKey types for different access levels.
- PassKey can be extended to allow access to multiple classes by making them friends.
- This idiom is especially useful in large codebases where encapsulation is critical.
- If you need to allow access to a function from multiple classes, you can make multiple classes friends of the PassKey.
