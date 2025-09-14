# Use std::move for rvalues which are not forwarding reference

When working with rvalues, using `std::move` can help avoid unnecessary copies and improve performance. This is especially important when dealing with expensive-to-copy types like `std::string`.

## Problem

### Code snippet 1
```cpp
#include <string>

void Foo(std::string str) {
  std::string copy = str;  // Inefficient copy.
  // Use `copy`.
  std::ignore = copy;
}

int main() {
  Foo("example");
}
```

### Fix
```cpp
#include <string>

void Foo(std::string str) {
  std::string copy = std::move(str);  // Efficient move.
  // Use `copy`.
  std::ignore = copy;
}

int main() {
  Foo("example");
}
```

## Nuances

### Nuance 1: Avoid moving from const objects
```cpp
#include <string>

void Foo(const std::string& str) {
  std::string copy = std::move(str);  // Error: Cannot move from const.
  // Use `copy`.
  std::ignore = copy;
}

int main() {
  const std::string example = "example";
  Foo(example);
}
```

### Fix
```cpp
#include <string>

void Foo(const std::string& str) {
  std::string copy = str;  // Correct: Copy instead of move.
  // Use `copy`.
  std::ignore = copy;
}

int main() {
  const std::string example = "example";
  Foo(example);
}
```

### Nuance 2: Use `std::move` only when ownership transfer is intended
```cpp
#include <string>

void Foo(std::string str) {
  std::string copy = std::move(str);  // Efficient move.
  // Use `copy`.
  std::ignore = copy;
}

int main() {
  Foo("example");
}
```

### Fix
Ensure that the original object is not used after the move:
```cpp
#include <string>

void Foo(std::string str) {
  std::string copy = std::move(str);  // Efficient move.
  // Use `copy`.
  std::ignore = copy;
}

int main() {
  Foo("example");
}
```
