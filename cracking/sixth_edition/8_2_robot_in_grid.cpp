#include <iostream>
#include <vector>

template<class T = int>
class Grid
{
public:
  Grid(size_t row, size_t col):
    row_(std::move(row)),
    col_(std::move(col)),
    grid_(row * col, T(0))
  {}

  Grid(size_t row, size_t col, std::vector<T> vec):
    row_(std::move(row)),
    col_(std::move(col)),
    grid_(std::move(vec))
  {
    if (row_ * col_ != grid_.size()) {
      throw std::runtime_error("specified row and col don't match vec dimensions");
    }
  }

  const T & at(size_t row, size_t col) const
  {
    if (row >= row_) {
      throw std::out_of_range("row out of bounds");
    }
    if (col >= col_) {
      throw std::out_of_range("col out of bounds");
    }

    return grid_[row * col_ + col];
  }

  void set(size_t row, size_t col, T val)
  {
    if (row >= row_) {
      throw std::out_of_range("row out of bounds");
    }
    if (col >= col_) {
      throw std::out_of_range("col out of bounds");
    }

    grid_[row * col_ + col] = val;
  }

private:
  size_t row_;
  size_t col_;
  std::vector<T> grid_;
};

template<class T = int>
bool find_path(
  Grid<T> & grid,
  const std::pair<size_t, size_t> & start,
  const std::pair<size_t, size_t> & goal,
  std::vector<std::pair<size_t, size_t>> & path)
{
  if (start.first == goal.first && start.second == goal.second) {
    path.push_back(goal);
    return true;
  }

  try {
    if (grid.at(start.first, start.second) == -1) {
      return false;
    }
  } catch (const std::out_of_range &) {
    return false;
  }

  std::cout << "visiting " << start.first << " and " << start.second << std::endl;
  path.push_back(start);
  if (find_path(grid, {start.first + 1, start.second}, goal, path)) {
    return true;
  }
  if (find_path(grid, {start.first, start.second + 1}, goal, path)) {
    return true;
  }
  grid.set(start.first, start.second, -1);

  path.pop_back();
  return false;
}

int main()
{
  std::vector<int> init = {
    0,  0,  0,  0, 0,
    0,  0,  0, -1, 0,
    0, -1, -1, -1, -1,
    0,  0,  0,  0, 0 };

  Grid<int> grid(4, 5, init);
  std::vector<std::pair<size_t, size_t>> path;
  std::pair<size_t, size_t> start = {0, 0};
  std::pair<size_t, size_t> goal =  {3, 4};

  bool found_path = find_path(grid, start, goal, path);
  if (found_path) {
    std::cout << "found path" << std::endl;
    for (const auto & pair : path) {
      std::cout << "[" << pair.first << "][" << pair.second << "] -> ";
    }
    std::cout << std::endl;
  } else {
    std::cout << "no path found :(" << std::endl;
  }

  return 0;
}
