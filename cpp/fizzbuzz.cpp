#include  <iostream>

int main()
{
  auto n = 100;
  for (auto i=0; i<n; ++i)
  {
    if (i%3 == 0)
      std::cout << "fizz";
    if (i%5 == 0)
      std::cout << "buzz";
    if (i%3 != 0 && i%5 != 0)
      std::cout << i;
    std::cout << "; ";
  }
  std::cout << std::endl;

  return 0;
}
