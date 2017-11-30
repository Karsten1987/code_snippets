#include <iostream>
#include <thread>
#include <atomic>
#include <array>
#include <vector>
#include <chrono>
#include <unordered_map>

using namespace std::chrono_literals;

struct GlobalCounter
{
  std::array<std::atomic<unsigned int>, 10> counter_array;
  std::unordered_map<std::thread::id, std::atomic<unsigned int>> counter_map;
  static thread_local unsigned int local_counter;
};

thread_local unsigned int GlobalCounter::local_counter = 0;

static GlobalCounter instance;

thread_local unsigned int local_counter = 0;

int main()
{
  std::vector<std::thread> thread_pool;
  for (auto i = 0u; i < 10; ++i) {
    thread_pool.push_back(std::thread([i] {
      for (auto k = 0u; k < 10; ++k) {
          instance.counter_array[i].fetch_add(1);
          std::this_thread::sleep_for(1s);
      }
    }));
  }

  for (auto & thread : thread_pool) {
    thread.join();
  }

  for (std::atomic<unsigned int> & counter : instance.counter_array) {
    std::cout << "counter value " << counter << std::endl;
  }

  thread_pool.clear();

  for (auto i = 0u; i < 10; ++i) {
    thread_pool.push_back(std::thread([i] {
      instance.counter_map[std::this_thread::get_id()] = 0;
      for (auto k = 0u; k < 10; ++k) {
          instance.counter_map[std::this_thread::get_id()].fetch_add(1);
          std::this_thread::sleep_for(1s);
      }
    }));
  }

  for (auto & thread : thread_pool) {
    thread.join();
  }

  for (auto & map_entry : instance.counter_map) {
    std::cout << "map value " << map_entry.second << std::endl;
  }

  thread_pool.clear();

  for (auto i = 0u; i < 10; ++i) {
    thread_pool.push_back(std::thread([] {
          instance.local_counter = 0;
      for (auto k = 0u; k < 10; ++k) {
          local_counter++;
          instance.local_counter++;
          std::this_thread::sleep_for(1s);
      }
      printf("leavin thread with local counter of %u\n", local_counter);
      printf("leavin thread with instance counter of %u\n", instance.local_counter);
    }));
  }

  for (auto & thread : thread_pool) {
    thread.join();
  }

  for (auto & map_entry : instance.counter_map) {
    std::cout << "local value " << local_counter << std::endl;
    std::cout << "instance value " << instance.local_counter << std::endl;
  }
  return 0;
}

