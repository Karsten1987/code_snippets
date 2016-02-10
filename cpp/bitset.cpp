#include <iostream>
#include <bitset>

int main()
{
  auto ll = 1ull;
  std::cout << std::bitset<sizeof(ll)*8>(ll) << std::endl;

  ll |= (decltype(ll)(1)<<63);
  std::cout << std::bitset<sizeof(ll)*8>(ll) << std::endl;

  return 0;
}
