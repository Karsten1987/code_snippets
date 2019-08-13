#include <iostream>
#include <vector>

std::pair<size_t, size_t> get_max_sum(const std::vector<int> & vec)
{
  auto size = vec.size();
  if (size == 0) {
    return {size, size};
  }
  if (size == 1) {
    return {0ul, 0ul};
  }

  size_t begin = 0ul;
  size_t end = 1ul;
  int max_sum = vec[begin];
  int tmp_sum = vec[begin];
  size_t tmp_runner = begin;

  for (size_t i = 0; i < size; ++i) {
    tmp_sum += vec[i];
    if (tmp_sum >= max_sum) {
      begin = tmp_runner;
      end = i;
      max_sum = tmp_sum;
    } else if (tmp_sum < 0) {
      tmp_runner = i + 1;
      tmp_sum = 0;
    }
  }

  std::cout << "max sum : " << max_sum << std::endl;
  return {begin, end};
}

int main()
{
  //std::vector<int> vec = {-1, 10, 4, -18, 7, 10, 9};
  std::vector<int> vec = {-11, -10, -4, -18, -7, -10, -9};
  auto max_range = get_max_sum(vec);
  std::cout << "max sum from " << max_range.first << " until " << max_range.second << std::endl;
}
