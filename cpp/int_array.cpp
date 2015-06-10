#include <iostream>
#include <vector>

/*
Q- Implement a method that split a sorted array in two parts and swap them
Example:
  input: array [5 7 10 20 22 27]
split index: 2 (i.e. split between 7 and 10)
  output: array [10 20 22 27 5 7]
*/

void printVector( const std::vector<int>& vec )
{
  for (auto i=0;i<vec.size();++i)
  {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;
}

void reverse( std::vector<int>& vec, int lhs, int rhs )
{
  while ( lhs < rhs )
  {
    int tmp = vec[lhs];
    vec[lhs] = vec[rhs];
    vec[rhs] = tmp;

    ++lhs;
    --rhs;
  }
}

void splitAndSwap( std::vector<int>& vec, int si )
{
  int k = vec.size()-si;
  reverse( vec, 0, vec.size()-1 );
  printVector( vec );
  reverse( vec, 0, k-1);
  reverse( vec, k, vec.size()-1 );
}

std::vector<int> rotate( const std::vector<int>& vec, int k )
{
  if (vec.empty())
  {
    return std::vector<int>();
  }
  if (vec.size()==1)
  {
    return vec;
  }

  std::vector<int> rot_vec;
  rot_vec.reserve( vec.size() );
  for (auto i=k;i<vec.size()+k;++i)
  {
    rot_vec.push_back( vec[i%vec.size()] );
  }
  return rot_vec;
}


int main()
{
  std::vector<int> vec = {5, 7, 10, 20, 22, 27};
  std::cout << "original vector:" << std::endl;
  printVector( vec );
  int si = 2;
  std::vector<int> rot_vec = rotate( vec, si );
  printVector( rot_vec );
  //splitAndSwap( vec, si );
  //printVector( vec );
}
