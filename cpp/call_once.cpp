#include <iostream>
#include <mutex>

  std::once_flag flag;
void f( int i )
{
  for (auto k=0; k<i; ++k)
  {
    std::cout << "Got value k: " << k << std::endl;
  }
}

void loop()
{
  for (auto k=0; k<15; ++k)
  {
    std::call_once(flag, f, 30);
    std::cout << "loop cycle" << std::endl;
  }
}

int main()
{

  loop();
  return 0;
}
