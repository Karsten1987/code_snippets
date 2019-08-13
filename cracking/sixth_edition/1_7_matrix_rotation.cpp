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

MatrixT rotate_matrix(const MatrixT & matrix)
{
  MatrixT rot_matrix(matrix.size(), std::vector<size_t>(matrix.size(), 0ul));

  float m_x = (matrix.size() - 1) / 2.0f;
  float m_y = m_x;  // squared matrix

  printf("mx and my: %f, %f\n", m_x, m_y);

  auto row = 3;
  auto col = 3;
  auto x = row - m_x;
  auto y = col - m_y;
  printf("new index for 0 0 = %f, %f\n", y, -x);

  for (auto row = 0u; row < matrix.size(); ++row) {
    for (auto col = 0u; col < matrix.size(); ++col) {
      auto x = row - m_x;
      auto y = col - m_y;
      rot_matrix[y + m_x][-x + m_y] = matrix[row][col];
    }
  }
  return rot_matrix;
}

int main()
{
  MatrixT image(5, std::vector<size_t>(5, 0ul));
  image[0][0] = 1;
  image[0][4] = 5;
  image[0][1] = 2;
  image[4][0] = 20;
  image[4][4] = 25;
  print_matrix(image);
  MatrixT rot_image = rotate_matrix(image);
  print_matrix(rot_image);
  return 0;
}
