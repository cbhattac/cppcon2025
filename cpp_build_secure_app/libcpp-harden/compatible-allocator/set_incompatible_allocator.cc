#include <new>
#include <set>

// A custom stateful allocator.
// It has an ID to differentiate instances.
template <class T>
class MyAllocator final {
 public:
  using value_type = T;

  explicit MyAllocator(int id) : id_(id) {}

  template <class U>
  MyAllocator(const MyAllocator<U>& other) : id_(other.id_) {}

  T* allocate(size_t n) {
    return static_cast<T*>(::operator new(n * sizeof(T)));
  }

  void deallocate(T* p, size_t /*n*/) { ::operator delete(p); }

  // Comparison operators are crucial for this example.
  // The allocators are only equal if their IDs are the same.
  friend bool operator==(const MyAllocator& a, const MyAllocator& b) {
    return a.id_ == b.id_;
  }

 private:
  const int id_;
  template <class>
  friend class MyAllocator;
};

int main() {
  // Create two sets with different MyAllocator instances (id 1 and id 2).
  // The allocators are considered incompatible because their IDs differ.
  std::set<int, std::less<int>, MyAllocator<int>> set1{MyAllocator<int>(1)};
  std::set<int, std::less<int>, MyAllocator<int>> set2{MyAllocator<int>(2)};

  set1.insert(42);

  // Extract a node from the first set.
  // This node retains the allocator information from set1.
  auto node = set1.extract(42);

  // Attempt to insert the node into the second set.
  // Since the node's allocator (id 1) is not compatible with
  // set2's allocator (id 2), this will trigger the assertion.
  set2.insert(std::move(node));
}