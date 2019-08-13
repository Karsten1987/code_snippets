#include <iostream>
#include <algorithm>
#include <vector>

template<class T>
void print_vector(const std::vector<T> & vec)
{
  for (auto & el : vec) {
    std::cout << el << " ";
  }
  std::cout << std::endl;
}

template<class T>
void reverse(std::vector<T> & vec, int lhs, int rhs)
{
  while (lhs < rhs) {
    std::swap(vec[lhs], vec[rhs]);
    ++lhs;
    --rhs;
  }
}

template<class T>
int rotate(std::vector<T> & vec, int lhs, int rhs, int k)
{
  std::cout << "rotate lhs=" << vec[lhs] << " and " << vec[rhs] << " around k=" << k << std::endl;
  if (k == 0) {
    return 0;
  }
  reverse(vec, lhs, lhs + k - 1);
  reverse(vec, lhs + k, rhs);
  reverse(vec, lhs, rhs);

  return lhs + (rhs - k);
}

template<class T, class P>
int stable_partition(std::vector<T> & vec, int lhs, int rhs, P p)
{
  std::cout << "lhs=" << vec[lhs] << " rhs=" << vec[rhs] << std::endl;
  auto n = rhs - lhs + 1;
  std::cout << "n = " << n << std::endl;
  if (n == 1) {
    return p(vec[lhs]) ? 1 : 0;
  }

  auto middle = lhs + (rhs - lhs) / 2;
  auto good_elements_lhs = stable_partition(vec, lhs, middle, p);
  auto good_elements_rhs = stable_partition(vec, middle + 1, rhs, p);

  std::cout << "good_elements_lhs " << good_elements_lhs << std::endl;
  std::cout << "good_elements_rhs " << good_elements_rhs << std::endl;

  std::cout << "nongood guys left = " << (middle + 1 - lhs) - good_elements_lhs << std::endl;
  rotate(vec, lhs + good_elements_lhs, middle + good_elements_rhs, (middle + 1 - lhs) - good_elements_lhs);
  std::cout << "rotated vector ";
  print_vector(vec);
  return good_elements_lhs + good_elements_rhs;
}

int main()
{
  std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  //std::vector<int> vec = {1, 2, 3, 4};

  print_vector(vec);

  auto is_even = [](int i) -> bool { return i % 2 == 0 ? true : false; };
  auto is_odd = [](int i) -> bool { return i % 2 != 0 ? true : false; };
  stable_partition(vec, 0, vec.size() -1, is_odd);
  print_vector(vec);
  return 0;
}
