#include <cmath>
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

  void print() const
  {
    for (int row = 0; row < row_; ++row) {
      for (int col = 0; col < col_; ++col) {
        std::cout << grid_[row * row_ + col] << " ";
      }
      std::cout << std::endl;
    }
  }

  const int & rows() { return row_; }
  const int & cols() { return col_; }

private:
  std::vector<int> grid_;
  int row_;
  int col_;
};

Grid generate_grid(size_t k)
{
  std::vector<int> init(k * k, 1);
  for (size_t row = 0; row < k; ++row)
  {
    bool toggle = row % 2 == 0 ? true : false;
    for (size_t col = 0; col < k; ++col) {
      if (toggle) {
        init[row * k + col] = 0;
        toggle = false;
      } else {
        toggle = true;
      }
    }
  }
  return Grid(init, k, k);
}

class Ant
{
public:
  Ant(int col, int row, double orientation)
  : col_(col), row_(row), orientation_(orientation)
  {}

  void move(int steps = 1)
  {
    row_ += steps * cos(orientation_);
    col_ += steps * sin(orientation_);
  }

  void turn_left(int steps = 1)
  {
    orientation_ += steps * M_PI/2;
  }

  void turn_right(int steps = 1)
  {
    orientation_ -= steps * M_PI/2;
  }

  int col_;
  int row_;
  double orientation_;
};

int main()
{
  size_t k = 5;
  Grid g = generate_grid(k+1);

  Ant a(k/2, k/2, M_PI);

  for (size_t i = 0; i < k; ++i) {
    if (g.at(a.row_, a.col_) == 0) {
      g.set(a.row_, a.col_, 1);
      a.turn_right();
      a.move();
    } else {
      g.set(a.row_, a.col_, 0);
      a.turn_left();
      a.move();
    }

    std::cout << std::endl;
    g.print();

  }

  std::cout << std::endl;
  g.set(a.row_, a.col_, 2);
  g.print();

  return 0;
}
