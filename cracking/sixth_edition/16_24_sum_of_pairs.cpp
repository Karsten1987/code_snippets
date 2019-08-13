#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<std::pair<size_t, size_t>> get_pair_of_sum(const std::vector<size_t> & vec, size_t sum)
{
  std::vector<std::pair<size_t, size_t>> pairs;

  // map from value to indeces
  std::unordered_map<size_t, size_t> compliments;
  for (size_t i = 0; i < vec.size(); ++i)
  {
    auto compliment = compliments.find(sum - vec[i]);
    if (compliment != compliments.end()) {
      pairs.push_back({compliment->second, i});
    } else {
      compliments.insert({vec[i], i});
    }
  }

  return pairs;
}

int main()
{
  size_t sum = 7;
  std::vector<size_t> vec = {1, 3, 5, 2, 7, 4, 8};

  auto pairs = get_pair_of_sum(vec, sum);
  for (const auto & pair : pairs) {
    std::cout << pair.first << " " << pair.second << std::endl;
  }
  return 0;
}
