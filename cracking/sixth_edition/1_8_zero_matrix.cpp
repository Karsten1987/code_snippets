#include <vector>

using MatrixT = std::vector<std::vector<size_t>>;

void print_matrix(const MatrixT & matrix)
{
  for (auto row = 0ul; row < matrix.size(); ++row) {
    for (auto col = 0ul; col < matrix.size(); ++col) {
      printf("[%zu] ", matrix[row][col]);
    }
    printf("\n");
  }
}

MatrixT & zero_matrix(MatrixT & matrix)
{
  if (matrix.size() == 0) {
    return matrix;
  }
  if (matrix[0].size() == 0) {
    return matrix;
  }

  std::vector<size_t> empty_rows;
  empty_rows.reserve(matrix.size());
  std::vector<size_t> empty_cols;
  empty_cols.reserve(matrix[0].size());

  for (auto row = 0u; row < matrix.size(); ++row) {
    for (auto col = 0u; col < matrix[0].size(); ++col) {
      if (matrix[row][col] == 0) {
        empty_rows.push_back(row);
        empty_cols.push_back(col);
      }
    }
  }

  for (auto row : empty_rows) {
    for (auto col = 0u; col < matrix[row].size(); ++col) {
      matrix[row][col] = 0;
    }
  }

  for (auto col : empty_cols) {
    for (auto row = 0u; row < matrix.size(); ++row) {
      matrix[row][col] = 0;
    }
  }

  return matrix;
}

int main()
{
  MatrixT image(5, std::vector<size_t>(5, 0ul));
  image[0][0] = 1;
  image[0][1] = 2;
  image[0][2] = 3;
  image[0][3] = 4;
  image[0][4] = 5;
  image[1][0] = 6;
  image[2][0] = 11;
  image[3][0] = 16;
  image[4][0] = 21;
  print_matrix(image);
  zero_matrix(image);
  print_matrix(image);
  return 0;
}
