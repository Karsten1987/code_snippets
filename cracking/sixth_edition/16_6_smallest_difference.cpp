#include <algorithm>
#include <iostream>
#include <vector>

template<class T>
void print_vector(const std::vector<T> & vec)
{
  for (const auto & el : vec) {
    std::cout << "[" << el << "]";
  }
  std::cout << std::endl;
}

template<class T>
size_t smallest_difference(
  std::vector<T> & v1,
  std::vector<T> & v2)
{
  std::sort(v1.begin(), v1.end(), std::greater<T>());
  std::sort(v2.begin(), v2.end());

  print_vector(v1);
  print_vector(v2);

  auto v1_iter = v1.begin();
  auto v2_iter = v2.begin();

  auto max_diff = *v1_iter - *v2_iter;
  while (*v1_iter >= *v2_iter && v1_iter != v1.end() && v2_iter != v2.end()) {
    max_diff = *v1_iter - *v2_iter;
    ++v1_iter;
  }

  return max_diff;
}

int main()
{
  std::vector<int> v1 = {1, 3, 11, 15, 2, 10};
  std::vector<int> v2 = {23, 127, 235, 19, 8};

  auto diff = smallest_difference(v1, v2);
  std::cout << "smallest diff is " << diff << std::endl;
}
