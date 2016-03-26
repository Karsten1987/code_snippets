#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

namespace helper
{

template<class T>
inline void print_vector( const std::vector<T>& vec, std::string prefix = "" )
{
  std::cout << prefix << "[ ";
  std::for_each(vec.begin(), vec.end(), [&](const T& v) { std::cout << v << " "; });
  std::cout << "]" << std::endl;
}

inline void print_vector( const std::string& vec, std::string prefix = "" )
{
  std::cout << prefix << "[ ";
  std::for_each(vec.begin(), vec.end(), [&](const char& c) { std::cout << c << " "; });
  std::cout << "]" << std::endl;
}

template<class T>
inline void print_vector( typename std::vector<T>::const_iterator first, typename std::vector<T>::const_iterator last, std::string prefix = "" )
{
  std::cout << prefix << "[ ";
  for (; first != last; ++first)
  {
    std::cout << *first << " ";
  }
  std::cout << "]" << std::endl;
}

}// helper
