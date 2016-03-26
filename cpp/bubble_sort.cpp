#include <iostream>
#include <vector>

#include "helper.h"

template<class T>
void sort( std::vector<T>& vec )
{
  for (size_t i=0; i<vec.size(); ++i)
  {
    for (size_t j=0; j<vec.size(); ++j)
    {
      if (vec[i] < vec[j])
      {
        T tmp = vec[i];
        vec[i] = vec[j];
        vec[j] = tmp;
      }
    }
  }
}

int main()
{
  std::vector<int> vec = {1,2,35,1,3,6,876,3,6,3,6,4,2,5,7,7,4,2,2,7,8,8,4,57,52,2,45,754342,8,76,54,3};
  sort(vec);
  helper::print_vector(vec);
  return 0;
}
