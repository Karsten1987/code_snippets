#include <chrono>
#include <iostream>
#include <thread>

int main()
{
  for (size_t i = 0; i < 30; ++i) {
    int * p = new int(i);
    *p = i+10;
    delete p;

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}
