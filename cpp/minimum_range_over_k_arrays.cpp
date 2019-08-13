// http://techieme.in/minimum-range-over-k-arrays/

#include <vector>

std::pair<int, int> get_range(
  const std::vector<std::vector<int>> & k_arrays,
  const std::vector<std::pair<size_t, size_t>> & k_ranges)
{
  int min_element = INT_MAX;
  int max_element = INT_MIN;

  for (size_t i = 0; i < k_arrays.size(); ++i) {
    auto & arr = k_arrays[i];
    if (min_element > arr[k_ranges[i].first]) {
      min_element = arr[k_ranges[i].first];
    }
    if (max_element < arr[k_ranges[i].second]) {
      max_element = arr[k_ranges[i].second];
    }
  }

  return {min_element, max_element};
}

size_t smallest_array(const std::vector<std::vector<int>> & k_array, const std::vector<std::pair<size_t, size_t>> & k_ranges)
{
  size_t smallest_k = 0u;
  for (size_t i = 0; i < k_array.size(); ++i) {
    if (k_array[i][k_ranges[i].first] < k_array[smallest_k][k_ranges[smallest_k].first]) {
      smallest_k = i;
    }
  }

  return smallest_k;
}

size_t biggest_array(const std::vector<std::vector<int>> & k_array, const std::vector<std::pair<size_t, size_t>> & k_ranges)
{
  size_t biggest_k = 0u;
  for (size_t i = 0; i < k_array.size(); ++i) {
    if (k_array[i][k_ranges[i].second] > k_array[biggest_k][k_ranges[biggest_k].second]) {
      biggest_k = i;
    }
  }

  return biggest_k;
}

std::pair<int, int> get_minimum_range(const std::vector<std::vector<int>> & k_arrays)
{
  std::vector<std::pair<size_t, size_t>> k_ranges;
  k_ranges.reserve(k_arrays.size());
  for (size_t i = 0; i < k_arrays.size(); ++i) {
    k_ranges.push_back({0u, k_arrays[i].size() - 1});
  }
  auto range = get_range(k_arrays, k_ranges);
  auto new_range = range;

  // find smallest array
  // increase start
  // break if new range > old range
  while ((new_range.second - new_range.first) <= (range.second - range.first))
  {
    range = new_range;
    auto smallest_k = smallest_array(k_arrays, k_ranges);
    if (k_ranges[smallest_k].first == k_ranges[smallest_k].second) {
      break;
    }
    k_ranges[smallest_k].first += 1;
    new_range = get_range(k_arrays, k_ranges);
  }

  while ((new_range.second - new_range.first) <= (range.second - range.first))
  {
    range = new_range;
    auto biggest_k = biggest_array(k_arrays, k_ranges);
    if (k_ranges[biggest_k].first == k_ranges[biggest_k].second) {
      break;
    }
    k_ranges[biggest_k].second -= 1;
    new_range = get_range(k_arrays, k_ranges);
  }
  return range;
}

int main()
{
  std::vector<std::vector<int>> k_arrays;
  k_arrays.push_back({5, 9, 13, 17});
  k_arrays.push_back({8, 10, 11});
  k_arrays.push_back({2, 3, 6, 7});
  std::pair<int, int> range = get_minimum_range(k_arrays);
  printf("range from %d to %d\n", range.first, range.second);

  return 0;
}
