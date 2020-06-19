#include <iostream>

#include "helper.h"

class DataView
{
public:
  DataView(std::vector<double> * data)
  : data_(std::move(data))
  {}

  // Shallow Delete
  ~DataView() = default;

  DataView(const DataView & other) = delete;

  DataView(DataView && other) = default;

  std::vector<double> & get_data()
  {
    return *data_;
  }

private:
  std::vector<double> * data_;
};

class Actuator
{
public:
  Actuator(size_t size = 10)
  : data_(size)
  {
    std::cout << "producer data address: " << &data_ << std::endl;
  }

  DataView get_data_handle()
  {
    return DataView(&data_);
  }

private:
  std::vector<double> data_;
};

class Controller
{
public:
  Controller() = default;

  void update(DataView && data)
  {
    std::cout << "consumer data address: " << &data.get_data() << std::endl;
    helper::print_vector(data.get_data());
  }
};

int main()
{
  Actuator actuator1;
  Controller controller1;
  Controller controller2;

  controller1.update(actuator1.get_data_handle());
  return 0;
}
