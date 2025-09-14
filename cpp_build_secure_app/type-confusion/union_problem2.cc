#include <iostream>
#include <new>
#include <optional>
#include <string>
#include <vector>

struct Wrapper {
  std::optional<bool> is_string_;
  union U {
    std::string s;
    std::vector<int> v;
    U() {}   // trivial default
    ~U() {}  // destruction managed manually
  } u;

  void SetString(const std::string& str) {
    new (&u.s) std::string(str);
    is_string_ = true;
  }
  void SetVector(std::vector<int> vv) {
    new (&u.v) std::vector<int>(std::move(vv));
    is_string_ = false;
  }
  ~Wrapper() {
    if (!is_string_) {
      return;
    }
    if (*is_string_) {
      u.s.~basic_string();
    } else {
      u.v.~vector();
    }
  }
  void Print() const {
    if (!is_string_) {
      return;
    }
    if (*is_string_) {
      std::cout << "String: " << u.s << '\n';
    } else {
      std::cout << "Vector: ";
      for (const auto i : u.v) {
        std::cout << i << ' ';
      }
      std::cout << '\n';
    }
  }
};

int main() {
  Wrapper w;
  w.Print();
  w.SetString("hello world, this is long");
  w.Print();
  w.SetVector({1, 2, 3});
  w.Print();
}

// When run with -fsanitize=address
/*
=================================================================
==1==ERROR: LeakSanitizer: detected memory leaks
Direct leak of 32 byte(s) in 1 object(s) allocated from:
    #0 0x5a2fc04bbb3d in operator new(unsigned long) /root/llvm-project/compiler-rt/lib/asan/asan_new_delete.cpp:86:3
    #1 0x5a2fc04be346 in void* std::__1::__libcpp_operator_new[abi:se200100]<unsigned long>(unsigned long) /opt/compiler-explorer/clang-20.1.0/bin/../include/c++/v1/__new/allocate.h:37:10
    #2 0x5a2fc04be346 in char* std::__1::__libcpp_allocate[abi:se200100]<char>(std::__1::__element_count, unsigned long) /opt/compiler-explorer/clang-20.1.0/bin/../include/c++/v1/__new/allocate.h:64:28
    #3 0x5a2fc04be346 in std::__1::allocator<char>::allocate[abi:se200100](unsigned long) /opt/compiler-explorer/clang-20.1.0/bin/../include/c++/v1/__memory/allocator.h:105:14
    #4 0x5a2fc04be346 in std::__1::__allocation_result<std::__1::allocator_traits<std::__1::allocator<char>>::pointer> std::__1::__allocate_at_least[abi:se200100]<std::__1::allocator<char>>(std::__1::allocator<char>&, unsigned long) /opt/compiler-explorer/clang-20.1.0/bin/../include/c++/v1/__memory/allocate_at_least.h:41:19
    #5 0x5a2fc04be346 in std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>::__init_copy_ctor_external(char const*, unsigned long) /opt/compiler-explorer/clang-20.1.0/bin/../include/c++/v1/string:2393:25
    #6 0x77f614e29d8f  (/lib/x86_64-linux-gnu/libc.so.6+0x29d8f) (BuildId: d5197096f709801829b118af1b7cf6631efa2dcd)

SUMMARY: AddressSanitizer: 32 byte(s) leaked in 1 allocation(s).
*/