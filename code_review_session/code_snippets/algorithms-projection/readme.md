# Use projections in STL algorithms when possible

C++20 introduced projections for many STL algorithms, allowing you to operate on a member or property directly, making code more concise and expressive.

## Why is this important?
- Projections reduce boilerplate and improve readability.
- They allow you to focus on the property of interest without writing extra lambdas.

### Example: Sorting by a class property.
```cpp
struct City {
  std::string name;
  int population = 0;
  int height_in_feet = 0;
};
```
```cpp
// More verbose.
void SortSpecial(std::span<City> cities) {
  std::ranges::sort(cities, [](const City& a, const City& b) {
    return a.population < b.population;
  });
}
```
```cpp
// More concise using projection.
void SortSpecial(std::span<City> cities) {
  std::ranges::sort(cities, {}, &City::population);
}
```

### Nuance: Projections with member variables
Projections can be used with member variables as well, e.g., `&MyStruct::member`.
