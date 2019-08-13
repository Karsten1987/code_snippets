#include <iostream>
#include <vector>

size_t magic_index_bf(const std::vector<int> & vec)
{
  for (size_t i = 0lu; i < vec.size(); ++i) {
    if (vec[i] == static_cast<int>(i)) {
      return i;
    }
  }
  return vec.size();
}

size_t magic_index_bs(const std::vector<int> & vec, size_t lhs, size_t rhs)
{
  if (lhs == rhs) {
    if (vec[lhs] == static_cast<int>(lhs)) {
      return lhs;
    }
    else {
      return vec.size();
    }
  }

  auto middle = lhs + ((rhs - lhs) / 2);
  printf("looking for middle %zu\n", middle);
  if (vec[middle] == static_cast<int>(middle)) {
    return middle;
  }
  if (vec[middle] > static_cast<int>(middle)) {
    return magic_index_bs(vec, lhs, middle);
  } else {
    return magic_index_bs(vec, middle + 1, rhs);
  }
  return vec.size();
}

int main()
{
  //std::vector<int> magic_vector = {-10, -8, 1, 2, 3, 5, 6, 7, 8, 9};
  //std::vector<int> magic_vector = {-10, -8, 1, 2, 3, 6, 7, 8, 9, 10};
  std::vector<int> magic_vector = {5, 5, 5, 5, 5, 5, 5,5 ,5 ,5 ,5 ,5};
  //size_t index = magic_index_bf(magic_vector);
  size_t index = magic_index_bs(magic_vector, 0, magic_vector.size() - 1);
  if (index < magic_vector.size()) {
    std::cout << index << " -> " << magic_vector[index] << std::endl;
  } else {
    std::cout << "no magic index found" << std::endl;
  }

  return 0;
}
