#include <iostream>
#include <string>
#include <bitset>
#include <limits>

void removeDuplicates(std::string& str)
{
  long long map = 0ULL;
  for (int i = 0; i < str.size(); i++) {
    int shift = (str[i] - '0');
    std::cout << str[i] << " gonna shift about " << shift << std::endl;
    if ((map & (1ULL << shift)) > 0) // duplicate detected
      str[i] = 0;
    else // add unique char as a bit '1' to the map
      map |= 1ULL << shift;
  }
  std::cout << std::bitset<64>(map) << std::endl;
}

void printBits( int i )
{
  std::cout << std::bitset<32>(i) << std::endl;
}

void printBits( long long ll )
{
  std::cout << std::bitset<64>(ll) << std::endl;
}
int main()
{
  printBits( std::numeric_limits<int>::max() );
  printBits( 0 );
  printBits( -1);
  printBits( std::numeric_limits<int>::min() );
  printBits( std::numeric_limits<long long>::max() );

  int a = static_cast<int>('a');
  int A = static_cast<int>('A');
  std::cout << "a " << a << ":: A " << A << std::endl;
  std::cout << 'k'-'a' << std::endl;
  std::cout << 'K'-'A' << std::endl;
  std::string s = "113411aaaaaabbbbbbccccccKarstenK4";
  std::cerr << "remove duplicates from " << s << " == ";
  removeDuplicates(s);
  std::cerr << s << std::endl;

  long long bitfield = 0ULL;
  bitfield |= 1ULL<<62;
  std::cout << "bitfield" << std::endl;
  std::cout << std::bitset<64>(bitfield) << std::endl;

  std::string to_delete = "abcdkefgh";
  for (size_t i=0; i<to_delete.size(); ++i)
  {
    if (to_delete[i] == 'k')
    {
      to_delete[i] = 0;
    }
  }
  std::cout << "string without a k " << to_delete << std::endl;
  return 0;
}
