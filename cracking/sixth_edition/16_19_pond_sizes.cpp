#include <iostream>
#include <vector>

class Grid
{
public:
  Grid(std::vector<int> init, int row, int col):
    grid_(std::move(init)),
    row_(row),
    col_(col)
  {
    if (row_ * col_ != grid_.size()) {
      throw std::runtime_error("dimensions don't match");
    }
  }

  int at(int row, int col)
  {
    if (row < 0 || row >= row_) {
      return -1;
    }
    if (col < 0 || col >= col_) {
      return -1;
    }

    return grid_[row * row_ + col];
  }

  int set(int row, int col, int value)
  {
    if (row < 0 || row >= row_) {
      return -1;
    }
    if (col < 0 || col >= col_) {
      return -1;
    }

    grid_[row * row_ + col] = value;
    return value;
  }

  const int & rows() { return row_; }
  const int & cols() { return col_; }

private:
  std::vector<int> grid_;
  int row_;
  int col_;
};

size_t get_pond_size(Grid & g, int row, int col)
{
  auto sum = 0lu;

  int cell_value = g.at(row, col);
  if (cell_value != 0) {
    return sum;
  }

  // current cell
  sum += 1;
  g.set(row, col, -1);

  // up
  sum += get_pond_size(g, row - 1, col);
  // up right
  sum += get_pond_size(g, row - 1, col + 1);
  // right
  sum += get_pond_size(g, row, col + 1);
  // down right
  sum += get_pond_size(g, row + 1, col + 1);
  // down
  sum += get_pond_size(g, row + 1, col);
  // down left
  sum += get_pond_size(g, row + 1, col - 1);
  // left
  sum += get_pond_size(g, row, col - 1);
  // up left
  sum += get_pond_size(g, row - 1, col - 1);

  return sum;
}

std::vector<size_t> extract_pond_sizes(Grid & g)
{
  std::vector<size_t> ponds;
  for (int row = 0; row < g.rows(); ++row) {
    for (int col = 0; col < g.cols(); ++col) {
      auto sum = get_pond_size(g, row, col);
      if (sum > 0) {
        ponds.push_back(sum);
      }
    }
  }

  return ponds;
}

int main()
{
  std::vector<int> grid = {
    // 0, 2, 1, 0,
    // 0, 1, 0, 1,
    // 1, 1, 0, 1,
    // 0, 1, 0, 1,
    0, 1, 1, 0,
    1, 0, 0, 1,
    1, 0, 0, 1,
    0, 1, 1, 0,
  };
  Grid g(grid, 4, 4);

  auto ponds = extract_pond_sizes(g);
  std::for_each(ponds.begin(), ponds.end(), [](auto p) {
      std::cout << "pond size: " << p << std::endl;
      });

  return 0;
}
