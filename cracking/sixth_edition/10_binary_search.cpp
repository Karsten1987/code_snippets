#include <vector>
#include <iostream>

template<class T>
void print_vector(const std::vector<T> & vec)
{
  for (auto & element : vec) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

template<class T>
size_t binary_search(const std::vector<T> & vec, int lhs, int rhs, T element)
{
  if (lhs >= rhs) {
    return vec.size() + 1;
  }

  int middle_index = (lhs + rhs) / 2;
  if (vec[middle_index] == element) {
    return middle_index;
  }

  if (vec[middle_index] > element) {
    return binary_search<T>(vec, lhs, middle_index - 1, element);
  }
  if (vec[middle_index] < element) {
    return binary_search<T>(vec, middle_index + 1, rhs, element);
  }

  return vec.size() + 1;
}

template<class T>
size_t binary_search(const std::vector<T> & vec, T element)
{
  return binary_search(vec, 0, vec.size() -1, element);
}

int main()
{
  std::vector<size_t> vec = {1, 5, 32, 67, 928, 2, 4, 5, 18};
  std::sort(vec.begin(), vec.end());
  print_vector(vec);

  size_t element = 3;
  size_t index = binary_search(vec, element);
  printf("found %zu at position %zu\n", element, index);
}
