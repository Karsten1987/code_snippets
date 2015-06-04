#include <iostream>
#include <tuple>

int main()
{
  std::pair<int, int> int_pair = std::make_pair<int, int>(123, 456);
  std::cout << "pair elements first " << int_pair.first << " and " << int_pair.second << std::endl;
}
