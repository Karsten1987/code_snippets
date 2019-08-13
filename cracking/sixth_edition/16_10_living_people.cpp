#include <iostream>
#include <vector>

struct Person
{
  size_t birth_year;
  size_t death_year;
};

void print_vector(const std::vector<int> & vec)
{
  for (const auto & el : vec) {
    std::cout << "[" << el << "]";
  }
  std::cout << std::endl;
}

int get_max_year(
  const std::vector<Person> & vec, int min_year, int max_year)
{
  std::vector<int> living_people_per_year(max_year - min_year + 2);

  int currently_living = 0;
  for (auto & p : vec) {
    ++currently_living;
    living_people_per_year[p.birth_year - min_year] = currently_living;
  }
  for (auto & p : vec) {
    --currently_living;
    living_people_per_year[p.death_year - min_year] = currently_living;
  }

  print_vector(living_people_per_year);

  int max_population = 0;
  for (size_t i = 0lu; i < living_people_per_year.size(); ++i) {
    if (living_people_per_year[i] > max_population) {
      max_year = min_year + i;
      max_population = living_people_per_year[i];
    }
  }

  return max_year;
}

int main()
{
  std::vector<Person> vec;
  vec.push_back({1908, 1990});
  vec.push_back({1912, 1997});
  vec.push_back({1916, 2000});
  vec.push_back({1900, 1999});
  vec.push_back({1950, 1987});

  auto max_year = get_max_year(vec, 1900, 2000);
  std::cout << "max year: " << max_year << std::endl;
}
