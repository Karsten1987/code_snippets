#include <iostream>
#include <vector>

template<class T, typename std::enable_if<std::is_arithmetic<T>::value, T>::type * = nullptr>
class Matrix
{
public:
  Matrix(size_t row, size_t col, std::vector<T> data)
    : Matrix(row, col)
  {
    if (row * col != data.size()) {
      throw std::runtime_error("matrix dimensions don't match up");
    }
    data_ = std::move(data);
  }

  ~Matrix() = default;

  void print() const
  {
    for (auto row = 0lu; row < row_; ++row) {
      for (auto col = 0lu; col < col_ - 1; ++col) {
        std::cout << "[" << data_[row * col_ + col] << "] ";
      }
      std::cout << "[" << data_[row * col_ + col_ - 1] << "]" << std::endl;
    }
  }

  size_t rows() const
  {
    return row_;
  }

  size_t cols() const
  {
    return col_;
  }

  T at(size_t row, size_t col) const
  {
    return data_[row * col_ + col];
  }

  Matrix<T> operator*(const Matrix<T> & other)
  {
    if (cols() != other.rows()) {
      throw std::runtime_error("matrix dimensions don't match vector dimensions");
    }

    std::vector<T> matrix_data;
    matrix_data.reserve(rows() * other.cols());

    for (size_t m_row = 0lu; m_row < rows(); ++m_row) {
      for (size_t other_col = 0lu; other_col < other.cols(); ++other_col) {
        T sum = 0;
        for (size_t other_row = 0lu; other_row < other.rows(); ++other_row) {
          sum += (at(m_row, other_row) * other.at(other_row, other_col));
        }
        matrix_data.push_back(sum);
      }
    }
    Matrix<T> m(rows(), other.cols(), matrix_data);

    return m;
  }

protected:
    Matrix(size_t row, size_t col)
    : row_(row), col_(col)
  {}

private:
  size_t row_;
  size_t col_;
  std::vector<T> data_;
};

template<class T, typename std::enable_if<std::is_arithmetic<T>::value, T>::type * = nullptr>
class Vector : public Matrix<T>
{
public:
  Vector(size_t row, std::vector<T> data)
    : Matrix<T>(row, 1, data)
  {}

  T at(size_t row, size_t col) = delete;

  T at(size_t row) const {
    return Matrix<T>::at(row, 0);
  }
};

int main()
{
  std::cout << "matrix data" << std::endl;
  std::vector<double> matrix_data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Matrix<double> m(3, 3, matrix_data);
  m.print();

  std::cout << "vector data" << std::endl;
  std::vector<double> vector_data = {1, 2, 3};
  Vector<double> v(3, vector_data);
  v.print();

  std::cout << "matrix * vector data" << std::endl;
  auto mv = m * v;
  mv.print();

  std::cout << "matrix 2 data" << std::endl;
  std::vector<double> matrix2_data = {1, 1, 2, 2, 3, 3};
  Matrix<double> m2(3, 2, matrix2_data);
  m2.print();

  std::cout << "matrix * matrix 2 data" << std::endl;
  auto mm2 = m * m2;
  mm2.print();

  return 0;
}
