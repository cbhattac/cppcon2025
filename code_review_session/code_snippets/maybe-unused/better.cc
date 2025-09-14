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

void ProcessData(const Data& data, [[maybe_unused]] bool force_reload) {
  // ... process data ...
  data.DumpData();
}

void HandleData() {
  auto result = LoadData();
  if (result) {
    ProcessData(*result, false);
  } else {
    [[maybe_unused]] const int error_code = result.error();
#ifndef NDEBUG
    std::cerr << "Error loading data: " << error_code << '\n';
#endif
  }
}

int main() {
  HandleData();
}