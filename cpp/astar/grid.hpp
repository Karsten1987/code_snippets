#pragma once

#include <vector>
#include <iostream>
#include <type_traits>
#include <cstdint>
#include <utility>

namespace astar
{

struct GridIndex
{
  size_t row;
  size_t col;

  bool operator==(const GridIndex & rhs)
  {
    return row == rhs.row && col == rhs.col;
  }

  bool operator!=(const GridIndex & rhs)
  {
    return !(*this == rhs);
  }
};

template<typename ValueType>
struct GridValue
{
  ValueType value;
  std::string print_value;
  using type = ValueType;

  bool operator==(const GridValue<ValueType> & rhs)
  {
    return value == rhs.value;
  }
  bool operator!=(const GridValue<ValueType> & rhs)
  {
    return !(*this == rhs);
  }
};

template<typename T>
class Grid
{
public:
  Grid(size_t rows, size_t cols):
    grid_(rows * cols, GridValue<T>()),
    rows_(std::move(rows)),
    cols_(std::move(cols))
  {};

  virtual ~Grid() = default;

  size_t
  num_rows()
  {
    return rows_;
  }

  size_t
  num_cols()
  {
    return cols_;
  }

  bool
  valid_index(const GridIndex & index) const
  {
    return index.row < rows_ && index.col < cols_;
  }

  void
  set_value(const GridIndex & index, const GridValue<T> & value)
  {
    grid_[to_index(index.row, index.col)] = value;
  }

  const GridValue<T> &
  get_value(const GridIndex & index) const
  {
    return grid_[to_index(index.row, index.col)];
  }

  virtual void
  print() const
  {
    for (auto row = 0; row < rows_; ++row)
    {
      std::cout << "|";
      for (auto col = 0; col < cols_; ++col)
      {
        auto & val = grid_[to_index(row, col)];
        std::cout << val.print_value;
      }
      std::cout << std::endl;
    }
  }


protected:
  size_t to_index(size_t row, size_t col) const
  {
    return row * cols_ + col;
  }

  std::vector<GridValue<T>> grid_;
  size_t rows_;
  size_t cols_;
};

class Map : public Grid<std::uint8_t>
{
public:
  Map(size_t row, size_t col):
    Grid(row, col)
  {
    std::fill(grid_.begin(), grid_.end(), free_value);
  };

  virtual ~Map() = default;

  void
  set_start(GridIndex start)
  {
    set_value(start, start_value);
    start_index_ = start;
  }

  void
  set_goal(GridIndex goal)
  {
    set_value(goal, goal_value);
    goal_index_ = goal;
  }

  void
  set_obstacle(const GridIndex & obstacle)
  {
    set_value(obstacle, obstacle_value);
  }

  void
  set_visited(const GridIndex & index)
  {
    set_value(index, visited_value);
  }

  GridIndex
  get_start_index() const
  {
    return start_index_;
  }

  GridIndex
  get_goal_index() const
  {
    return goal_index_;
  }

  std::vector<GridIndex>
  get_valid_neighbours(const GridIndex & index) const
  {
    std::vector<GridIndex> neighbours;
    neighbours.reserve(4);

    //check upwards
    GridIndex index_up {index.row + 1, index.col};
    GridIndex index_right {index.row, index.col + 1};
    GridIndex index_down {index.row - 1, index.col};
    GridIndex index_left {index.row, index.col -1};

    for (auto index : {index_up, index_right, index_down, index_left}) {
      if (valid_index(index)) {
        auto val = get_value(index);
        if (val != obstacle_value && val != visited_value) {
          neighbours.emplace_back(index);
        }
      }
    }

    return neighbours;
  }

private:
  const GridValue<std::uint8_t> free_value      = {0, "\033[1;2;40m 1 \033[0m|"};
  const GridValue<std::uint8_t> start_value     = {1, "\033[1;1;52;31m S \033[0m|"};
  const GridValue<std::uint8_t> goal_value      = {2, "\033[1;1;32m G \033[0m|"};
  const GridValue<std::uint8_t> obstacle_value  = {3, "\033[2;37;40m   \033[0m|"};
  const GridValue<std::uint8_t> visited_value   = {4, "\033[1;38m x \033[0m|"};

  GridIndex start_index_;
  GridIndex goal_index_;
};

}  // namespace astar
