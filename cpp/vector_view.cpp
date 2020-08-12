#include <iostream>
#include <vector>

template<class T>
class VectorView
{
  class iterator
  {
  public:
    typedef iterator self_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int difference_type;

    iterator(std::vector<T> & base, std::vector<size_t> & indices)
    :iterator(base, indices, 0)
    {}

    iterator(std::vector<T> & base, std::vector<size_t> & indices, size_t index)
    : current_index_(index),
      base_(base),
      indices_(indices),
      ptr_(&base[indices[current_index_]])
    {}

    self_type operator++()
    {
      self_type i = *this;
      ++i.current_index_;
      i.ptr_ = &base_[indices_[i.current_index_]];
      return i;
    }

    reference operator*() {
      return *ptr_;
    }

    pointer operator->() {
      return ptr_;
    }

    bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }

  private:
    size_t current_index_;
    std::vector<T> & base_;
    std::vector<size_t> & indices_;
    pointer ptr_;
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

int main() {

  std::vector<int> base = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  VectorView<int> view(base, {0, 2, 4, 6, 8});

  auto it = view.begin();
  std::cout << *it << std::endl;
  std::cout << *++it << std::endl;
  return 0;
}
