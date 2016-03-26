#include <iostream>

template<int lhs, int rhs, int counter>
struct fibonacci_t
{
  static constexpr int value = fibonacci_t<rhs, lhs+rhs, counter-1>::value;
};

template<int lhs, int rhs>
struct fibonacci_t<lhs, rhs, 0>
{
  static constexpr int value = lhs+rhs;
};

int fibonacci( size_t lhs, size_t rhs, size_t counter )
{
  if (counter == 0)
  {
    return lhs+rhs;
  }
  return fibonacci( rhs, lhs+rhs, --counter);
}

int main()
{
  std::cout << "recursive function " << fibonacci(0, 1, 10) << std::endl;
  std::cout << "recursive template " << fibonacci_t<0,1,10>::value << std::endl;
  return 0;
}
