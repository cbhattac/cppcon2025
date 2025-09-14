# Prefer std::ranges Algorithms Over Classic std Algorithms

C++20 introduced ranges-based algorithms, which are safer and more expressive than classic iterator-based algorithms.

## Problem: Classic std algorithms with iterators
```cpp
void PrintSorted(const std::vector<int>& v) {
  std::vector<int> copy = v;
  std::sort(copy.begin(), copy.end());
  for (auto it = copy.begin(); it != copy.end(); ++it) {
    std::cout << *it << ' ';
  }
}
```

### Fix: Use std::ranges algorithms
```cpp
void PrintSorted(const std::vector<int>& v) {
  std::vector<int> copy = v;
  std::ranges::sort(copy);
  for (int x : copy) {
    std::cout << x << ' ';
  }
}
```

## Nuance: Readability and safety
Ranges algorithms operate directly on containers, reducing the risk of iterator errors and improving readability.

## Nuance: Pipelining and views
Ranges algorithms can be composed with views for powerful data transformations:
```cpp
for (int x : v | std::views::filter([](int x){ return x > 0; }) | std::views::transform([](int x){ return x * 2; })) {
  std::cout << x << ' ';
}
```

## Nuance: Compatibility
Ranges algorithms require C++20. Not all codebases or compilers may support them yet.
