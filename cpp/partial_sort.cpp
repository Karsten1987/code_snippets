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

int main()
{
  std::vector<int> vec = {4, 13, 12, 7, 9, 5, 15, 14, 2, 11, 6, 16, 10, 1,8, 3};

  auto sf = vec.begin() + 5;
  auto sl = vec.begin() + 10;
  std::cout << "sorted subrange between " << *sf << " and " << *sl << std::endl;
  //std::nth_element(vec.begin(), sf, vec.end());
  std::partial_sort(++sf, sl, vec.end());
  print_vector(vec);

  return 0;
}
