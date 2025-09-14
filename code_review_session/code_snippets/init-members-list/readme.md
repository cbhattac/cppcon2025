# Class: Initialize all members, at least by member initialization list, instead of the constructor body.

## Brief Description
In C++, it is generally more optimal and safer to initialize class members using a member initialization list in the constructor, rather than assigning values within the constructor's body. The initialization list allows members to be directly constructed with their initial values, whereas assignment in the body means members are first default-constructed and then assigned (potentially incurring an extra operation and overhead, especially for complex objects). Furthermore, some types of members *must* be initialized this way (e.g., `const` members and reference members).

## Details and Nuances

### 1. Performance and Efficiency
When you assign values in the constructor body, non-POD (Plain Old Data) members are first default-constructed (e.g., `std::string` to an empty string, `std::vector` to an empty vector), and then a copy assignment operator is called to assign the desired value. With a member initialization list, the members are directly constructed with the specified values, avoiding the redundant default construction and subsequent assignment. For simple types like `int`, the performance difference might be negligible, but for complex objects, it can lead to significant overhead.

### 2. Correctness: `const` and Reference Members
`const` member variables and reference member variables cannot be assigned values after their declaration. They *must* be initialized at the point of their creation. Since the constructor body executes *after* all members have been created (and potentially default-constructed), `const` and reference members *must* be initialized in the member initialization list. Failure to do so will result in a compilation error.

### 3. Initialization Order
The order in which members are initialized is determined by their *declaration order* in the class definition, **not** by their order in the member initialization list. While it's good practice to list them in the initialization list in the same order as their declaration for readability, understanding the actual initialization order is crucial when one member's initialization depends on another.

### 4. Delegating Constructors (C++11 and later)
C++11 introduced delegating constructors, which allow one constructor to call another constructor of the same class. When a constructor delegates, the delegated constructor performs the member initialization, and the delegating constructor's body is executed afterward. This is a special case where initialization is handled by another constructor.

## Code Snippets

### Snippet 1: Basic `int` member

Illustrates the difference for a simple integer member. While performance impact is minimal here, it sets the stage.

#### Problem:
```cpp
class MyClass {
 public:
  MyClass() {
    my_int_ = 10; // Default constructed, then assigned.
  }
 private:
  int my_int_;
};
```

## Code Snippets

### Snippet 1: `std::string` member (Performance Impact)

Demonstrates the performance implications for a non-POD type like `std::string`.

#### Problem:

```cpp
#include <string>

class MyClass {
 public:
  MyClass() {
    // 1. my_string_ is default-constructed (becomes an empty string).
    // 2. A temporary std::string "Hello" is created.
    // 3. The assignment operator (operator=) is called to copy "Hello" into my_string_.
    my_string_ = "Hello";
  }
 private:
  std::string my_string_;
};
```

#### Fix:

```cpp
#include <string>

class MyClass {
 public:
  MyClass() : my_string_("Hello") {
    // 1. my_string_ is directly constructed with "Hello", avoiding the intermediate
    //    default construction and subsequent assignment. This is more efficient.
  }
 private:
  std::string my_string_;
};
```

### Snippet 2: `const` member (Compilation Error)

Shows that `const` members *must* be initialized in the member initialization list.

#### Problem (Compilation Error):

```cpp
class MyClass {
 public:
  MyClass() {
    // ERROR: Assignment of read-only member 'kMyConstInt_'
    kMyConstInt_ = 10;
  }
 private:
  const int kMyConstInt_;
};
```

#### Fix:

```cpp
class MyClass {
 public:
  MyClass() : kMyConstInt_(10) { // Must initialize const members here.
  }
 private:
  const int kMyConstInt_;
};
```

### Snippet 3: Reference member (Compilation Error)

Shows that reference members *must* be initialized in the member initialization list.

#### Problem (Compilation Error):

```cpp
class MyClass {
 public:
  // Requires an int& parameter to initialize the reference.
  MyClass(int& value) {
    // ERROR: Assignment of read-only reference 'ref_member_'
    // References must be initialized at construction.
    ref_member_ = value;
  }
 private:
  int& ref_member_;
};
```

#### Fix:

```cpp
class MyClass {
 public:
  MyClass(int& value) : ref_member_(value) { // Must initialize reference members here.
  }
 private:
  int& ref_member_;
};
```

### Snippet 4: Initialization Order Importance

Illustrates that member initialization order is based on declaration order, not the order in the initializer list.

#### Problem (Potential Runtime Error/Unexpected Behavior):

```cpp
class MyClass {
 public:
  // Declared first, but initialized second in the list.
  int member_a_;
  // Declared second, but initialized first in the list.
  int member_b_;

  MyClass() : member_b_(member_a_ + 1), member_a_(10) {
    // When member_b_ is initialized, member_a_ has not yet been initialized
    // according to its declaration order. Its value will be indeterminate.
    // The order in the initializer list does NOT override the declaration order.
  }
};
```

#### Fix (Ensure Declaration Order Matches Dependencies/Logical Flow):

```cpp
class MyClass {
 public:
  // Declare members in the order they should be initialized.
  int member_a_;
  int member_b_;

  MyClass() : member_a_(10), member_b_(member_a_ + 1) {
    // member_a_ is initialized first, then member_b_ can safely use its value.
    // The initializer list order also matches the declaration order for clarity.
  }
};
```