#include <iostream>

int main()
{

  int i = 0;
  std::cerr << "init :" << i << std::endl;

  i = 0;
  std::cerr << "before :" << ++i << std::endl;

  i = 0;
  std::cerr << "after :" << i++ << std::endl;

  i = i++;
  std::cerr << "assigning it :" << i << std::endl;

  i = 0;
  i = ++i;
  std::cerr << "assigning it again : " << i << std::endl;

  return 0;
}
