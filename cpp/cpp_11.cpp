/*
 * compile with
 * g++ -std=c++0x 
 */

#include <iostream>
#include <string>

std::string&& returnRValue()
{
  return "hello world";
}

int main()
{
  std::string&& rr = returnRValue();
  std::cout << "found r-value " << rr << std::endl;

  std::string x;
  x = rr;
  //std::cout << "found r-value " << rr << std::endl;
  return 0;
}
