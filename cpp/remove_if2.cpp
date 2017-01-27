#include <iostream>
#include <vector>

#include "helper.h"

template<typename T>
void remove_if(std::vector<T> & vec, T condition_value)
{
  // position of the first cond_val
  size_t condition_index = 0;
  for (auto i=0; i<vec.size(); ++i)
  {
    if (vec[i] != condition_value)
    {
      vec[condition_index] = vec[i];
      ++condition_index;
    }
    helper::print_vector(vec);
  }
}

int main()
{
  std::vector<int> vec = {1,2,3,4,5,1,2,3,4,5};

  helper::print_vector(vec);
  remove_if(vec, 2);
  helper::print_vector(vec);
  return 0;
}
