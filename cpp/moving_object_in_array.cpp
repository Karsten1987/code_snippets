#include <iostream>
#include <array>

template<size_t N>
void print_array(std::array<size_t, N> & arr)
{
  for (auto n : arr) {
    printf("%zu ", n);
  }
  printf("\n");
}

template<size_t N>
void reverse_array(std::array<size_t, N> & arr, size_t lhs, size_t rhs)
{
  while (rhs > lhs) {
    std::swap(arr[lhs], arr[rhs]);
    --rhs;
    ++lhs;
  }
}

template<size_t N>
void my_rotate(std::array<size_t, N> & arr,
  size_t lhs, size_t middle, size_t rhs)
{
  if (lhs > middle) {
    return;
  }
  if (middle > rhs) {
    return;
  }

  reverse_array(arr, lhs, middle -1);
  reverse_array(arr, middle, rhs);
  reverse_array(arr, lhs, rhs);
}

int main()
{
  std::array<size_t, 8> arr = {1, 2, 4, 5, 3, 6, 7, 8};
  print_array(arr);
  auto ret = std::rotate(arr.begin() + 2, arr.end() - 2, arr.end() - 2);
  print_array(arr);
  std::cout << "ret " << *ret << std::endl;
  std::array<size_t, 5> arr2 = {5, 1, 2, 3, 4};
  ret = std::rotate(arr2.begin(), arr2.begin() + 1, arr2.end());
  print_array(arr2);
  std::cout << "ret " << *ret << std::endl;

  std::array<size_t, 9> my_arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  print_array(my_arr);
  my_rotate(my_arr, 1, 5, 7);
  print_array(my_arr);
  return 0;
}
