#include <vector>
#include <unordered_map>

void print_k_most_elements(const std::vector<size_t> & v, size_t k)
{
  std::unordered_map<size_t, size_t> map;

  for (auto v_i : v) {
    map[v_i]++;
  }

  for (auto n = 0u; n < k; ++n) {
    size_t max_element = 0u;
    size_t max_count = 0u;
    for (size_t i = 0u; i < v.size(); ++i) {
      //printf("vi %zu occurs %zu times\n", v[i], map[v[i]]);
      if (map[v[i]] > max_count) {
        max_element = v[i];
        max_count = map[v[i]];
      }
    }

    printf("max element %zu\n", max_element);
    printf("max count %zu\n", max_count);

    map.erase(max_element);
  }
}

int main()
{
  std::vector<size_t> v = {1, 2, 432, 432, 2, 32, 3, 43, 543, 65, 5, 6, 5, 5, 43, 4};

  size_t k = 3;

  print_k_most_elements(v, k);

  return 0;
}
