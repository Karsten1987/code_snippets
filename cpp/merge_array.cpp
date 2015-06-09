#include <iostream>
#include <vector>


void printVector( const std::vector<int> vec )
{
  for (int i=0; i<vec.size();++i)
  {
    std::cout << vec[i] << " --> ";
  }
  std::cout << "EOF" << std::endl;
}

/*
 * merge from the back
 * this resolves uncessary reshifting per step
 * [1] [3] [4] [5] [7] [10]   [] [] [] []
 *   [2]         [6]  [8] [9]
 */
void merge( std::vector<int>& a, std::vector<int>& b )
{
  int idx_a = a.size()-1;
  int idx_b = b.size()-1;

  a.resize( a.size()+b.size() ); // resize for containing both
  std::cout << "set new size for contactented array " << a.size() << std::endl;
  while (idx_a>=0 && idx_b>=0)
  {
      std::cerr << "checking " << a[idx_a] << " < " << b[idx_b] << std::endl;
    // shift to the end
    if ( a[idx_a]<b[idx_b] )
    {
      a[idx_a+idx_b+1] = b[idx_b];
      --idx_b;
    }
    else
    {
      a[idx_a+idx_b+1] = a[idx_a];
      --idx_a;
    }
  }

  // if b stil has arguments, we simply put them first
  for (int i=0;i<=idx_b;++i)
  {
    a[i] = b[i];
  }
}

int main()
{
  std::vector<int> a = {4,5,7,10};
  std::vector<int> b = {1,2,3,6,8,9};

  merge(a, b);
  printVector(a);
  return 0;
}
