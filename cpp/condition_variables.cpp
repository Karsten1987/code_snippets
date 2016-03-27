#include <iostream>
#include <csignal>
#include <mutex>
#include <vector>
#include <array>
#include <random>
#include <thread>
#include <atomic>
#include <condition_variable>

struct Product
{
  Product()
  {}

  Product(int id_, double data_):
    id(id_),
    data(data_)
  {}

  int id = -1;
  double data = -1;
};

bool                      shutdown_requested;

//std::mutex                mutex_producer;
//std::mutex                mutex_consumer;
std::mutex                mutex_products;
std::mutex                mutex_print;

std::condition_variable   cv_free_spot;
bool                      cv_notified;

std::atomic<int>          array_index;
std::array<Product, 5>    all_products;

// initialize a random generator
std::mt19937 generator((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_int_distribution<> dis(1, 10);

void producer( int id )
{
  while (!shutdown_requested)
  {
    int seconds = dis(generator);
    std::this_thread::sleep_for(std::chrono::seconds(seconds));

    Product p = {id, id*13.5};

    {
      // wait until free spot is there
      std::unique_lock<std::mutex> cv_lock(mutex_products);
      cv_free_spot.wait(cv_lock, [](){ return cv_notified == true;});
      
      // if in the meantime a shutdown was requested
      if (shutdown_requested)
      {
        return;
      }

      if (all_products[array_index].id != -1)
      {
        std::cout << "FAILLLLL" << std::endl;
      }
      all_products[array_index] = p;
      cv_notified = false;
    }

    {
      std::lock_guard<std::mutex> lg(mutex_print);
      std::cout << "[producer #" << id << "] produces data: " << p.data << std::endl;
    }
  }
}

void consumer( int id )
{
  while (!shutdown_requested)
  {
    int seconds = dis(generator);
    std::this_thread::sleep_for(std::chrono::seconds(seconds));

    int idx = array_index.load();

    {
      std::unique_lock<std::mutex> cv_lock(mutex_products);
      Product& p = all_products[idx];

      {
        std::lock_guard<std::mutex> lg(mutex_print);
        std::cout << "[consumer #" << id << "] consumes data: " << p.data << std::endl;
      }
      p.id = -1;
      p.data = -1.0;
    }

    array_index.store(++idx%all_products.size());
    cv_notified = true;
    cv_free_spot.notify_one();
  }

  std::unique_lock<std::mutex> lock(mutex_products);
  cv_notified = true;
  cv_free_spot.notify_all();
}

void sigint_handler( int /**/ )
{
  {
    std::lock_guard<std::mutex> lg(mutex_print);
    std::cout << "shutdown requested ..!" << std::endl;
    shutdown_requested = true;
  }
  cv_notified = true;

}

int main()
{
  signal(SIGINT, sigint_handler);

  std::array<std::thread, 10> producer_pool;
  std::array<std::thread, 5>  consumer_pool;

  for (size_t i=0; i<producer_pool.size(); ++i)
  {
    int id = i;
    producer_pool[i] = std::thread(producer, ++id);
  }

  for (size_t i=0; i<consumer_pool.size(); ++i)
  {
    int id = i;
    consumer_pool[i] = std::thread(consumer, ++id);
  }

  while (!shutdown_requested)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  for (auto& t : producer_pool)
  {
    t.join();
  }

  for (auto& t : consumer_pool)
  {
    t.join();
  }

  for (auto& p : all_products)
  {
    std::cout << "Product id: " << p.id << "\tdata: " << p.data << std::endl;
  }

  return 0;
}
