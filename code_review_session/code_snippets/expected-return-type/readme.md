Returning Values: Use std::expected as return type when appropriate.

**Problem:**
Returning a bool for success/failure and using output parameters for both value and error message is verbose and less expressive.

```cpp
// non_optimal.cc
// Returns error message via output parameter, returns true on success.
bool ParseInt(const std::string& input, int* value, std::string* error) {
  try {
    *value = std::stoi(input);
    return true;
  } catch (const std::exception& e) {
    *error = e.what();
    return false;
  }
}
```

**Fix:**
Use `std::expected` to return either the value or the error in a single return type.

```cpp
// better.cc
expected<int, std::string> ParseInt(const std::string& input) {
  try {
    return std::stoi(input);
  } catch (const std::exception& e) {
    return unexpected<std::string>(e.what());
  }
}
```

### Returning Values: Use `std::expected` as return type when appropriate.

Returning values from functions can sometimes be ambiguous, especially when a function might fail. Historically, developers have used various techniques to indicate failure, such as returning special "error" values (e.g., `nullptr`, empty strings, negative integers), out-parameters, or throwing exceptions. While these methods have their uses, they often come with drawbacks regarding clarity, error handling, and performance (in the case of exceptions for expected errors).

`std::expected` (available since C++23) provides a robust and explicit way to represent a function that might either return a value or an error. It's a sum type that can hold either a value of type `T` or an error of type `E`. This makes the intent of the function's return clearer, encourages explicit error handling, and avoids the overhead of exceptions for routine error conditions.

#### Nuance 1: Using Special Return Values for Errors

**Problem:** Using a specific value from the return type's domain to indicate an error can lead to ambiguity and force the caller to remember and check for that specific "magic value".

```cpp
// Problematic code: Returning an empty string to indicate an error.
std::string GetUserNameById(int user_id) {
  if (user_id < 0) {
    return ""; // Invalid ID error, but also a valid empty string could be a user name
  }
  if (user_id == 123) {
    return "John Doe";
  }
  return ""; // User not found, indistinguishable from invalid ID or an actual empty name
}

// Caller must remember to check for `empty()`.
void CallSiteProblem() {
  std::string user_name = GetUserNameById(123);
  if (user_name.empty()) {
    // This could be an error or a legitimate empty user name.
    // The error type is not specific.
    std::cerr << "Error or empty name.\n";
  }
}
```

**Fix:** Use `std::expected` to clearly separate the success value from different error types.

```cpp
// Fixed code: Using std::expected with a custom error enum.
enum class UserError {
  kInvalidId,
  kUserNotFound,
  kDatabaseError,
};

std::expected<std::string, UserError> GetUserNameById(int user_id) {
  if (user_id < 0) {
    return std::unexpected(UserError::kInvalidId);
  }
  if (user_id == 123) {
    return "John Doe";
  }
  return std::unexpected(UserError::kUserNotFound);
}

// Caller explicitly checks for success or specific error types.
void CallSiteFix() {
  auto result = GetUserNameById(123);
  if (result.has_value()) {
    std::cout << "User name: " << result.value() << "\n";
  } else {
    // Error type is explicit and can be handled specifically.
    switch (result.error()) {
      case UserError::kInvalidId:
        std::cerr << "Error: Invalid user ID.\n";
        break;
      case UserError::kUserNotFound:
        std::cerr << "Error: User not found.\n";
        break;
      case UserError::kDatabaseError:
        std::cerr << "Error: Database problem.\n";
        break;
    }
  }
}
```

#### Nuance 2: Using Out-Parameters for Error Information

**Problem:** Out-parameters can obscure the function's return value and make the API less intuitive. The primary return is often ignored for error checking.

```cpp
// Problematic code: Using an out-parameter for error details.
bool TryGetUserNameById(int user_id, std::string& user_name, std::string& error_message) {
  if (user_id < 0) {
    error_message = "Invalid user ID";
    return false;
  }
  if (user_id == 123) {
    user_name = "Jane Doe";
    return true;
  }
  error_message = "User not found";
  return false;
}

void CallSiteProblemOutParam() {
  std::string name;
  std::string error;
  if (TryGetUserNameById(456, name, error)) {
    std::cout << "User name: " << name << "\n";
  } else {
    std::cerr << "Error: " << error << "\n";
  }
}
```

