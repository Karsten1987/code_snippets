#include <iostream>
#include <vector>

#include "helper.h"

template<class T>
std::vector<T> merge( const std::vector<T>& lhs, const std::vector<T>& rhs )
{
  if (lhs.size() == 0)
  {
    return rhs;
  }
  if (rhs.size() == 0)
  {
    return lhs;
  }

  std::vector<T> result;
  result.reserve(lhs.size()+rhs.size());

  size_t left_idx=0;
  size_t right_idx=0;
  while (left_idx < lhs.size() && right_idx < rhs.size())
  {
    if (lhs[left_idx] < rhs[right_idx])
    {
      result.push_back(lhs[left_idx]);
      left_idx++;
    }
    else
    {
      result.push_back(rhs[right_idx]);
      right_idx++;
    }
  }
  for (auto l=left_idx; l<lhs.size(); ++l)
  {
    result.push_back(lhs[l]);
  }
  for (auto r=right_idx; r<rhs.size(); ++r)
  {
    result.push_back(rhs[r]);
  }

  return result;
}

template<class T>
std::vector<T> sort( const std::vector<T>& vec )
{
  if (vec.size() <= 1)
  {
    return vec;
  }

  auto pivot = vec.size()/2;
  auto lhs = sort( std::vector<T>(vec.begin(), vec.begin()+pivot) );
  auto rhs = sort( std::vector<T>(vec.begin()+pivot, vec.end() ) );
  auto merged = merge(lhs, rhs);
  return merged;
}

int main()
{
  std::vector<int> vec = {3,2,6,6,1,4,6,7,1,2,3,3,5,45,676,87,8,56,6,7,8,6,453,2,2,3,1,1,7,89,9,0};
  std::vector<int> sorted = sort(vec);
  helper::print_vector(sorted);

  std::vector<int> lhs = {3,1,3,4,1};
  std::vector<int> rhs = {2,5,2,1,3};
  std::vector<int> vec_merge = merge(lhs, rhs);

  helper::print_vector(lhs, "lhs");
  helper::print_vector(rhs, "rhs");
  helper::print_vector(vec_merge);
  return 0;
}
