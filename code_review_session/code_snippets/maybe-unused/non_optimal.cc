#include <expected>
#include <iostream>

struct Data {
  // Data members...
  void DumpData() const {
    // Do some data processing.
  }
};

std::expected<Data, int> LoadData() {
  // Simulate a failure for demonstration.
  return std::unexpected(42);  // Example error code
}

void ProcessData(const Data& data, bool force_reload) {
  (void)force_reload;  // Unused in this specific implementation.
  // ... process data ...
  data.DumpData();
}

void HandleData() {
  auto result = LoadData();
  if (result) {
    ProcessData(*result, false);
  } else {
    const int error_code = result.error();
#ifndef NDEBUG
    std::cerr << "Error loading data: " << error_code << '\n';
#endif
    (void)error_code;
  }
}

int main() {
  HandleData();
}

// Without (void).
/*
-Wunused-variable (-Wall) -Wunused-parameter (-Wextra)

error: unused parameter 'force_reload' [-Werror,-Wunused-parameter]
 void ProcessData(const Data& data, bool force_reload) {
                                         ^
error: unused variable 'error_code' [-Werror,-Wunused-variable]
     const int error_code = result.error();
               ^~~~~~~~~~
*/
