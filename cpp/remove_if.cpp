#include <iostream>
#include <vector>
#include <algorithm>

template<class T>
void print_vector( const std::vector<T>& vec )
{
  std::cout << "[ " ;
  std::for_each(vec.begin(), vec.end(), [&](const T& t) {
      std::cout << t << " ";
      });
  std::cout << "]" << std::endl;
}

template<class T>
void delete_value( std::vector<T>& vec, const T& value )
{
  int value_idx = 0;
  for (auto i=0; i<vec.size(); ++i)
  {
    if (vec[i] == value)
    {
      value_idx = i;
      break;
    }
  }

  for (auto i=value_idx; i<vec.size()-1; ++i)
  {
    if (vec[i+1] != value)
    {
      vec[value_idx] = vec[i+1];
      ++value_idx;
    }
  }
}

template<class T>
typename std::vector<T>::iterator my_remove( std::vector<T>& vec, const T& value )
{
  auto first = vec.begin();
  auto last = vec.end();
  //auto pivot = ++first;
  auto pivot = first;
  for (auto it=first; it!=last; ++it)
  {
    if (*it != value)
    {
      *pivot = *it;
      pivot++;
    }
  }
  for (auto p=pivot; p!=last; ++p)
  {
    *p = value;
  }
  return pivot;
}

int main()
{
  const std::vector<int> vec_origin = {1,2,3,4,1,5,3,4,5,1,3,4,5,6,1};
  std::cout << "original vector" << std::endl;
  print_vector(vec_origin);

  auto vec_my_remove = vec_origin;
  my_remove(vec_my_remove, 1);
  std::cout << "after my remove " << std::endl;
  print_vector(vec_my_remove);

  std::vector<int> vec_std_remove = vec_origin;
  std::remove(vec_std_remove.begin(), vec_std_remove.end(), 1);
  std::cout << "after std remove " << std::endl;
  print_vector(vec_std_remove);

  std::vector<int> vec_my_delete = vec_origin;
  delete_value(vec_my_delete, 1);
  std::cout << "after my delete " << std::endl;
  print_vector(vec_my_delete);
  return 0;
}
