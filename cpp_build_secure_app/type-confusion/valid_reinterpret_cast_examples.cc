#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

class ExampleStruct {
 public:
  ExampleStruct(int a, double b) : a_(a), b_(b) {}
  int a() const { return a_; }
  double b() const { return b_; }

 private:
  int a_;
  double b_;
};

// Inspect object representation bytes via unsigned char*
void ExampleInspectBytes() {
  std::cout << "--- ExampleInspectBytes ---\n";
  ExampleStruct s(42, 3.141592653589793);
  unsigned char* p = reinterpret_cast<unsigned char*>(&s);  // allowed
  std::cout << "raw bytes of ExampleStruct (size=" << sizeof(s) << "):";
  for (std::size_t i = 0; i < sizeof(s); ++i) {
    std::cout << ' ' << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(p[i]);
  }
  std::cout << std::dec << '\n';
}

// Pointer to standard-layout object <-> pointer to its first non-static data
// member
void ExampleFirstMemberPointer() {
  std::cout << "--- ExampleFirstMemberPointer ---\n";
  ExampleStruct s(7, 0.0);
  // For standard-layout-like layout, the address of the object equals address
  // of its first member in many implementations. Demonstration:
  // reinterpret_cast to int*.
  int* pa = reinterpret_cast<int*>(
      &s);  // points to first data at the object's address
  std::cout << "first-member value via pointer = " << *pa << '\n';
}

// Pointer -> uintptr_t -> pointer round-trip
void ExampleUintptrRoundtrip() {
  std::cout << "--- ExampleUintptrRoundtrip ---\n";
  int x = 1234;
  std::uintptr_t as_int =
      reinterpret_cast<std::uintptr_t>(&x);  // store pointer as integer
  int* p = reinterpret_cast<int*>(as_int);   // restore pointer
  std::cout << "restored value = " << *p << '\n';
}

// void* round-trip
void ExampleVoidptrRoundtrip() {
  std::cout << "--- ExampleVoidptrRoundtrip ---\n";
  int x = 99;
  void* v = reinterpret_cast<void*>(&x);
  int* p = reinterpret_cast<int*>(v);
  std::cout << "via void* = " << *p << '\n';
}

// Function used by function-pointer example.
void ExampleFreeFunction() {
  std::cout << "ExampleFreeFunction()\n";
}

// Function-pointer conversion round-trip (call only with correct type)
void ExampleFunctionPointerRoundtrip() {
  std::cout << "--- ExampleFunctionPointerRoundtrip ---\n";
  using Fn1 = void (*)();
  using Fn2 = void (*)(int);

  Fn1 f1 = &ExampleFreeFunction;
  Fn2 f2 = reinterpret_cast<Fn2>(f1);   // allowed to convert
  Fn1 f1b = reinterpret_cast<Fn1>(f2);  // convert back
  f1b();  // safe because we call using the original, correct type
}

int main() {
  ExampleInspectBytes();
  ExampleFirstMemberPointer();
  ExampleUintptrRoundtrip();
  ExampleVoidptrRoundtrip();
  ExampleFunctionPointerRoundtrip();
}

/*
--- ExampleInspectBytes ---
raw bytes of ExampleStruct (size=16): 2a 00 00 00 40 79 00 00 18 2d 44 54 fb 21 09 40
--- ExampleFirstMemberPointer ---
first-member value via pointer = 7
--- ExampleUintptrRoundtrip ---
restored value = 1234
--- ExampleVoidptrRoundtrip ---
via void* = 99
--- ExampleFunctionPointerRoundtrip ---
ExampleFreeFunction()
*/

// Even though they are valid, they will be flagged by cppcoreguidelines-pro-type-reinterpret-cast.