## Class: Don't make member variables const if you need to use move construction.

When designing a class in C++, it's generally good practice to allow for move semantics (move construction and move assignment) if the class manages resources or holds large objects. Move semantics can significantly improve performance by transferring ownership of resources rather than performing deep copies, especially when objects are passed by value, returned from functions, or stored in containers like `std::vector` that might reallocate their elements.

A common pitfall that prevents the compiler from implicitly generating or effectively using move constructors/assignment operators is declaring member variables as `const`. If a class has a `const` member variable, the compiler cannot generate a move constructor that "moves" the value of that `const` member, because a `const` member, once initialized, cannot be modified (or "moved from"). This effectively means that if you try to move an object of such a class, a copy operation will be performed for the `const` member (if it's copyable), or the move operation will be ill-formed if the `const` member is not copyable. This can lead to unexpected performance degradation.

### Nuance 1: `const` member explicitly prevents move constructor.

If a class has a `const` member, the implicitly declared move constructor is defined as deleted (C++11/14) or is trivialized (C++17 onwards, if the `const` member is copyable and the implicit move constructor would otherwise be trivial). In either case, it often means that operations that would normally trigger a move will instead trigger a copy, leading to performance overhead.

```cpp
// Problem: `const` member prevents efficient move.
#include <iostream>
#include <string>

class NonOptimalClass {
 public:
  // `name_` is const.
  explicit NonOptimalClass(const std::string& name) : name_(name) {
    std::cout << "NonOptimalClass(const std::string&) constructor for " << name_
              << std::endl;
  }

  NonOptimalClass(const NonOptimalClass& other) : name_(other.name_) {
    std::cout << "NonOptimalClass(const NonOptimalClass&) copy constructor for "
              << name_ << std::endl;
  }

  // The implicitly declared move constructor would be deleted or trivialized,
  // causing a copy to occur when trying to move.
  // If you explicitly define it, it must initialize the const member,
  // which would still be a copy.
  NonOptimalClass(NonOptimalClass&& other) noexcept
      : name_(other.name_) {  // Still a copy of other.name_
    std::cout << "NonOptimalClass(NonOptimalClass&&) move constructor "
                 "(actually copy) for "
              << name_ << std::endl;
  }

 private:
  const std::string name_;
};

int main() {
  NonOptimalClass obj("TestObject");
  std::cout << "Moving obj:" << std::endl;
  NonOptimalClass moved_obj =
      std::move(obj);  // Will call copy constructor of NonOptimalClass
}
```

```cpp
// Fix: Make the member non-const to enable move semantics.
#include <iostream>
#include <string>
#include <utility>  // For std::move

void Ignore(auto&&) {}

class BetterClass {
 public:
  // `name_` is non-const.
  explicit BetterClass(std::string name) : name_(std::move(name)) {
    std::cout << "BetterClass(std::string) constructor for " << name_
              << std::endl;
  }

  BetterClass(const BetterClass& other) : name_(other.name_) {
    std::cout << "BetterClass(const BetterClass&) copy constructor for "
              << name_ << std::endl;
  }

  BetterClass(BetterClass&& other) noexcept : name_(std::move(other.name_)) {
    Ignore(other.name_);  // To prevent unused variable warning.
    std::cout << "BetterClass(BetterClass&&) move constructor for " << name_
              << std::endl;
  }

 private:
  std::string name_;
};

int main() {
  BetterClass obj("TestObject");
  std::cout << "Moving obj:" << std::endl;
  BetterClass moved_obj =
      std::move(obj);  // Will call move constructor of BetterClass
}
```

### Nuance 2: Impact on `std::vector` reallocations.

When a `std::vector` needs to grow beyond its current capacity, it typically allocates new memory, moves or copies its existing elements to the new location, and then deallocates the old memory. If the elements stored in the `vector` have `const` members, they will be copied instead of moved during reallocation, leading to unnecessary overhead, especially for large objects.

```cpp
// Problem: `const` member forces copies during vector reallocation.
#include <iostream>
#include <string>
#include <utility>  // For std::move
#include <vector>

class ItemWithConst {
 public:
  explicit ItemWithConst(const std::string& id) : id_(id) {
    std::cout << "ItemWithConst(const std::string&) constructor for " << id_
              << std::endl;
  }

  ItemWithConst(const ItemWithConst& other) : id_(other.id_) {
    std::cout << "ItemWithConst(const ItemWithConst&) copy constructor for "
              << id_ << std::endl;
  }

  // Move constructor is effectively disabled or trivialized due to 'const id_'.
  // If we try to explicitly define it to move, it will still copy id_.
  ItemWithConst(ItemWithConst&& other) noexcept : id_(other.id_) {
    std::cout << "ItemWithConst(ItemWithConst&&) (acting as copy) for " << id_
              << std::endl;
  }

  const std::string& id() const { return id_; }

 private:
  const std::string id_;
};

int main() {
  std::vector<ItemWithConst> items;
  items.reserve(1);  // Small initial capacity to trigger reallocation

  std::cout << "Adding item 1:" << std::endl;
  items.push_back(ItemWithConst("Alpha"));  // Copy
  std::cout << "\nAdding item 2 (triggering reallocation):" << std::endl;
  items.push_back(ItemWithConst(
      "Beta"));  // Original "Alpha" is copied, then "Beta" is copied
  std::cout << "\nAdding item 3 (triggering reallocation):" << std::endl;
  items.push_back(ItemWithConst(
      "Gamma"));  // "Alpha" and "Beta" are copied, then "Gamma" is copied

  std::cout << "\nFinal items:" << std::endl;
  for (const auto& item : items) {
    std::cout << "  " << item.id() << std::endl;
  }
}
```

```cpp
// Fix: Non-const member enables moves during vector reallocation.
#include <iostream>
#include <string>
#include <utility>  // For std::move
#include <vector>

void Ignore(auto&&) {}

class ItemWithoutConst {
 public:
  explicit ItemWithoutConst(std::string id) : id_(std::move(id)) {
    std::cout << "ItemWithoutConst(std::string) constructor for " << id_
              << std::endl;
  }

  ItemWithoutConst(const ItemWithoutConst& other) : id_(other.id_) {
    std::cout
        << "ItemWithoutConst(const ItemWithoutConst&) copy constructor for "
        << id_ << std::endl;
  }

  ItemWithoutConst(ItemWithoutConst&& other) noexcept
      : id_(std::move(other.id_)) {
    Ignore(other.id_);  // To prevent unused variable warning.
    std::cout << "ItemWithoutConst(ItemWithoutConst&&) move constructor for "
              << id_ << std::endl;
  }

  ItemWithoutConst& operator=(ItemWithoutConst&& other) noexcept {
    if (this != &other) {
      id_ = std::move(other.id_);
      Ignore(other.id_);  // To prevent unused variable warning.
      std::cout << "ItemWithoutConst& operator=(ItemWithoutConst&&) move "
                   "assignment for "
                << id_ << std::endl;
    }
    return *this;
  }

  const std::string& id() const { return id_; }

 private:
  std::string id_;
};

int main() {
  std::vector<ItemWithoutConst> items;
  items.reserve(1);  // Small initial capacity to trigger reallocation

  std::cout << "Adding item 1:" << std::endl;
  items.push_back(ItemWithoutConst("Alpha"));  // Move
  std::cout << "\nAdding item 2 (triggering reallocation):" << std::endl;
  items.push_back(ItemWithoutConst(
      "Beta"));  // Original "Alpha" is moved, then "Beta" is moved
  std::cout << "\nAdding item 3 (triggering reallocation):" << std::endl;
  items.push_back(ItemWithoutConst(
      "Gamma"));  // "Alpha" and "Beta" are moved, then "Gamma" is moved

  std::cout << "\nFinal items:" << std::endl;
  for (const auto& item : items) {
    std::cout << "  " << item.id() << std::endl;
  }
}
```

### Nuance 3: When a `const` member is truly necessary.

There are rare cases where a `const` member might be desired, for example, if the object's identity or a crucial part of its state is truly immutable and part of its construction, and copy/move semantics are either not needed or specifically intended to be copies. However, this is an advanced design choice and should be made with a clear understanding of its implications on performance and usability. For most general-purpose classes, especially those intended for use in STL containers, non-`const` members are preferred to enable efficient move operations.

A common alternative to `const` members for immutable data is to have a private, non-`const` member initialized in the constructor and then provide only `const` accessors (getter methods). This allows the internal state to be moved while still presenting an immutable interface to users of the class.

```cpp
// Correct way to achieve immutability while allowing moves:
// Non-const private member with const public accessor.
#include <iostream>
#include <string>
#include <utility>  // For std::move

void Ignore(auto&&) {}

class ImmutableViaAccessor {
 public:
  explicit ImmutableViaAccessor(std::string data) : data_(std::move(data)) {
    std::cout << "ImmutableViaAccessor(std::string) constructor for " << data_
              << std::endl;
  }

  // Copy constructor
  ImmutableViaAccessor(const ImmutableViaAccessor& other) : data_(other.data_) {
    std::cout << "ImmutableViaAccessor(const ImmutableViaAccessor&) copy "
                 "constructor for "
              << data_ << std::endl;
  }

  // Move constructor
  ImmutableViaAccessor(ImmutableViaAccessor&& other) noexcept
      : data_(std::move(other.data_)) {
    Ignore(other.data_);  // To prevent unused variable warning.
    std::cout
        << "ImmutableViaAccessor(ImmutableViaAccessor&&) move constructor for "
        << data_ << std::endl;
  }

  // Public accessor returns const reference, making the data appear immutable
  // from outside.
  const std::string& data() const { return data_; }

 private:
  std::string data_;  // Private, non-const member.
};

int main() {
  ImmutableViaAccessor obj("PermanentData");
  std::cout << "Data via accessor: " << obj.data() << std::endl;

  std::cout << "Moving obj:" << std::endl;
  ImmutableViaAccessor moved_obj =
      std::move(obj);  // Will call move constructor
  std::cout << "Data via accessor of moved_obj: " << moved_obj.data()
            << std::endl;
  // obj.data() is now in a valid but unspecified state (likely empty string)
}
```

By following these guidelines, you can ensure your C++ classes are performant and correctly interact with modern C++ features like move semantics.
