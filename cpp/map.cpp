#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <tr1/unordered_map>
#include <unordered_map>

int main()
{

  std::cout << "normal map" << std::endl;
  std::map<std::string, int> m;
  m["a"] = 1;
  m["c"] = 3;
  m["b"] = 2;
  m["c"] += 1;
  for (std::map<std::string, int>::iterator it = m.begin(); it!=m.end(); ++it)
  {
    std::cerr << it->first << std::endl;
  }

  // order is not based on insert, but on update
  std::cout << "tr1  unordered map" << std::endl;
  std::tr1::unordered_map<std::string, int> um;
  um["a"] = 1;
  um["c"] = 3;
  um["b"] = 2;
  um["c"] +=1;
  um["b"] += 2;
  for (std::tr1::unordered_map<std::string, int>::iterator it = um.begin(); it!=um.end(); ++it)
  {
    std::cerr << it->first << std::endl;
  }

  // c++11
  std::cout << "c++11 unordered map" << std::endl;
  std::unordered_map<std::string, int> um_11;
  um_11["a"] = 1;
  um_11["c"] = 3;
  um_11["b"] = 2;
  um_11["c"] +=1;
  um_11["b"] += 2;
  for (std::unordered_map<std::string, int>::iterator it = um_11.begin(); it!=um_11.end(); ++it)
  {
    std::cerr << it->first << std::endl;
  }
  return 0;

}
