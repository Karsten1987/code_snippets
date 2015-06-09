#include <iostream>

#include <vector>
#include <string>

/*
 * merge sort
 */
void printVector( std::vector<int>& vec )
{
  for (size_t i=0;i<vec.size();++i)
  {
    std::cerr << vec[i] << " --> ";
  }
  std::cerr << std::endl;
}

std::vector<int> merge( std::vector<int>& vec, std::vector<int>& lhs, std::vector<int>& rhs )
{
  // lhs 1, 3, 5, 6, 7
  // rhs 2, 3, 4, 5
  // 1,2,3,3,4,5,5,6,7

  std::vector<int> result;
  int lhs_idx=0;
  int rhs_idx = 0;

  /*
   * merge until one of the vectors is empty
   * merge: element lhs vs element rhs
   *        add the smallest to result
   *        increase their respective index
   */
  while (lhs_idx < lhs.size() && rhs_idx < rhs.size())
  {
    if (lhs[lhs_idx] <= rhs[rhs_idx])
    {
      result.push_back( lhs[lhs_idx] );
      lhs_idx++;
    }
    else
    {
      result.push_back( rhs[rhs_idx] );
      rhs_idx++;
    }
  }

  for (int i=lhs_idx;i<lhs.size();++i)
  {
    result.push_back( lhs[i] );
  }
  for (int i=rhs_idx;i<rhs.size();++i)
  {
    result.push_back( rhs[i] );
  }

  vec = result;
  return vec;
}

std::vector<int> mergeSort( std::vector<int>& vec )
{
  if (vec.size()==1)
  {
    return vec;
  }

  int mid_idx = vec.size()/2;
  std::vector<int> lhs(vec.begin(), vec.begin()+mid_idx);
  std::vector<int> rhs(vec.begin()+mid_idx, vec.end());
  mergeSort( lhs );
  mergeSort( rhs );

  return merge( vec, lhs, rhs );
}

// [1,3,3,3,5,6,6,7]  --> 2
int findInsertIndex( const std::vector<int>& vec, const int value, int lhs, int rhs )
{
  if (vec.size() == 0)
  {
    return -1;
  }

  if (lhs==rhs)
  {
    std::cout << "LEFT HAND SIDE EQUALS TO RIGHT HAND SIDE" << std::endl;
    return lhs+1;
  }

  int middle_idx = lhs + (rhs-lhs)/2;
  std::cout << "middle idx " << middle_idx << std::endl;
  if (vec[middle_idx]==value)
  {
    return middle_idx+1;
  }

  if ( value < vec[middle_idx] )
  {
    return findInsertIndex( vec, value, lhs, middle_idx-1 );
  }
  else
  {
    return findInsertIndex( vec, value, middle_idx+1, rhs );
  }
}

int findRotationIndex( const std::vector<int> vec, int lhs, int rhs )
{
  if (vec.size()<=1)
  {
    return -1;
  }

  if (lhs == rhs)
  {
    return -1;
  }

  int middle_idx = lhs + (rhs-lhs)/2;
  if (vec[middle_idx] > vec[middle_idx+1])
  {
    return middle_idx+1;
  }
  if (vec[middle_idx] > vec[rhs]) // sign changed
  {
    return findRotationIndex( vec, middle_idx, rhs );
  }
  else
  {
    return findRotationIndex( vec, lhs, middle_idx );
  }
}

int main()
{
  std::vector<int> vec_i = {1,2,3,4,5};
  vec_i = mergeSort( vec_i );

  int idx = findInsertIndex( vec_i, 3, 0, vec_i.size()-1 );
  std::cout << "find insertion (3) " << idx << std::endl;
  printVector( vec_i );

  std::vector<int> vec_rot = {4,5,1,2,3};
  printVector( vec_rot );
  int rot_idx = findRotationIndex( vec_rot, 0, vec_rot.size()-1);
  std::cout << "find rotation index (2) " << rot_idx << std::endl;
  rot_idx = findRotationIndex( vec_i, 0, vec_i.size()-1);
  std::cout << "find rotation index (-1) " << rot_idx << std::endl;
  return 0;
}
