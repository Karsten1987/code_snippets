#include <iostream>
#include <future>
#include <thread>
#include <algorithm>


int do_stuff()
{
  std::cerr << "Doing stuff on thread " << std::this_thread::get_id() << std::endl;
  int i = 0;
  while (i < 5)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ++i;
  }
  return i;
}

int main() {
  int i = 0;

  std::future<int> fut = std::async(std::launch::async, do_stuff);

  std::cerr << "Doing main stuff on thread " << std::this_thread::get_id() << std::endl;
  while (fut.wait_for(std::chrono::milliseconds(1000)) != std::future_status::ready)
  {
    ++i;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  std::cout << "main thread got " << i << std::endl;
  std::cout << "do stuff returns " << fut.get() << std::endl;
  // your code goes here
  return 0;
}
