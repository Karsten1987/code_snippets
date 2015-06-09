#include <iostream>
#include <vector>

template<typename T>
int binarySearch( const std::vector<T>& vec, const T& key, int lhs, int rhs )
{
  if (lhs == rhs)
  {
    return -1;
  }

  int mid_idx = lhs + (rhs-lhs)/2;

  if (vec[mid_idx] == key)
  {
    return mid_idx;
  }

  if (key < vec[mid_idx])
  {
    return binarySearch( vec, key, lhs, mid_idx );
  }
  return binarySearch( vec, key, mid_idx+1, rhs );
}

template<typename T>
int binarySearch( const std::vector<T>& vec, const T& key )
{
  return binarySearch( vec, key, 0, vec.size()-1);
}


template<typename T>
int getRotationIndex( const std::vector<T>& vec, int lhs, int rhs )
{
  if (lhs == rhs)
  {
    return -1;
  }

  int mid_idx = lhs + (rhs-lhs)/2;
  if (vec[mid_idx] > vec[mid_idx+1])
  {
    return mid_idx+1;
  }
  if (vec[mid_idx] > vec[rhs]) // break is in the right part
  {
    return getRotationIndex( vec, mid_idx, rhs );
  }
  if (vec[mid_idx] < vec[lhs]) // break is in the left part
  {
    return getRotationIndex( vec, lhs, mid_idx-1 );
  }
}

template<typename T>
int binarySearchRotated( const std::vector<T>& vec, const T& key, int rot)
{
  if (vec[rot] == key)
  {
    return rot;
  }

  if (vec[rot] < rot)
  {
    return binarySearch( vec, key, 0, rot);
  }
  else
  {
    return binarySearch( vec, key, rot, vec.size());
  }
}

template<typename T>
int getRotationIndex( const std::vector<T>& vec )
{
  return getRotationIndex( vec, 0, vec.size()-1);
  for (int i=1;i<vec.size();++i)
  {
    if (vec[i] < vec[i-1])
    {
      return i;
    }
  }
  return -1;
}

int main()
{
  std::vector<int> input = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  int rot_idx = getRotationIndex( input );
  std::cerr << "rotation index (-1):" << rot_idx << std::endl;
  int idx = binarySearch( input, 13 );
  std::cerr << "13 is found at pos : " << idx << std::endl;

  std::vector<int> rot_input = { 4, 4, 4, 4, 5, 5, 6, 6, 1, 2, 3, 3, 3, 4 };
  rot_idx = getRotationIndex( rot_input );
  std::cerr << "rotation index (8):" << rot_idx << std::endl;
  idx = binarySearchRotated( rot_input, 6, rot_idx );
  std::cerr << "1 is found at pos (6): " << idx << std::endl;

  return 0;
}
