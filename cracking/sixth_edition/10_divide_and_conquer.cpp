#include <vector>

template<class T>
T divide_and_conquer(const std::vector<T> & vec, size_t lhs, size_t rhs)
{
  if (lhs >= rhs) {
    printf("returning with single element %zu\n", vec[lhs]);
    return vec[lhs];
  }

  auto middle = lhs + ((rhs - lhs) / 2);
  auto left = divide_and_conquer(vec, lhs, middle);
  auto right = divide_and_conquer(vec, middle + 1, rhs);
  return left+right;
}

template<class T>
T divide_and_conquer(const std::vector<T> & vec)
{
  return divide_and_conquer(vec, 0, vec.size() - 1);
}

int main()
{
  std::vector<size_t> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  size_t sum = divide_and_conquer(vec);
  printf("got sum of %zu\n", sum);
}
