# Do not return const value from functions

Returning a const value from a function is unnecessary and can lead to confusion. The const qualifier does not affect the returned value and may prevent optimizations.

**Problem:**
```cpp
const std::string MakeString() {
  return "hello world";
}
```

**Fix:**
```cpp
std::string MakeString() {
  return "hello world";
}
```
### Returning Values from Functions: Don't return const value

Returning a `const` value from a function, especially for user-defined types, can prevent move semantics and introduce unnecessary copying. It can also lead to compilation errors if the caller tries to modify the returned `const` object. For primitive types, returning `const` has no effect as they are typically copied anyway.

#### Nuance 1: Preventing Move Semantics for User-Defined Types

When a function returns a `const` object of a user-defined type, it prevents the compiler from using move constructors/assignment operators, forcing a copy instead. This can lead to performance degradation for large objects.

```cpp
// Problem: Returning const MyClass prevents move semantics
class MyClass {
 public:
  MyClass() { /* std::cout << "Default Constructor\n"; */ }
  MyClass(const MyClass&) { /* std::cout << "Copy Constructor\n"; */ }
  MyClass(MyClass&&) noexcept { /* std::cout << "Move Constructor\n"; */ }
  MyClass& operator=(const MyClass&) { /* std::cout << "Copy Assignment\n"; */ return *this; }
  MyClass& operator=(MyClass&&) noexcept { /* std::cout << "Move Assignment\n"; */ return *this; }
};

const MyClass CreateConstObject() {
  return MyClass();
}

// TODO: UPDATE: INCORRECT CODE.
void ConsumeObject() {
  MyClass obj = CreateConstObject(); // Will call copy constructor even if move is available
}
````

```cpp
// Fix: Returning MyClass allows move semantics (Return Value Optimization - RVO or move constructor)
class MyClass {
 public:
  MyClass() { /* std::cout << "Default Constructor\n"; */ }
  MyClass(const MyClass&) { /* std::cout << "Copy Constructor\n"; */ }
  MyClass(MyClass&&) noexcept { /* std::cout << "Move Constructor\n"; */ }
  MyClass& operator=(const MyClass&) { /* std::cout << "Copy Assignment\n"; */ return *this; }
  MyClass& operator=(MyClass&&) noexcept { /* std::cout << "Move Assignment\n"; */ return *this; }
};

MyClass CreateObject() {
  return MyClass();
}

void ConsumeObject() {
  MyClass obj = CreateObject(); // Will likely use RVO, or move constructor if RVO is not applicable
}
```

#### Nuance 2: No Benefit for Primitive Types

For built-in primitive types (like `int`, `double`, pointers), returning `const` generally offers no practical advantage and can be misleading. These types are typically copied by value, and adding `const` to the return type doesn't change this fundamental behavior or improve performance.

```cpp
// Problem: Returning const int is redundant and has no effect
const int GetConstInt() {
  return 42;
}

void UseInt() {
  int val = GetConstInt(); // 'val' will be a copy, const-ness is lost
}
```

```cpp
// Fix: Returning int is standard and sufficient
int GetInt() {
  return 42;
}

void UseInt() {
  int val = GetInt();
}
```

```
```