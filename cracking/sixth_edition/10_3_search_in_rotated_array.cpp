#include <iostream>
#include <vector>

template<class T>
void print_vector(const std::vector<T> & vec)
{
  for (const auto & element : vec)
  {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

template<class T>
size_t binary_search(const std::vector<T> & vec, size_t lhs, size_t rhs, const T & element)
{
  if (lhs == rhs) {
    if (vec[lhs] == element) {
      return lhs;
    }
    return vec.size() + 1;
  }

  auto middle = lhs + ((rhs - lhs) / 2);
  if (vec[middle] < element) {
    return binary_search(vec, lhs, middle, element);
  } else if (vec[middle] > element) {
    return binary_search(vec, middle, rhs, element);
  } return middle;
}

template<class T>
size_t find_rotated_array(const std::vector<T> & vec, size_t lhs, size_t rhs, const T & element)
{
  size_t rotation_point = lhs;
  while (lhs <= rhs) {
    // early escape
    if (vec[lhs] == element) {
      return lhs;
    }
    if (vec[rhs] == element) {
      return rhs;
    }

    if (vec[lhs] > vec[lhs + 1]) {
      rotation_point = lhs;
    }
    if (vec[rhs] < vec[rhs - 1]) {
      rotation_point = rhs - 1;
    }
    ++lhs;
    --rhs;
  }

  if (vec[lhs] <= element && element <= vec[rotation_point]) {
     return binary_search(vec, lhs, rotation_point, element);
  } else {
     return binary_search(vec, rotation_point + 1, rhs, element);
  }
  return vec.size() + 1;
}

int main()
{
  std::vector<size_t> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::rotate(vec.begin(), vec.begin() + 2, vec.end());
  print_vector(vec);
  auto element = 10lu;
  auto index = find_rotated_array(vec, 0, vec.size() - 1, element);
  std::cout << "rotation element " <<  element << " at index " << index << " [" << vec[index] << "]" <<  std::endl;
}
