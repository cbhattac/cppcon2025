#include <vector>

class DataProcessor {
 public:
  virtual ~DataProcessor() = default;
  virtual void ProcessData() = 0;
};

class DataProvider {
 public:
  virtual ~DataProvider() = default;
  virtual void SetProcessor(DataProcessor* processor) = 0;
};

// clang-tidy check: none
// Clang-C++ warning: none
class DataHolder : public DataProcessor {
 public:
  DataHolder() = default;
  DataHolder& operator=(DataHolder&&) noexcept = delete;

  void Init(std::vector<int>&& data, DataProvider& provider) {
    data_ = std::move(data);
    // Needs a fully created object, so that virtual functions can be called.
    provider.SetProcessor(this);
    // Other stuff.
  }

 private:
  void ProcessData() override {
    // Process data here.
  }

  std::vector<int> data_;
};

class MockDataProvider : public DataProvider {
 public:
  void SetProcessor(DataProcessor* processor) override {
    // Store the processor for later use.
    processor_ = processor;
  }

 private:
  DataProcessor* processor_ = nullptr;
};

int main() {
  DataHolder d;
  MockDataProvider provider;
  d.Init({1, 2, 3}, provider);
}
