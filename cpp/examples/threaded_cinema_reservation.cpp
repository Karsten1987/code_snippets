#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <algorithm>
/*
 * idea here is to spawn multiple threads (aka clients)
 * who are about to randomly purchase places
 * places are reserved by incrementing the cinema vector
 * this has to be safe since multiple threads can reserve
 * the same spot simulataneously
 */

std::vector<int> cinema(100, 0);

void printCinema()
{
  for (auto i=cinema.begin(); i!=cinema.end(); )
  {
    std::cout << *i << " ";
    if (std::distance(++i, cinema.end())%10 == 0)
    {
      std::cout << std::endl;
    }
  }
}

namespace random_gen
{
 std::random_device rd;
 std::mt19937 gen(rd());

 int wait( int client_number )
 {
   static std::uniform_int_distribution<> dis(0, 6);
   int wait_in_sec = dis(gen);
   //std::cout << "client " << client_number << " is going to sleep for " << wait_in_sec << " seconds" << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(wait_in_sec));
   return wait_in_sec;
 }

 int places( )
 {
   static std::uniform_int_distribution<> dis(1,4);
   int places = dis(gen);
   return places;
 }
}

std::mutex print_mutex;
std::mutex cinema_mutex;

void reservePlace( int client_number )
{
  int wait_time = random_gen::wait(client_number);
  for (auto i=0; i<random_gen::places(); ++i)
  {
    //std::lock_guard<std::mutex> cg(cinema_mutex);
    auto place = std::find_if(cinema.begin(), cinema.end(), [](int& i)
      {
       return i == 0;
      });
    if (place == cinema.end())
    {
      std::lock_guard<std::mutex> lg(print_mutex);
      std::cout << "No free place available!" << std::endl;
    }
    ++(*place);
    std::lock_guard<std::mutex> lg(print_mutex);
    std::cout << "client " << client_number << " is going to reserve place " << std::distance(cinema.begin(), place) << " after " << wait_time << " seconds" << std::endl;
  }
}


int main()
{
  printCinema();

  auto constexpr number_of_clients = 50;
  std::vector<std::thread> clients;
  for (auto i=0; i<number_of_clients; ++i)
  {
    clients.emplace_back(std::thread(reservePlace, i));
  }

  for (auto& thread : clients)
  {
    thread.join();
  }

  printCinema();

  std::cout << "sanity check " << std::accumulate(cinema.begin(), cinema.end(), 0) << std::endl;
  return 0;
}
