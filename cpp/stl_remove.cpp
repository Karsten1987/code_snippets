#include <iostream>
#include <vector>

#include "helper.h"

/**
 * the idea here is to shift all elements which are not the element to filter out
 * to the last position of the filter-element. When we replace this element we increment
 * the pivot element. We can do this beacuse we either swap two neighbour values or the
 * neighbour value is as well a filtered element.
 * example:
 * [ x 1 1 ] --> [ 1 x ]
 * [ x x 1 ] --> [ 1 x x ]
 **/

template<class T>
typename std::vector<T>::iterator remove( std::vector<T>& vec, const T& value )
{
  auto pivot = vec.begin();
  for (auto it=vec.begin(); it!=vec.end(); ++it)
  {
    if (*it != value)
    {
      *pivot = *it;
      ++pivot;
    }
  }
  return pivot;
}

typename std::string::iterator remove( std::string& s, const char c )
{
  auto pivot = s.begin();
  for (auto it=s.begin(); it!=s.end(); ++it)
  {
    if (*it != c)
    {
      *pivot = *it;
      ++pivot;
    }
  }
  return pivot;
}

int main()
{
  std::vector<int> vec = {1,2,3,4,2,3,1,3,1,2,3,4,2,1,3,4,2,5,1,2,3,4,5,1,1,1,1,3,4,3,2,3,2,3,2,3,3,2,5,2};
  helper::print_vector(vec);
  auto end = remove(vec, 1);

  helper::print_vector(vec);

  std::string s = "Hello World";
  auto s_end = remove(s, 'l');
  helper::print_vector(s);
  return 0;
};
