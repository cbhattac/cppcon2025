#include <memory>
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
  static std::unique_ptr<DataHolder> Create(std::vector<int>&& data,
                                            DataProvider& provider) {
    std::unique_ptr<DataHolder> holder(new DataHolder(std::move(data)));
    provider.SetProcessor(holder.get());
    return holder;
  }
  DataHolder& operator=(DataHolder&&) noexcept = delete;

 private:
  DataHolder(std::vector<int>&& data) : data_(std::move(data)) {}

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
  MockDataProvider provider;
  [[maybe_unused]] const auto d = DataHolder::Create({1, 2, 3}, provider);
}
