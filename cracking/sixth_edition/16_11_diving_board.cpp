#include <iostream>
#include <vector>

template<class T>
void print_vector(const std::vector<T> & vec)
{
  for (const auto & el : vec) {
    std::cout << "[" << el << "]";
  }
  std::cout << std::endl;
}

int main()
{
  size_t s = 5;
  size_t l = 10;

  size_t k = 3;

  std::vector<unsigned long> vec;
  for (size_t i = 1lu; i <= k; ++i) {
    vec.push_back(i * s + (k-i) * l);
  }
  print_vector(vec);
}
