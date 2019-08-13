#include <vector>
#include <iostream>

template<class T>
void print_vector(const std::vector<T> & vec)
{
  for (auto & element : vec) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

template<class T>
void merge(std::vector<T> & vec, std::vector<T> & helper, int lhs, int middle, int rhs)
{
  for (int i = lhs; i <= rhs; ++i) {
    printf("copying %zu\n", vec[i]);
    helper[i] = vec[i];
  }

  int front_left = lhs;
  int front_right = middle + 1;
  int current = lhs;

  while (front_left <= middle && front_right <= rhs) {
    if (helper[front_left] <= helper[front_right]) {
      vec[current] = helper[front_left];
      ++front_left;
    } else {
      vec[current] = helper[front_right];
      ++front_right;
    }
    ++current;
  }

  while (front_left <= middle) {
    vec[current] = helper[front_left];
    ++front_left;
    ++current;
  }
  while (front_right < rhs) {
    vec[current] = helper[front_right];
    ++front_right;
    ++current;
  }
}

template<class T>
void merge_sort(std::vector<T> & vec, std::vector<T> & helper, int lhs, int rhs)
{
  if (lhs >= rhs) {
    return;
  }

  auto middle = (lhs + rhs) / 2;
  merge_sort(vec, helper, lhs, middle);
  merge_sort(vec, helper, middle + 1, rhs);
  merge(vec, helper, lhs, middle, rhs);
}

template<class T>
void merge_sort(std::vector<T> & vec)
{
  std::vector<T> helper(vec.size());
  merge_sort(vec, helper, 0u, vec.size() - 1);
}

int main()
{
  std::vector<size_t> vec = {1, 5, 32, 67, 928, 2, 4, 5, 18};
  merge_sort(vec);
  print_vector(vec);
}
