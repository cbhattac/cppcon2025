#include <new>
#include <vector>

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
  std::vector<int, MyAllocator<int>> vec1{1u, 2, MyAllocator<int>(1)};
  std::vector<int, MyAllocator<int>> vec2{1u, 3, MyAllocator<int>(2)};
  // Will crash here.
  vec1.swap(vec2);
}