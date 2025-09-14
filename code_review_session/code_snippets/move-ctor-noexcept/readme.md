### Ensure the Move Constructor is `noexcept`

When implementing a custom class that manages a resource, it is a best practice to mark the move constructor as `noexcept` if it does not throw exceptions. This is a subtle but critical optimization for standard library containers.

Standard containers like `std::vector`, `std::list`, and `std::string` rely on an object's `noexcept` status to make a fundamental decision about how to handle resizing and reallocation. If a container needs to move an existing element to a new memory location (e.g., when a `std::vector` runs out of capacity), it will check if the element's move constructor is `noexcept`.

  - If the move constructor **is** `noexcept`, the container can safely use it. This is because a move operation that doesn't throw is the most efficient way to relocate the object.
  - If the move constructor is **not** `noexcept`, the container must assume it could throw an exception. To maintain strong exception safety (guaranteeing the container remains in a valid state), the container will fall back to the more expensive **copy constructor** instead.

By correctly marking your move constructor as `noexcept`, you are enabling these performance optimizations and ensuring your class behaves correctly within the standard library.

#### Non-Optimal Code

This code defines a class `A` with a move constructor that is not marked `noexcept`.

```cpp
struct A final {
  A(int a) : a_(a) { printf("A(%d)\n", a_); }
  ~A() { puts("~A()"); }
  A(const A& rhs) : a_(rhs.a_) { printf("A(const A&): %d\n", a_); }
  A(A&& rhs) : a_(rhs.a_) { printf("A(A&&): %d\n", a_); }
  A& operator=(const A& rhs) {
    a_ = rhs.a_;
    printf("A& operator=(const A&): %d\n", a_);
    return *this;
  }
  A& operator=(A&& rhs) noexcept {
    a_ = rhs.a_;
    printf("A& operator=(A&&): %d\n", a_);
    return *this;
  }
  int a_ = 0;
};
```

The following program uses this class inside a `std::vector`. When the vector resizes, it is forced to use the less-efficient copy constructor to move the first element.

```cpp
#include <stdio.h>

#include <vector>

int main() {
  std::vector<A> vec;
  // Don't consider `reserve` for the moment.
  for (int i = 0; i < 4; ++i) {
    vec.emplace_back(i);
  }
}
```

Expected output:

```
A(0)
A(1)
A(const A&): 0
~A()
A(2)
A(const A&): 1
A(const A&): 0
~A()
~A()
A(3)
~A()
~A()
~A()
~A()
```

#### Better Code

The fix is to simply add the `noexcept` specifier to the move constructor. Since move constructors typically just swap pointers or resources, they are generally exception-safe.

```cpp
struct A final {
  A(int a) : a_(a) { printf("A(%d)\n", a_); }
  ~A() { puts("~A()"); }
  A(const A& rhs) : a_(rhs.a_) { printf("A(const A&): %d\n", a_); }
  A(A&& rhs) noexcept : a_(rhs.a_) { printf("A(A&&): %d\n", a_); }
  A& operator=(const A& rhs) {
    a_ = rhs.a_;
    printf("A& operator=(const A&): %d\n", a_);
    return *this;
  }
  A& operator=(A&& rhs) noexcept {
    a_ = rhs.a_;
    printf("A& operator=(A&&): %d\n", a_);
    return *this;
  }
  int a_ = 0;
};
```

The corrected program now leverages this `noexcept` guarantee. When the `std::vector` resizes, it is able to use the more efficient move constructor.

```cpp
#include <stdio.h>

#include <vector>

int main() {
  std::vector<A> vec;
  // Don't consider `reserve` for the moment.
  for (int i = 0; i < 4; ++i) {
    vec.emplace_back(i);
  }
}
```

Expected output:

```
A(0)
A(1)
A(A&&): 0
~A()
A(2)
A(A&&): 0
A(A&&): 1
~A()
~A()
A(3)
~A()
~A()
~A()
~A()
```