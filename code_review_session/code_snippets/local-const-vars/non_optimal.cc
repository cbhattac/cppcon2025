#include <iostream>
#include <numeric>
#include <span>
#include <string>
#include <vector>

// clang-tidy check: readability-const-return-type
// Clang-C++ warning: none

std::vector<int> GetIntData(const std::string& str);
std::string GetStringData(const std::string& str);
int GetInterestingNumber(std::string_view s);
int GetSomeValue(std::span<const int> sp);

void Calculate(double radius) {
  double pi = 3.14159;
  double circumference = 2 * pi * radius;
  double area = pi * radius * radius;

  std::cout << "For a circle with radius " << radius << ":\n";
  std::cout << "Circumference: " << circumference << "\n";
  std::cout << "Area: " << area << '\n';
}

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

int main() {
  ProcessData();
}

std::vector<int> GetIntData(const std::string& str) {
  // Simulate extracting integers from a string
  std::vector<int> data;
  for (char ch : str) {
    if (std::isdigit(ch)) {
      data.push_back(ch - '0');
    }
  }
  return data;
}

std::string GetStringData(const std::string& str) {
  // Simulate extracting alphabetic characters from a string
  std::string result;
  for (char ch : str) {
    if (std::isalpha(ch)) {
      result += ch;
    }
  }
  return result;
}

int GetInterestingNumber(std::string_view s) {
  // Return the length of the string as an "interesting" number
  return static_cast<int>(s.size());
}

int GetSomeValue(std::span<const int> sp) {
  // Calculate the sum of integers in the span.
  return std::accumulate(sp.begin(), sp.end(), 0);
}

/*
File path: folder/filepath.text
Integer data: Sum: 0
String data: folderfilepathtext
18
*/