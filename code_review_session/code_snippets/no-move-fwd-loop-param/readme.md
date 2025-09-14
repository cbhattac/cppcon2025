# Don't use std::move / std::forward on function parameters for variadic functions being called into a loop

When calling a function in a loop, avoid using `std::move` or `std::forward` on the loop variable unless you are certain the variable will not be used again. Moving from a variable in a loop can leave it in a valid but unspecified state, leading to subtle bugs if the variable is accessed again.

This is especially important for template functions, where the value category may not be obvious.

## Example 1: Forwarding in a loop
```cpp
template <typename... Args>
void CallAll(const std::vector<std::function<void(Args...)>>& funcs,
             Args&&... args) {
  for (const auto& func : funcs) {
    func(std::forward<Args>(args)...);
  }
}

void Func1(std::string s) {
  printf("Func1(%s)\n", s.c_str());
}

void Func2(std::string s) {
  printf("Func2(%s)\n", s.c_str());
}

int main() {
  std::vector<std::function<void(std::string)>> funcs{Func1, Func2};
  CallAll(funcs, std::string{"hello world"});
}
```

### Fix:
```cpp
template <typename... Args>
void CallAll(const std::vector<std::function<void(const Args&...)>>& funcs,
             Args&&... args) {
  for (const auto& func : funcs) {
    func(args...);
  }
}

void Func1(const std::string& s) {
  printf("Func1(%s)\n", s.c_str());
}

void Func2(const std::string& s) {
  printf("Func2(%s)\n", s.c_str());
}

int main() {
  std::vector<std::function<void(const std::string&)>> funcs{Func1, Func2};
  CallAll(funcs, std::string{"hello world"});
}
```

