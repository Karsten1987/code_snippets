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
};

template<typename T>
class Grid
{
public:
  Grid(size_t rows, size_t cols):
    grid_(rows*cols, T()),
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

  void
  set_value(const GridIndex & index, const T & value)
  {
    grid_[to_index(index.row, index.col)] = value;
  }

  T&
  get_value(const GridIndex & index)
  {
    return grid_[to_index(index.row, index.col)];
  }

protected:
  size_t to_index(size_t row, size_t col) const
  {
    if (row >= rows_)
    {
      throw std::runtime_error(std::string("Wrong row: ") + std::to_string(row));
    }
    if (col >= cols_)
    {
      throw std::runtime_error(std::string("Wrong col: ") + std::to_string(col));
    }
    return row*cols_+col;
  }

  std::vector<T> grid_;
  size_t rows_;
  size_t cols_;
};

class Map : public Grid<std::uint8_t>
{
public:
  Map(size_t row, size_t col):
    Grid(row, col)
  {};

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
    try
    {
      if (grid_[to_index(index.row+1, index.col)] != obstacle_value
          && grid_[to_index(index.row+1, index.col)] != visited_value)
      {
        GridIndex up {index.row+1, index.col};
        neighbours.emplace_back(std::move(up));
      }
    } catch (const std::exception &) {}

    //check right
    try
    {
      if (grid_[to_index(index.row, index.col+1)] != obstacle_value
          && grid_[to_index(index.row, index.col+1)] != visited_value)
      {
        GridIndex right {index.row, index.col+1};
        neighbours.emplace_back(std::move(right));
      }
    } catch (const std::exception &) {}

    //check down
    try
    {
      if (grid_[to_index(index.row-1, index.col)] != obstacle_value
          && grid_[to_index(index.row-1, index.col)] != visited_value)
      {
        GridIndex down {index.row-1, index.col};
        neighbours.emplace_back(std::move(down));
      }
    } catch (const std::exception &) {}

    //check left
    try
    {
      if (grid_[to_index(index.row, index.col-1)] != obstacle_value
          && grid_[to_index(index.row, index.col-1)] != visited_value)
      {
        GridIndex left {index.row, index.col-1};
        neighbours.emplace_back(std::move(left));
      }
    } catch (const std::exception &) {}

    return neighbours;
  }

  virtual void
  print() const
  {
    for (auto row=0; row<rows_; ++row)
    {
      std::cout << "|";
      for (auto col=0; col<cols_; ++col)
      {
        auto & val = grid_[to_index(row, col)];
        if (val == start_value)
        {
          std::cout << "\033[1;6;52;31m S \033[0m|";
        } else if (val == goal_value)
        {
          std::cout << "\033[1;32m G \033[0m|";
        } else if (val == obstacle_value)
        {
          std::cout << "\033[2;37;40m   \033[0m|";
        } else if (val == visited_value)
        {
          std::cout << "\033[1;38m x \033[0m|";
        } else
        {
          std::cout << " " << std::to_string(grid_[to_index(row, col)]) << " |";
        }
      }
      std::cout << std::endl;
    }
  }
private:
  const std::uint8_t start_value = 1;
  const std::uint8_t goal_value = 2;
  const std::uint8_t obstacle_value = 3;
  const std::uint8_t visited_value = 4;

  GridIndex start_index_;
  GridIndex goal_index_;
};

}  // namespace astar
