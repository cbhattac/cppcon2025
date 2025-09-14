### Use `std::optional` as return type

Functions that might or might not produce a value, and traditionally used a `bool` return type with an output parameter (e.g., `bool GetValue(InputType input, ValueType* output)`), can often be made more robust and readable by returning `std::optional<ValueType>`.

#### Problems with `bool` return + output parameter:

1.  **Readability:** It's not immediately clear from the function signature that `output` is an optional return value rather than an input or a required output.
2.  **Safety:** If the caller forgets to check the boolean return value, they might use uninitialized data from `*output`, leading to undefined behavior or crashes.
3.  **Error-prone:** It's easy to forget to initialize the `output` parameter before passing it to the function.
4.  **No `const` for output parameter:** The output parameter cannot be `const`, which might mislead about its mutability.

#### Benefits of `std::optional` return type:

1.  **Clarity:** The function signature `std::optional<T> Func(...)` clearly indicates that the function may or may not return a value of type `T`.
2.  **Type Safety:** `std::optional` inherently forces the caller to check for the presence of a value before accessing it (e.g., via `has_value()` or `*` operator), reducing the risk of using uninitialized data.
3.  **Expressiveness:** It directly models the concept of "an optional value," which is more semantically correct than using a boolean flag and an out-parameter.
4.  **Chaining Operations:** `std::optional` can be easily used with monadic operations (e.g., `and_then`, `transform` in C++23) for more concise and functional-style code.

#### Code Snippets:

**Snippet 1: Basic conversion from `bool` out-parameter to `std::optional`**

This example demonstrates a simple function that tries to find an element in a vector and returns its value.

```cpp
// Non-optimal: Using bool and out-parameter
bool FindValue(const std::vector<int>& vec, int target, int* out_value) {
    for (int val : vec) {
        if (val == target) {
            *out_value = val;
            return true;
        }
    }
    return false;
}
````

```cpp
// Better: Using std::optional
std::optional<int> FindValue(const std::vector<int>& vec, int target) {
    for (int val : vec) {
        if (val == target) {
            return val;
        }
    }
    return std::nullopt;
}
```

**Snippet 2: Handling default values or alternative paths**

Often, if a value is not found, a default value or alternative logic is required.

```cpp
// Non-optimal: Requires separate handling of the boolean result
int value_to_use;
if (FindValue(my_vec, 10, &value_to_use)) {
    // Use value_to_use
    // ...
} else {
    value_to_use = -1; // Default value
    // ...
}
```

```cpp
// Better: Using value_or for default values
int value_to_use = FindValue(my_vec, 10).value_or(-1);

// Better: Using if (optional_var) for alternative paths
if (auto val_opt = FindValue(my_vec, 10)) {
    // Use val_opt.value() or *val_opt
    // ...
} else {
    // Handle case where value is not present
    // ...
}
```

**Snippet 3: Avoiding uninitialized variables and promoting `const` correctness**

The `std::optional` approach ensures that `val` is only accessible if a value is present, preventing accidental use of an uninitialized variable.

```cpp
// Non-optimal: `result` might be used uninitialized if `GetStringLength` returns false
size_t result;
if (GetStringLength("test", &result)) {
    // result is initialized
    std::ignore = result;
} else {
    // result is NOT initialized here, but could still be accessed later
}
```

```cpp
// Better: `length_opt` is clearly optional; its value is accessed safely
std::optional<size_t> length_opt = GetStringLength("test");
if (length_opt.has_value()) {
    const size_t length = length_opt.value(); // `length` is const and initialized
    std::ignore = length;
}
// If length_opt does not have a value, there is no corresponding `length` variable to misuse.
```
