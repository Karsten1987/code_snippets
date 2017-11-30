#include <atomic>
#include <chrono>
#include <cstdio>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

size_t thread_count = 10;
int tops = 40;
std::atomic<int> i(0);

int
main(int argc, char ** argv)
{

  auto inc = [&] {
      while (++i < tops + 10) {
        int tmp_i = i;
        fprintf(stderr, "therad %p has set i to %d\n", std::this_thread::get_id(), tmp_i);
        std::this_thread::sleep_for(1s);
      }
    };

  std::vector<std::thread> thread_pool;
  for (auto t = 0u; t < thread_count; ++t)
  {
    thread_pool.push_back(std::thread(inc));
  }

  int desired = tops+1;
  int expected = tops;
  while (!i.compare_exchange_weak(expected, desired)) {
    printf("current value of ex is: %d\n", expected);
    printf("current value of i is: %d\n", i.load());
    std::this_thread::sleep_for(500ms);
    expected = tops;
  }

  for (auto t = 0u; t < thread_count; ++t)
  {
    thread_pool[t].join();
  }

  return 0;
}