**Fix:** `std::expected` centralizes both the success value and the error information in the return type.

```cpp
// Fixed code: std::expected encapsulates both the result and error.
std::expected<std::string, UserError> GetUserNameByIdExpected(int user_id) {
  if (user_id < 0) {
    return std::unexpected(UserError::kInvalidId);
  }
  if (user_id == 123) {
    return "Jane Doe";
  }
  return std::unexpected(UserError::kUserNotFound);
}

void CallSiteFixExpected() {
  auto result = GetUserNameByIdExpected(456);
  if (result.has_value()) {
    std::cout << "User name: " << result.value() << "\n";
  } else {
    // Error handling is more direct.
    switch (result.error()) {
      case UserError::kInvalidId:
        std::cerr << "Error: Invalid user ID.\n";
        break;
      case UserError::kUserNotFound:
        std::cerr << "Error: User not found.\n";
        break;
      case UserError::kDatabaseError:
        std::cerr << "Error: Database problem.\n";
        break;
    }
  }
}
```

#### Nuance 3: Mixing `std::expected` with Exceptions

**Problem:** While `std::expected` is great for expected errors, it's generally not a replacement for exceptions in truly exceptional or unrecoverable situations (e.g., resource exhaustion, severe programming errors). Using `std::expected` for errors that *should* be exceptional can lead to verbose error handling.

```cpp
// Problematic code: Using std::expected for errors that might be better as exceptions.
// For example, if memory allocation truly fails and the program cannot recover.
std::expected<std::vector<int>, std::string> AllocateLargeVector(size_t size) {
  try {
    return std::vector<int>(size);
  } catch (const std::bad_alloc& e) {
    return std::unexpected(e.what()); // Converting an exception to an expected error
  }
}

void CallSiteProblemMixed() {
  auto vec_result = AllocateLargeVector(1'000'000'000); // Might throw bad_alloc
  if (!vec_result.has_value()) {
    std::cerr << "Error allocating vector: " << vec_result.error() << "\n";
    // Program might still be in a bad state if memory is truly exhausted.
  }
}
```

**Fix:** Use `std::expected` for anticipated, recoverable errors, and exceptions for truly exceptional, unrecoverable situations.

```cpp
// Fixed code: Allow std::bad_alloc to propagate as an exception for unrecoverable errors.
std::expected<std::vector<int>, UserError> GetFilteredData(const std::vector<int>& data) {
  if (data.empty()) {
    return std::unexpected(UserError::kInvalidId); // Use an existing error type for demo
  }
  // Simulate some filtering operation that might succeed or have an expected error.
  std::vector<int> filtered_data;
  // ... filtering logic ...
  if (filtered_data.empty()) {
    return std::unexpected(UserError::kUserNotFound); // No data found, an expected outcome
  }
  return filtered_data;
}

void CallSiteFixProperExceptionHandling() {
  try {
    // If AllocateLargeVector throws std::bad_alloc, it's an exceptional case.
    // std::vector<int> large_vec = AllocateLargeVector(1'000'000'000).value(); // This would throw if unexpected is used
    // A better approach for truly exceptional memory allocation failure is to let `std::vector` constructor throw.
    std::vector<int> large_vec(1'000'000); // Constructor throws bad_alloc if memory fails

    auto result = GetFilteredData(large_vec);
    if (result.has_value()) {
      std::cout << "Filtered data size: " << result.value().size() << "\n";
    } else {
      // Handle expected errors with std::expected.
      switch (result.error()) {
        case UserError::kInvalidId:
          std::cerr << "Error: Invalid data input.\n";
          break;
        case UserError::kUserNotFound: // Re-using for "no matching data" scenario
          std::cerr << "Error: No filtered data found.\n";
          break;
        case UserError::kDatabaseError: // Example, not relevant to this specific function
          std::cerr << "Error: Database error.\n";
          break;
      }
    }
  } catch (const std::bad_alloc& e) {
    std::cerr << "Fatal error: Memory allocation failed: " << e.what() << "\n";
    // This is an unrecoverable error, potentially terminate the program or log extensively.
  }
}
```