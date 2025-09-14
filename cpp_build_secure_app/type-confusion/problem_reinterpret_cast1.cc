#include <memory.h>

#include <iostream>
#include <optional>

std::optional<float> GetFloat(char* p, size_t n) {
  if (n < sizeof(float)) {
    return std::nullopt;
  }
  return *reinterpret_cast<float*>(p);
}

std::optional<float> GetFloatCorrect(char* p, size_t n) {
  if (n < sizeof(float)) {
    return std::nullopt;
  }
  float f;
  memcpy(&f, p, sizeof(float));
  return f;
}

int main() {
  float f = 10;
  char* f_as_char = reinterpret_cast<char*>(&f);
  std::cout << GetFloat(f_as_char, sizeof(f)).value() << ", "
            << GetFloatCorrect(f_as_char, sizeof(f)).value() << '\n';
  // This code can produce undefined behavior with GetFloat.
  char buffer[2 * sizeof(float)]{};
  char* float_buffer = &buffer[2];
  memcpy(float_buffer, &f, sizeof(f));
  std::cout << GetFloat(float_buffer, sizeof(f)).value() << ", "
            << GetFloatCorrect(float_buffer, sizeof(f)).value() << '\n';
}
