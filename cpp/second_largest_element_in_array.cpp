#include <vector>

size_t find_second_largest_value(const std::vector<size_t> & v)
{
  if (v.size() == 1) {
    return v[0];
  }

  size_t largest_element = 0u;
  size_t second_element = 0u;

  for (size_t i = 1; i < v.size(); ++i) {
    if (v[i] > largest_element) {
      second_element = largest_element;
      largest_element = v[i];
    } else {
      if (v[i] > second_element) {
        second_element = v[i];
      }
    }
  }

  return second_element;
}

int main()
{
  //std::vector<size_t> v = {1, 3, 5, 67, 13, 1231, 124, 9, 12324};
  std::vector<size_t> v = {10, 10, 10};
  size_t second_largest = find_second_largest_value(v);
  printf("second largest %zu\n", second_largest);
  return 0;
}
