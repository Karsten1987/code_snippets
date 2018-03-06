#include <iostream>
#include <chrono>
#include <thread>

#include "astar/grid.hpp"

using namespace std::chrono_literals;

/**
 * 0 0 0 0 0 2 2 2
 * 0 0 x 0 0 2 2 2
 * 0 0 0 0 0 2 x 2
 * 1 1 1 1 1 2 2 2
 * 1 1 x 1 1 2 2 2
 */

size_t
manhatten_distance(astar::GridIndex  & lhs, astar::GridIndex & rhs)
{
  return (lhs.row - rhs.row) * (lhs.row - rhs.row)
    + (lhs.col - rhs.col) * (lhs.col - rhs.col);
}

astar::GridIndex
calculate_mean(double & mean_row, double & mean_col, size_t mean_multiplier, astar::GridIndex & index)
{
  mean_row = (mean_row * mean_multiplier + index.row) / (mean_multiplier + 1);
  mean_col = (mean_col * mean_multiplier + index.col) / (mean_multiplier + 1);
  return astar::GridIndex {static_cast<size_t>(mean_row), static_cast<size_t>(mean_col)};
}

int main(int charc, char ** argv)
{
  size_t rows = 10;
  size_t cols = 9;

  astar::GridValue<std::uint8_t> default_value {0, " 0 |"};
  astar::GridValue<std::uint8_t> class1_value {1, "\033[1;1;52;31m 1 \033[0m|"};
  astar::GridValue<std::uint8_t> mean1_value {1, "\033[1;4;52;31m 1 \033[0m|"};
  astar::GridValue<std::uint8_t> class2_value {2, "\033[1;1;32m 2 \033[0m|"};
  astar::GridValue<std::uint8_t> mean2_value {2, "\033[1;4;32m 2 \033[0m|"};

  astar::Grid<std::uint8_t> g(rows, cols);
  for (auto r = 0u; r < rows; ++r) {
    for (auto c = 0u; c < cols; ++c) {
      astar::GridIndex index {r, c};
      g.set_value(index, default_value);
    }
  }

  size_t mean1_multiplier = 1;
  size_t mean2_multiplier = 1;

  double mean1_row = 4.0;
  double mean1_col = 2.0;
  double mean2_row = 4.0;
  double mean2_col = 7.0;

  astar::GridIndex mean1_index {static_cast<size_t>(mean1_row), static_cast<size_t>(mean1_col)};
  astar::GridIndex mean2_index {static_cast<size_t>(mean2_row), static_cast<size_t>(mean2_col)};

  g.set_value(mean1_index, mean1_value);
  g.set_value(mean2_index, mean2_value);

  g.print();
  std::cout << "**** applying knn ****" << std::endl;

  for (auto r = 0u; r < rows; ++r) {
    for (auto c = 0u; c < cols; ++c) {
      g.set_value(mean1_index, class1_value);
      g.set_value(mean2_index, class2_value);

      astar::GridIndex index {r, c};
      auto d1 = manhatten_distance(mean1_index, index);
      auto d2 = manhatten_distance(mean2_index, index);
      if (d1 < d2) {
        g.set_value(index, class1_value);
        mean1_index = calculate_mean(
            mean1_row, mean1_col, mean1_multiplier, index);
        ++mean1_multiplier;
      } else {
        g.set_value(index, class2_value);
        mean2_index = calculate_mean(
            mean2_row, mean2_col, mean2_multiplier, index);
        ++mean2_multiplier;
      }

      g.set_value(mean1_index, mean1_value);
      g.set_value(mean2_index, mean2_value);

      g.print();
      std::cout << " ** >> ** << ** " << std::endl;
      std::this_thread::sleep_for(1s);
    }
  }
  g.print();

  return 0;
}
