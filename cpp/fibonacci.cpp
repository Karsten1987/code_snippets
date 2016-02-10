#include <iostream>


void fibonacci( size_t lhs, size_t rhs, size_t counter )
{
  if (counter == 0)
  {
    std::cout << std::endl;
    return;
  }
  std::cout << lhs+rhs << " ";
  return fibonacci( rhs, lhs+rhs, --counter);
}

int main()
{
  fibonacci(0, 1, 10);
  return 0;
}
