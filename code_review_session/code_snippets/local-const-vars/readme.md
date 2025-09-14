# Make local variables const to better comprehend code

Making local variables `const` improves code readability, helps prevent accidental modification.

## Scenario:

```cpp
void ProcessData() {
  std::string file_path{"folder/filepath.text"};
  std::vector<int> int_data = GetIntData(file_path);
  std::string str_data = GetStringData(file_path);

  // Use `file_path`, `int_data`, `str_data` without modifying.
  std::cout << "File path: " << file_path << '\n';
  std::cout << "Integer data: ";
  for (int num : int_data) {
    std::cout << num << " ";
  }
  std::cout << "Sum: " << GetSomeValue(int_data) << '\n';
  std::cout << "String data: " << str_data << '\n';
  std::cout << GetInterestingNumber(str_data) << '\n';
}
```

**Fix:**
Allows better comprehension:
```cpp
void ProcessData() {
  const std::string file_path{"folder/filepath.text"};
  const std::vector<int> int_data = GetIntData(file_path);
  const std::string str_data = GetStringData(file_path);

  // Use `file_path`, `int_data`, `str_data` without modifying.
  std::cout << "File path: " << file_path << '\n';
  std::cout << "Integer data: ";
  for (int num : int_data) {
    std::cout << num << " ";
  }
  std::cout << "Sum: " << GetSomeValue(int_data) << '\n';
  std::cout << "String data: " << str_data << '\n';
  std::cout << GetInterestingNumber(str_data) << '\n';
}
```
