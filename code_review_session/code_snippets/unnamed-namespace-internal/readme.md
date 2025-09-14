# Use unnamed namespaces instead of static for internal linkage

The `static` keyword at global or namespace scope in C++ is a C-style remnant used to limit the visibility of global variables and functions to the current translation unit (i.e., the current `.cc` file). While it achieves this goal, **unnamed namespaces** offer a more idiomatic and flexible C++ approach for the same purpose.

### Why unnamed namespaces are better:

  * **Clarity and Intent:** Unnamed namespaces clearly express the intent that the enclosed entities are internal to the translation unit and are not meant to be accessed from other files. The `static` keyword has multiple meanings in C++ (e.g., static class members, static local variables), which can lead to confusion.
  * **Avoids Name Collisions (Indirectly):** While `static` also helps prevent name collisions by limiting scope, unnamed namespaces are a more explicit way to create unique, internal names that won't clash with symbols in other translation units or the global namespace.
  * **Consistency with Modern C++:** Unnamed namespaces are a more modern C++ feature, aligning with the language's emphasis on namespaces for organizing code.
  * **Translation unit-only classes:** Unnamed namespaces can be used to create "transition-unit-scoped" classes which have no equivalent using `static` keyword.
  * **Easy grouping:** Unnamed namespaces allow easy grouping of "transition-unit-scoped" functions and variables. With `static` we need to repeat the keyword.

### Problems with `static` at global scope:

  * **Ambiguity:** As mentioned, `static` has different meanings depending on its context, which can make code harder to read and understand.
  * **Less Flexible:** `static` applies directly to individual declarations. Unnamed namespaces group related declarations.

### Code Snippets:

#### Nuance 1: Global Variables

This illustrates how to restrict the scope of a global variable to a single translation unit.

```cpp
// Problem: Using 'static' for internal linkage of a global variable.
// non_optimal.cc
static int s_internal_data = 10;

void UpdateInternalData(int new_value) {
  s_internal_data = new_value;
}
```

```cpp
// Fix: Using an unnamed namespace for internal linkage.
// better.cc
namespace {
int s_internal_data = 10;
} // namespace

void UpdateInternalData(int new_value) {
  s_internal_data = new_value;
}
```

-----

#### Nuance 2: Global Functions

This demonstrates how to restrict the scope of a global function to a single translation unit.

```cpp
// Problem: Using 'static' for internal linkage of a global function.
// non_optimal.cc
static void InternalHelperFunction() {
  // ...
}

void PublicFunction() {
  InternalHelperFunction();
}
```

```cpp
// Fix: Using an unnamed namespace for internal linkage.
// better.cc
namespace {
void InternalHelperFunction() {
  // ...
}
} // namespace

void PublicFunction() {
  InternalHelperFunction();
}
```

-----

#### Nuance 3: Grouping Related Entities

Unnamed namespaces allow for grouping multiple related variables and functions that are only intended for internal use.

```cpp
// Problem: 'static' keyword applied individually to multiple related entities.
// non_optimal.cc
static int s_config_value_a = 5;
static int s_config_value_b = 10;

static void InitConfig() {
  // ...
}
```

```cpp
// Fix: Grouping related entities within an unnamed namespace.
// better.cc
namespace {
int s_config_value_a = 5;
int s_config_value_b = 10;

void InitConfig() {
  // ...
}
} // namespace
```