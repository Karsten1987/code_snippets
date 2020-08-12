#include <chrono>
#include <iostream>
#include <future>
#include <thread>
#include <vector>

#include "pod.hpp"

constexpr auto verbose = false;

const auto ring_buffer_size = 5u;
const uint8_t empty = 0u;
const uint8_t full = 1u;
std::vector<std::atomic<uint8_t>> ring_buffer_map;
std::vector<std::vector<POD<verbose>>> ring_buffer;
size_t active_buffer_index;

std::vector<POD<verbose>> accumulate_data{};
// atomic because we modify the number of worker threads writing data
std::atomic<size_t> counter{0};

std::atomic<bool> running{true};
// INTRODUCE QUEUE WHICH STORES ITERATORS FOR THE DATA TO BE WRITTEN TO DISK
// DO WE NEED A LOCK HERE? HOW TO PREVENT THAT QUEUE IS TOO SLOW AND ITERATORS ARE BEING USED MULTIPLE TIMES?
// WHY DO WE NEED A SHARED POINTER? A VECTOR OF VECTORS SHOULD DO JUST FINE IF WE HAVE CONSTANT RING BUFFER

auto dt = std::chrono::milliseconds(10);
auto message_count = 1000000u;
const auto buffer_capacity = 1000u;

void write(const std::vector<POD<verbose>> & data)
{
  std::cout << "writing " << data.size() << " to storage" << std::endl;
  accumulate_data.insert(accumulate_data.end(), data.begin(), data.end());
}

void initialize_buffers()
{
  accumulate_data.reserve(message_count);

  ring_buffer.resize(ring_buffer_size);
  ring_buffer_map = std::vector<std::atomic<uint8_t>>(ring_buffer_size);
  for (auto i = 0u; i < ring_buffer_size; ++i) {
    ring_buffer[i].reserve(buffer_capacity);
    ring_buffer_map[i] = empty;
  }

  active_buffer_index = 0u;
}

void next_active_buffer_index()
{
  for (auto i = active_buffer_index + 1; i < ring_buffer_size; ++i) {
    if (ring_buffer_map[i] == empty) {
      active_buffer_index = i;
      return;
    }
  }
  for (auto i = 0u; i < active_buffer_index; ++i) {
    if (ring_buffer_map[i] == empty) {
      active_buffer_index = i;
      return;
    }
  }
  throw std::runtime_error("buffer overflow. no empty buffer available.");
}

void write_data(size_t val)
{
  //std::cout << "writing data " << val << " to buffer " << active_buffer_index << std::endl;
  auto & active_buffer = ring_buffer[active_buffer_index];
  active_buffer.emplace_back(POD<verbose>(val));

  if (active_buffer.size() >= buffer_capacity) {
    auto current_index = active_buffer_index;
    next_active_buffer_index();
    std::cout << "new active buffer index: " << active_buffer_index << std::endl;
    ring_buffer_map[current_index] = full;
  }
}

void store_data()
{
  while (running) {
    for (auto i = 0u; i < ring_buffer_size; ++i) {
      if (ring_buffer_map[i] == full) {
        std::cout << "writing buffer no. " << i << std::endl;
        // write data
        auto & full_buffer = ring_buffer[i];
        write(ring_buffer[i]);
        full_buffer.clear();
        full_buffer.reserve(buffer_capacity);
        ring_buffer_map[i] = empty;
      }
    }
  }
  // flush remaining
  for (auto i = 0u; i < ring_buffer_size; ++i) {
    if (ring_buffer_map[i] == full) {
      std::cout << "writing buffer no. " << i << std::endl;
      // write data
      auto & full_buffer = ring_buffer[i];
      write(ring_buffer[i]);
      full_buffer.clear();
      full_buffer.reserve(buffer_capacity);
      ring_buffer_map[i] = empty;
    }
  }
}

int main()
{
  initialize_buffers();
  //next_active_buffer_index();
  if (active_buffer_index != 0u) {
    std::cout << "something went wrong here" << std::endl;
    return -1;
  }

  auto handle = std::async(std::launch::async, &store_data);

  // dt is the duraiton for writing individual PODs
  while (counter <= message_count) {
    write_data(counter);

    std::this_thread::sleep_for(dt);
    ++counter;
  }

  running = false;
  handle.wait();

  std::cout << "accumulate data size: " << accumulate_data.size() << std::endl;
  for (size_t i = 1u; i < accumulate_data.size(); ++i) {
    if (accumulate_data[i].data - accumulate_data[i - 1].data != 1u) {
      std::cout<< "integrity is violated: " << accumulate_data[i].data << " comes after " << accumulate_data[i - 1].data << std::endl;
    }
  }
  std::cout << std::endl;
  POD<verbose>::print_statistics();
  return 0;
}
