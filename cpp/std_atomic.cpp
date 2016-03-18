#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <string>
#include <vector>
#include <numeric>

std::mutex mutex_print;

struct MyStruct
{
  double d;
  std::string s;
};

std::atomic<double> a;

void atomic_increment_and_print( )
{
  double d0 = a.load();
  double d1 = d0;
  do
  {
    d1++;
  }
  while( !a.compare_exchange_weak(d0, d1));

  std::lock_guard<std::mutex> lg(mutex_print);
  std::cout << "Atomic Mystruct value: \t" << d1 << std::endl;
}

double d;
void nonatomic_increment_and_print()
{
  d++;
  std::lock_guard<std::mutex> lg(mutex_print);
  std::cout << "Nonatomic Mystruct value: \t" << d << std::endl;
}

int main()
{
  std::vector<std::thread> thread_pool;

  std::cout << "Atomic prints" << std::endl;
  for(auto i=0; i<10; ++i)
  {
    thread_pool.push_back(std::thread(atomic_increment_and_print));
  }

  for(auto i=0; i<10; ++i)
  {
    thread_pool[i].join();
  }

  thread_pool.clear();

  std::cout << "NonAtomic prints" << std::endl;
  for(auto i=0; i<10; ++i)
  {
    thread_pool.push_back(std::thread(nonatomic_increment_and_print));
  }

  for(auto i=0; i<10; ++i)
  {
    thread_pool[i].join();
  }



  return 0;
}
