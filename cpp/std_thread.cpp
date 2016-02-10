#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <mutex>
#include <future>

std::mutex mutex_print;

struct Status
{
  size_t stat;
};

void printStatus( std::string prefix, const Status& status ) noexcept
{
  std::lock_guard<std::mutex> lg(mutex_print);
  auto time_point = std::chrono::high_resolution_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(time_point);
  //std::cout << std::ctime(&now_c) << " Current status value:\t" << status.stat << std::endl;
  std::cout << prefix << ":\t" << status.stat << std::endl;
}

void asyncStatusPrint( Status& status ) noexcept
{
  while (status.stat != 0)
  {
    printStatus( "In async thread", status);
    --status.stat;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

int main()
{
  Status st = {10};

  auto fut = std::async(std::launch::async, asyncStatusPrint, std::ref(st));

  while (st.stat != 0)
  {
    printStatus("In main thread", st);
    --st.stat;
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  fut.get();

  return 0;
}
