#include <iostream>
#include <vector>

#include "./helper.h"
#include "./pod.hpp"

template<
  class T,
  class Deleter = std::function<void(T *)>>
class LoanedResource
{
public:
  LoanedResource(
    T * resource,
    Deleter deleter)
  : resource_(resource),
    deleter_(deleter)
  {}

  ~LoanedResource()
  {
    deleter_(resource_);
  }

  LoanedResource(const LoanedResource & other) = delete;

  LoanedResource(LoanedResource && other) = default;

  void set_data(const T & value)
  {
    *resource_ = value;
  }

private:
  T * resource_;
  Deleter deleter_;
};

template<class T>
class ResourceManager
{
public:
  ResourceManager(size_t items)
  : loaned_(items, false)
  {
    resources_.resize(items);
  }

  LoanedResource<T> get_resource(size_t index)
  {
    if (index >= resources_.size()) {
      throw std::out_of_range("index not available");
    }

    if (loaned_[index]) {
      throw std::runtime_error("resource is already claimed");
    }

    loaned_[index] = true;

    auto deleter = std::bind(&ResourceManager<T>::return_resource, this, std::placeholders::_1, index);
    return LoanedResource<T>(&resources_[index], deleter);
  }

  void print_resources() const
  {
    helper::print_vector(resources_);
    helper::print_vector(loaned_);
  }

private:

  void return_resource(T * resource, size_t index)
  {
    (void) resource;
    loaned_[index] = false;
  }

  std::vector<T> resources_;
  std::vector<bool> loaned_;
};

int main()
{
  using ValueT = POD<true>;
  ResourceManager<ValueT> rm(10);

  {
    auto loan = rm.get_resource(0);
    auto loan2 = rm.get_resource(0);
    loan.set_data(ValueT(123));
    rm.print_resources();
  }

  rm.print_resources();
  return 0;
}
