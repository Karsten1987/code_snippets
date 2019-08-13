#include <iostream>
#include <vector>

template<class T>
void print_vector(const std::vector<T> & vec)
{
  for (const auto & el : vec) {
    std::cout << "[" << el << "] -->";
  }
  std::cout << std::endl;
}

template<class T>
size_t find_rotation_point(const std::vector<T> & vec, size_t lhs, size_t rhs)
{
  if (lhs >= rhs) {
    // failure code
    return vec.size();
  }

  if (vec[lhs] < vec[rhs]) {
    return vec.size();
  }

  auto middle = lhs + ((rhs - lhs) / 2);
  // vec[lhs] > vec[middle] = left side is rotated
  if (vec[lhs] > vec[middle]) {
    return find_rotation_point(vec, lhs, middle);
  }
  if (vec[middle + 1] > vec[rhs]) {
    return find_rotation_point(vec, middle + 1, rhs);
  }
  return middle;
}

template<class T>
size_t find_rotation_point(const std::vector<T> & vec)
{
  return find_rotation_point(vec, 0u, vec.size() -1);
}

int main()
{
  //std::vector<size_t> vec = {4, 5, 6, 7, 8, 10, 1, 2, 3};
  std::vector<size_t> vec = {10, 1, 2, 3};
  size_t rp = find_rotation_point(vec);
  print_vector(vec);
  printf("found rotation point at index %zu with element %zu\n",
    rp, vec[rp]);

  return 0;
}
