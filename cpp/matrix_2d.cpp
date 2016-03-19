#include <iostream>
#include <stdexcept>
#include <array>
#include <vector>

template<class T, int Row=3, int Col=3>
class Matrix2D
{
private:
  std::vector<T> data_;
  size_t row_, col_;

public:
  Matrix2D():
    data_(Row*Col, T()),
    row_(Row),
    col_(Col)
  {}

  Matrix2D( size_t row, size_t col ):
    data_(row*col, T()),
    row_(row),
    col_(col)
  {}

  void print() const
  {
    for (auto i=0; i<data_.size(); ++i)
    {
      std::cout << data_[i] << " ";
      if ((i+1)%col_ == 0)
      {
        std::cout << std::endl;
      }
    }
    std::cout << std::endl;
  }

  T& operator()( size_t row, size_t col )
  {
    return data_[toIndex(row, col)];
  }

  Matrix2D& operator+ ( const Matrix2D& rhs )
  {
    equal( rhs.row_, rhs.col_ );

    for (auto i=0; i<data_.size(); ++i)
    {
      data_[i] += rhs.data_[i];
    }
    return *this;
  }

  Matrix2D operator* ( const Matrix2D& rhs )
  {
    if (col_ != rhs.row_)
      throw std::range_error("RowCol mismatch " + std::to_string(col_) + " " + std::to_string(rhs.row_));
    if (row_ != rhs.col_)
      throw std::range_error("RowCol mismatch " + std::to_string(row_) + " " + std::to_string(rhs.col_));

    // M_np = M_nm * M_mp
    Matrix2D<T> m_copy(row_, rhs.col_);

    for (auto n=0; n<row_; ++n)
    {
      for (auto p=0; p<rhs.col_; ++p)
      {
        T sum = 0;
        for (auto m=0; m<col_; ++m)
        {
          sum += data_[toIndex(n,m)] * rhs.data_[toIndex(m,p)];
        }
        m_copy(n,p) = sum;
      }
    }
    return m_copy;
  }

  inline size_t toIndex( size_t row, size_t col )
  {
    inRange(row, col);

    return row*row_+col;
  }

  inline void inRange( size_t row, size_t col )
  {
    if (row >= row_)
      throw std::range_error("Wrong row index: " + std::to_string(row));
    if (col >= col_)
      throw std::range_error("Wrong col index: " + std::to_string(col));
  }

  inline void equal( size_t row, size_t col )
  {
    if (row != row_)
      throw std::range_error("Row mismatch: " + std::to_string(row) + " and " + std::to_string(row_));
    if (col != col_)
      throw std::range_error("Col mismatch: " + std::to_string(col) + " and " + std::to_string(col_));
  }

};

int main()
{

  Matrix2D<int> m;
  m.print();

  m(0,0) = 2;
  m(1,1) = 2;
  m(2,2) = 2;
  m.print();

  Matrix2D<int> m1;
  m1(0,0) = 3;
  m1(1,1) = 3;
  m1(2,2) = 3;
  m1.print();

  Matrix2D<int> m2 = m * m1;
  m2.print();
  return 0;
}
