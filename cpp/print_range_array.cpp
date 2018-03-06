#include <iostream>
#include <vector>

/*
 * [1,2,3,5,10,12,15,95]
 * output: 1-3,5,10,12,15,95-100
 */

void print_range( const std::vector<int> vec )
{
  // fail check for empty list etc.
  auto lhs = vec[0];
  auto rhs = vec[0];

  for (auto i=1; i<vec.size(); ++i)
  {
    if (vec[i]-lhs == 1) // two concecutive numbers
    {
      std::cout << lhs << "-";
      rhs = vec[i];
      continue;
    }
    if (vec[i]-rhs == 1)
    {
      rhs = vec[i];
      continue;
    }
    std::cout << rhs << ", ";
    lhs = vec[i];
    rhs = vec[i];
  }
  std::cout << vec[vec.size()-1] << std::endl;
}

void print_range2( const std::vector<int> vec )
{
  auto lhs = vec.begin();
  auto rhs = vec.begin() + 1;

  bool is_open_range = false;
  while (lhs != vec.end())
  {
    if ((*rhs - *lhs) == 1) {
      if (!is_open_range) {
        std::cout << *lhs << "-";
        is_open_range = true;
      }
    } else {
      std::cout << *lhs << ", ";
      is_open_range = false;
    }
    ++lhs;
    ++rhs;
  }
  if (*rhs != 100) {
    std::cout << "100";
  }
  std::cout << std::endl;
}

int main()
{
  {
    auto vec = {1,2,3,5,10,12,15,95};
    std::cout << "expected:" << std::endl;
    std::cout << "1-3, 5, 10, 12, 15, 95" << std::endl;
    std::cout << "actual:" << std::endl;
    print_range(vec);
  }
  std::cout << std::endl;
  {
    auto vec = {1,2,3,4,5,10,12,15,98,99,100};
    std::cout << "expected:" << std::endl;
    std::cout << "1-5, 10, 12, 15, 98-100" << std::endl;
    std::cout << "actual:" << std::endl;
    print_range(vec);
  }
  std::cout << std::endl;
  {
    auto vec = {1,2,3,4,5,10,12,15,98,99,100};
    std::cout << "expected:" << std::endl;
    std::cout << "1-5, 10, 12, 15, 98-100" << std::endl;
    std::cout << "actual:" << std::endl;
    print_range2(vec);
  }
  std::cout << std::endl;
  {
    auto vec = {1,2,3,5,10,12,15,95};
    std::cout << "expected:" << std::endl;
    std::cout << "1-3, 5, 10, 12, 15, 95" << std::endl;
    std::cout << "actual:" << std::endl;
    print_range2(vec);
  }

  return 0;
}
