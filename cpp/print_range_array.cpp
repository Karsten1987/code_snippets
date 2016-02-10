#include <iostream>
#include <vector>

/*
 * [1,2,3,5,10,12,15,95]
 * output: 1-3,5,10,12,15,95-100
 */

void printRange( const std::vector<int> vec )
{
  size_t lhs, rhs;

  lhs = vec[0];
  rhs = vec[0];
  for (size_t i=1; i<vec.size(); ++i)
  {
    if (vec[i]-rhs == 1) // is in range
    {
      rhs = vec[i];
    }
    else
    {
      if (lhs == rhs)
      {
        std::cout << lhs << ",";
      }
      else
      {
        std::cout << lhs << "-" << rhs << ",";
      }
      lhs = vec[i];
      rhs = vec[i];
    }
  }
  if (lhs != 100)
  {
    std::cout << lhs << "-" << 100 << std::endl;
  }
  else
  {
    std::cout << lhs << std::endl;
  }




}

int main()
{
  auto vec = {1,2,3,5,10,12,15,95};
  printRange(vec);
  vec = {1,2,3,4,5,10,12,15,98,99,100};
  printRange(vec);
  return 0;
}
