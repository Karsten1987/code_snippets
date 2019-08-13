#include <iostream>
#include <vector>

template<class T>
void print_vector(const std::vector<T> & vec)
{
  for (auto & element : vec) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

template<class T>
size_t partition(std::vector<T> & vec, int lhs,  int rhs)
{
  int pivot_index = (rhs + lhs) / 2;
  auto pivot = vec[pivot_index];
  while (lhs <= rhs) {
    // find element on left which should go to the right
    while (vec[lhs] < pivot) {
      ++lhs;
    }
    // find element on right which should got to the left
    while (vec[rhs] > pivot) {
      --rhs;
    }
    if (lhs <= rhs) {
      std::swap(vec[lhs], vec[rhs]);
      ++lhs;
      --rhs;
    }
  }
  return lhs;
}

template<class T>
void quick_sort(std::vector<T> & vec, size_t lhs, size_t rhs)
{
  if (lhs >= rhs) {
    return;
  }

  auto index = partition(vec, lhs, rhs);
  quick_sort(vec, lhs, index - 1);
  quick_sort(vec, index, rhs);
}

int main()
{
  std::vector<size_t> vec = {1, 5, 32, 67, 928, 2, 4, 5, 18};
  quick_sort(vec, 1, vec.size() - 2);
  print_vector(vec);
}
