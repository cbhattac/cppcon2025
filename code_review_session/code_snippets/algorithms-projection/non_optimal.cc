#include <algorithm>
#include <iostream>
#include <span>
#include <string>

// clang-tidy check: none
// Clang-C++ warning: none

struct City {
  std::string name;
  int population = 0;
  int height_in_feet = 0;
};

void SortSpecial(std::span<City> cities) {
  std::ranges::sort(cities, [](const City& a, const City& b) {
    return a.population < b.population;
  });
}

bool HasCityWithHeight(std::span<City> cities, int height) {
  return std::ranges::find_if(cities, [height](const City& a) {
           return a.height_in_feet == height;
         }) != cities.end();
}

void Print(const City& c) {
  const auto& [name, pop, height] = c;
  std::cout << "Name: " << name << ", population: " << pop
            << ", height: " << height << '\n';
}

int main() {
  City cities[]{{.name = "CityA", .population = 20000, .height_in_feet = 500},
                {.name = "CityB", .population = 5000, .height_in_feet = 5000},
                {.name = "CityC", .population = 2000, .height_in_feet = 200},
                {.name = "CityD", .population = 10000, .height_in_feet = 8000}};
  std::cout << std::boolalpha
            << "HasCityWithHeight(200): " << HasCityWithHeight(cities, 200)
            << '\n';
  SortSpecial(cities);
  for (const auto& c : cities) {
    Print(c);
  }
}

/*
HasCityWithHeight(200): true
Name: CityC, population: 2000, height: 200
Name: CityB, population: 5000, height: 5000
Name: CityD, population: 10000, height: 8000
Name: CityA, population: 20000, height: 500
*/