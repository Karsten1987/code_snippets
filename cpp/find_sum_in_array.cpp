#include <iostream>
#include <unordered_set>
#include <vector>

template<class T = size_t>
void print_vector(const std::vector<T> & vec)
{
  for (const auto & el : vec) {
    std::cout << "[" << el << "] ";
  }
  std::cout << std::endl;
}

template<class T = size_t>
std::pair<size_t, size_t> find_sum_in_array(
  const std::vector<T> & vec, int sum)
{
  for (size_t i = 0u; i < vec.size(); ++i) {
    if (vec[i] >= sum) {
      continue;
    }

    auto element_pair = std::equal_range(
      vec.begin() + i, vec.end(), sum - vec[i]);
    if (element_pair.first != vec.end()) {
      return {i, std::distance(vec.begin(), element_pair.first)};
    }
  }
  return {vec.size() + 1, vec.size() + 1};
}

template<class T = size_t>
std::pair<size_t, size_t> find_sum_in_array2(
  const std::vector<T> & vec, int sum)
{
  size_t lhs = 0u;
  size_t rhs = vec.size() - 1;

  while (lhs < rhs) {
    auto possible_sum = vec[lhs] + vec[rhs];
    if (possible_sum == sum) {
      return {lhs, rhs};
    }
    if (possible_sum < sum) {
      ++lhs;
    } else {
      ++rhs;
    }
  }

  return {vec.size() + 1, vec.size() + 1};
}

template<class T = size_t>
std::pair<size_t, size_t> find_sum_in_array_unsorted(
  const std::vector<T> & vec, int sum)
{
  std::unordered_set<size_t> set;
  for (size_t i = 0; i < vec.size(); ++i) {
    if (vec[i] > sum) {
      continue;
    }

      auto complement = set.find(sum - vec[i]);
      if (complement != set.end()) {
        return {vec[i], *complement};
      }
      set.insert(vec[i]);
  }

  return {vec.size(), vec.size()};
}

int main()
{
  std::vector<size_t> vec = {1, 2, 3, 4, 5, 6, 7};
  auto expected_sum = 8;

  print_vector(vec);
  auto sums = find_sum_in_array_unsorted(vec, expected_sum);
  if (sums.first != vec.size() + 1) {
    printf("sum of %d can be found in %zu and %zu\n",
      expected_sum, sums.first, sums.second);
  } else {
    printf("no matching pair found\n");
  }

  return 0;
}
