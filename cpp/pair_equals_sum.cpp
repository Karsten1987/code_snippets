#include <vector>

std::pair<size_t, size_t> get_pair_to_sum(const std::vector<size_t> & v, size_t sum)
{
  size_t lhs = 0u;
  size_t rhs = v.size() -1;

  while (lhs != rhs) {
    auto tmp_sum = v[lhs] + v[rhs];
    if (tmp_sum == sum) {
      return std::make_pair(v[lhs], v[rhs]);
    }
    if (tmp_sum > sum) {
      --rhs;
    } else {
      ++lhs;
    }
  }
  return std::make_pair(0, 0);
}

int main()
{
  std::vector<size_t> v1 = {1, 1, 2, 3, 4, 4, 7, 9};
  std::vector<size_t> v2 = {1, 2, 4, 4};
  std::vector<size_t> v3 = {1, 2, 4, 5};

  size_t sum = 8;
  auto pair = get_pair_to_sum(v3, sum);
  printf("%zu + %zu = %zu\n", pair.first, pair.second, sum);

  return 0;
}
