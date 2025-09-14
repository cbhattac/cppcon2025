#include <stdint.h>

#include <numeric>

// !!! NEEDS C++26 !!!

int main() {
  const int8_t a = 8;
  const int16_t b = 16;
  const auto c = a + b;
  const auto d = std::add_sat(a, b);
}

// FAILS AT COMPILE TIME.
/*
error: no matching function for call to 'add_sat'
   const auto d = std::add_sat(a, b);
                  ^~~~~~~~~~~~
*/