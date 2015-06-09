#include <iostream>
#include <vector>
#include <string>

int binarySearch( const std::vector<int>& input, const int key, int lhs, int rhs )
{
  if (input.empty())
  {
    return -1;
  }

  if (lhs == rhs)
  {
    if (input[lhs] == key)
    {
      return lhs;
    }
    else // not found
    {
      return -1;
    }
  }

  int middle_idx = lhs + (rhs-lhs)/2;
  if (key <= input[middle_idx])
  {
    return binarySearch(input, key, lhs, middle_idx);
  }
  else
  {
    return binarySearch(input, key, middle_idx+1, rhs);
  }
}

int findRotationIndex( const std::vector<int>& input, int lhs, int rhs )
{
  if (input.size()<=1)
  {
    return -1;
  }

  if ( lhs == rhs )
  {
    return -1;
  }

  int middle_idx = lhs + (rhs-lhs)/2;
  if ( input[middle_idx] > input[middle_idx+1] )
  {
    return middle_idx+1;
  }
  if ( input[middle_idx] > input[rhs] ) // break is in right half
  {
    return findRotationIndex( input, middle_idx, rhs );
  }
  if ( input[middle_idx] < input[lhs] ) // break is in left half
  {
    return findRotationIndex( input, lhs, middle_idx );
  }
}

int binarySearchRotated( const std::vector<int>& input, const int key )
{
  int rot_idx = findRotationIndex( input, 0, input.size()-1 );
  if ( input[rot_idx] == key )
  {
    return rot_idx;
  }
  if ( input[rot_idx] < key )
  {
    return binarySearch( input, key, 0, rot_idx );
  }
  else
  {
    return binarySearch( input, key, rot_idx, input.size()-1 );
  }
}

void rotate( std::vector<int>& vec, int n_rot )
{
  n_rot = n_rot%vec.size();
  std::cout << vec.size() << " actual rotations " << n_rot << std::endl;

  std::vector<int> tmp;
  tmp.reserve(vec.size());
  for (auto i=n_rot; i<n_rot+vec.size(); ++i)
  {
    tmp.push_back( vec[i%vec.size()] );
  }
  vec = tmp;
}

int findMinimum( const std::vector<int>& vec )
{
  auto rot_idx = findRotationIndex( vec, 0, vec.size()-1 );
  if (rot_idx < 0) // no rotation found
  {
    return vec[0]; // assuming sorted array
  }
  return vec[rot_idx];
}

void printVector( const std::vector<int>& vec )
{
  for (auto i=0;i<vec.size();++i)
  {
    std::cout << vec[i] << "-->";
  }
  std::cout << "NULL" << std::endl;
}

int main()
{
  std::vector<int> vec = {1,2,3,4,4,5,5,5,6,7,8};
  printVector( vec );
  auto idx = binarySearch( vec, 9, 0, vec.size()-1 );
  std::cout << "found value at " << idx << std::endl;

  std::vector<int> rot_vec = {3,4,5,6,7,8,8,8,9,1,2};
  printVector( rot_vec );
  auto rot_idx = findRotationIndex( rot_vec, 0, rot_vec.size()-1 ); // logN
  std::cout << "found rotation index at " << rot_idx << std::endl;
  int idx2 = binarySearchRotated( rot_vec, 9 );
  std::cout << "found value at " << idx2 << std::endl;

  std::vector<int> single_vec = {1,2,3,4,5,6,7,8,9,10};
  rotate( single_vec, 13 );
  printVector( single_vec );
  std::cout << "found minimum " << findMinimum( single_vec ) << std::endl;
  return 0;
}
