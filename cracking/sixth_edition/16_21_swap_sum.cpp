#include <iostream>
#include <numeric>
#include <vector>


std::pair<int, int> swap_sum(std::vector<int> & v1, std::vector<int> & v2)
{
  int sum1 = std::accumulate(v1.begin(), v1.end(), 0);
  int sum2 = std::accumulate(v2.begin(), v2.end(), 0);

  for (const auto & v : v1) {
    int element_to_look_for = (sum2 + v + v - sum1) / 2;
    auto element_iter = std::find(v2.begin(), v2.end(), element_to_look_for);
    if (element_iter != v2.end()) {
      return {v, element_to_look_for};
    }
  }

  return {0, 0};
}

int main()
{
  // sort arrays for better performance
  // or
  // push vec2 into a hashset and look it up directly (more space)
  std::vector<int> vec1 = {4, 1, 2, 1, 1, 2};
  std::vector<int> vec2 = {3, 6, 3, 3};

  std::pair<int, int> swapped_elements = swap_sum(vec1, vec2);

  std::cout << "two elements to swap " << swapped_elements.first << " " << swapped_elements.second << std::endl;
}
