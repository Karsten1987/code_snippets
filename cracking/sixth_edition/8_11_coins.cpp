#include <iostream>
#include <unordered_map>
#include <vector>

struct Change
{
  size_t quarters;
  size_t dimes;
  size_t nickel;
  size_t pennies;
};

int make_change(size_t cents, std::vector<Change> & vec, std::unordered_map<size_t, std::vector<size_t>> & memo)
{
  if (cents == 0) {
    vec.push_back(Change());
    return 1;
  }

  auto mem = memo.find(cents);

  if (mem == memo.end()) {
    memo[cents] = std::vector<size_t>();
  }
  mem = memo.find(cents);

  auto ways = 0;
  if (cents >= 25) {
    if (std::find(mem->second.begin(), mem->second.end(), 25) == mem->second.end()) {
      memo[cents].push_back(25);

      ways += make_change(cents - 25, vec, memo);
      for (auto & change : vec) {
        ++change.quarters;
      }
    }
  }
  if (cents >= 10) {
    if (std::find(mem->second.begin(), mem->second.end(), 10) == mem->second.end()) {
      memo[cents].push_back(10);
    std::vector<Change> changes;
    ways += make_change(cents - 10, changes, memo);
    for (auto & change : changes) {
      ++change.dimes;
    }
    vec.insert(vec.end(), changes.begin(), changes.end());
    }
  }
  if (cents >= 5) {
    if (std::find(mem->second.begin(), mem->second.end(), 5) == mem->second.end()) {
      memo[cents].push_back(5);
    std::vector<Change> changes;
    ways += make_change(cents - 5, changes, memo);
    for (auto & change : changes) {
      ++change.nickel;
    }
    vec.insert(vec.end(), changes.begin(), changes.end());
    }
  }
  if (cents >= 1) {
    if (std::find(mem->second.begin(), mem->second.end(), 1) == mem->second.end()) {
      memo[cents].push_back(1);
      std::vector<Change> changes;
      ways += make_change(cents - 1, changes, memo);
      for (auto & change : changes) {
        ++change.pennies;
      }
      vec.insert(vec.end(), changes.begin(), changes.end());
    }
  }

  return ways;
}

int main()
{
  size_t cents = 50;
  std::vector<Change> changes;
  std::unordered_map<size_t, std::vector<size_t>> memo;
  auto ways = make_change(cents, changes, memo);
  std::cout << "ways: " << ways << std::endl;

  for (auto & change : changes) {
    std::cout << "quarters: " << change.quarters << " dimes: " << change.dimes << " nickel: " << change.nickel << " pennies: " << change.pennies;
    std::cout << " sum: " << change.quarters * 25 + change.dimes * 10 + change.nickel * 5 + change.pennies * 1 << std::endl;
  }
}
