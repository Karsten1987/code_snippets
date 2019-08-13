#include <vector>

struct Profit
{
  int profit;
  size_t buy_index;
  size_t sell_index;
};

template<class T>
Profit get_max_profit(const std::vector<T> & vec)
{
  size_t max_element = 1u;
  size_t min_element = 0u;
  int max_profit = vec[1] - vec[0];

  for (size_t i = 1; i < vec.size(); ++i) {
    // check for selling right now
    if (vec[i] < vec[min_element]) {
      min_element = i;
    }

    if (vec[i] - vec[min_element] > max_profit) {
      max_profit = vec[i] - vec[min_element];
      max_element = i;
    }

  }

  Profit p;
  p.buy_index = min_element;
  p.sell_index = max_element;
  p.profit = max_profit;
  return p;
}

int main()
{
  // idea is to maximize profit
  // idnex of array is time line
  // value of each is value at time x
  //
  // can't sell before buying

  //std::vector<int> stocks = {5, 9, 2, 4, 7, 11, 24, 3, 100, 1};
  std::vector<int> stocks = {2, 2, 1, 3};
  auto max_profit = get_max_profit(stocks);
  printf("max profit of %d can be reach when buying at %zu and selling at %zu\n", 
    max_profit.profit, max_profit.buy_index, max_profit.sell_index);

  return 0;
}
