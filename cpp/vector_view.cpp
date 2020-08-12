#include <iostream>
#include <vector>

#include "pod.hpp"

template<class T>
class VectorView
{
  class iterator : public std::vector<T>::reverse_iterator
  {
  public:
    iterator(std::vector<T> & base, std::vector<size_t> & indices)
    :iterator(base, indices, 0)
    {}

    iterator(std::vector<T> & base, std::vector<size_t> & indices, size_t index)
    : current_index_(index),
      base_(base),
      indices_(indices),
      ptr_(&base[indices[current_index_]])
    {
      if (current_index_ >= indices_.size()) {
        ptr_ = &base[base.size()];
      }
    }

    iterator operator++()
    {
      ++current_index_;
      if (current_index_ >= indices_.size()) {
        ptr_ = &base_[base_.size()];
      } else {
        ptr_ = &base_[indices_[current_index_]];
      }
      return *this;
    }

    T & operator*()
    {
      return *ptr_;
    }

    T * operator->()
    {
      return ptr_;
    }

    bool operator==(const iterator & rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const iterator & rhs) { return ptr_ != rhs.ptr_; }

  private:
    size_t current_index_;
    std::vector<T> & base_;
    std::vector<size_t> & indices_;
    T * ptr_;
  };

public:
  VectorView(std::vector<T> & base, const std::vector<size_t> & indices)
    : base_(base), indices_(indices)
  {}

  iterator begin()
  {
    return iterator(base_, indices_);
  }

  iterator end()
  {
    return iterator(base_, indices_, indices_.size());
  }

private:
  std::vector<T> & base_;
  std::vector<size_t> indices_;
};

int main()
{
  using type_t = POD<true>;
  std::vector<type_t> base(10);
  for (auto i = 0u; i < base.size(); ++i) {
    base[i].data = i;
  }
  //std::vector<int> base = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  VectorView<type_t> view(base, {9, 8, 7, 6, 5, 4, 3, 2, 1, 0});

  auto it = view.begin();
  ++it;
  ++it;

  for (const auto & i : view) {
    std::cout << i.data << std::endl;
  }
  return 0;
}
