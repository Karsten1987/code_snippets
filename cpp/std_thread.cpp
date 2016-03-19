#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <mutex>
#include <future>
#include <csignal>

std::mutex mutex_print;

struct Status
{
  size_t stat;
};

//auto fut = std::async(std::launch::async, asyncStatusPrint, std::ref(st));

bool shutdown_requested;
std::atomic<int> account;
//int account;

void loopIncrement()
{
  while (!shutdown_requested)
  {
    {
      std::lock_guard<std::mutex> lg(mutex_print);
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      //std::cout << "increment " << account << std::endl;
      ++account;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  std::cout << "Shutting down increment loop" << std::endl;
}

void loopDecrement()
{
  while (!shutdown_requested)
  {
    {
      std::lock_guard<std::mutex> lg(mutex_print);
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      //std::cout << "decrement " << account << std::endl;
      --account;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Shutting down decrement loop" << std::endl;
}

void loopDuplicate()
{
  while (!shutdown_requested)
  {
    auto start = std::chrono::steady_clock::now();
    {
      std::lock_guard<std::mutex> lg(mutex_print);
      std::this_thread::sleep_for(std::chrono::milliseconds(300)); // fake work
      //std::cout << "duplicate " << account << std::endl;
      account += account;
    }
    auto end = std::chrono::steady_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    if (dt > std::chrono::milliseconds(1000))
    {
      std::cout << "missed cycle in duplicate " << dt.count() << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000 - dt.count()));
  }
  std::cout << "Shutting down duplicate loop" << std::endl;
}

void loopBisect()
{
  while (!shutdown_requested)
  {
    {
      std::lock_guard<std::mutex> lg(mutex_print);
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      //std::cout << "bisect " << account << std::endl;
      account -= account/2;
    }
    std::this_thread::sleep_for(std::chrono::seconds(5));
  }
  std::cout << "Shutting down bisect loop" << std::endl;
}

void shutdown(int signal)
{
  shutdown_requested = true;
}

struct S
{
  int i = 0;

  void operator()()
  {
    while (!shutdown_requested)
    {
      std::cout << "Having new int " << ++i << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  }
};

int main()
{
  std::signal(SIGINT, shutdown);

  S s;
  //std::thread t1(std::ref(S())); // fails
  std::thread t1(s);
  std::this_thread::sleep_for(std::chrono::milliseconds(5002));
  std::cout << "transmission of thread ownership" << std::endl;
  std::thread t2 = std::move(t1);

  std::thread thread_inc(loopIncrement);
  std::thread thread_dec(loopDecrement);
  std::thread thread_dup(loopDuplicate);
  std::thread thread_bis(loopBisect);

  //while (!shutdown_requested)
  //{
  //  std::cout << "Current account balance " << account << std::endl;
  //  std::this_thread::sleep_for(std::chrono::seconds(1));
  //}

  thread_inc.join();
  thread_dec.join();
  thread_dup.join();
  thread_bis.join();

  // t1.join(); system error!
  t2.join();

  std::cout << "shutting down! Good bye.." << std::endl;
  return 0;
}
