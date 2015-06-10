#include <iostream>
#include <bitset>

#include <cmath>

void print( int i )
{
  std::cout << i << "\t -->  " << std::bitset<32>(i) << std::endl;
}

void inverseBitset( )
{
  std::cout << "inverseBItset" << std::endl;
  int i = 1232;
  print( i );
  print( -1-i );
}

void shiftingNumbers()
{
  // k << n
  // 2^n*k
  std::cout << "shifting numbers " << std::endl;
  print( 1<<2 );
  int i = 4;
  print( i<<2 );
}

void printRecursively( unsigned i, int bits )
{
  if (bits == 0)
  {
    if (i == 1)
    {
      std::cout << "1" << std::endl;
      return;
    }
    else
    {
      std::cout << "0" << std::endl;
      return;
    }
  }
  unsigned lsb = std::pow(2,bits);
  if( i < lsb )
  {
    std::cout << "0";
    printRecursively( i, bits-1 );
  }
  else
  {
    unsigned diff = i-lsb;
    std::cout << "1";
    printRecursively( diff, bits-1 );
  }
}

int countBits( int a )
{
  int res = 0;
  for (int i=0;i<32;++i)
  {
    if ( (a & (1<<i)) != 0 )
    {
      ++res;
    }
  }
  return res;
}

void compareAndPrint( int a, int b )
{
  std::cout << "compare and print" << std::endl;
  print( a );
  print( b );
  print( a^b );
}

int main()
{
  print( 78 );
  printRecursively( 78, 31 );
  int lhs = 7;
  int rhs = 3;

  int a = 12321;
  int b = 454;
  int max = 0;
  int mask = (1 << rhs-1);
  for (int i=rhs;i<lhs;++i)
  {
    mask = mask |= (1 << i);
  }
  print( a );
  print( b );
  print( (a & (-1-mask)) | b);

  inverseBitset();
  shiftingNumbers();
  compareAndPrint( 78, 31 );

  std::cout << "comparison " << (4 & (1<<3)) << std::endl;
  int k = 78;
  std::cout << "active bits in  "<< k << " " << countBits(k) << std::endl;
}
