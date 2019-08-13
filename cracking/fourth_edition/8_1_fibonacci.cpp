#include <vector>

template<size_t N>
struct Fibonacci
{
  static constexpr size_t value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

template<>
struct Fibonacci<1>
{
  static constexpr size_t value = 1;
};

template<>
struct Fibonacci<0>
{
  static constexpr size_t value = 1;
};

void fibonacci_rec(size_t k1, size_t k2, size_t i, size_t n, std::vector<size_t> & numbers)
{
  if (i == n) {
    return;
  }

  numbers.push_back(k1+k2);
  fibonacci_rec(k2, k1+k2, ++i, n, numbers);
}

std::vector<size_t> get_fibonacci_numbers(size_t n)
{
  std::vector<size_t> numbers;
  numbers.reserve(n);
  numbers.push_back(0);
  numbers.push_back(1);
  fibonacci_rec(0, 1, 0, n, numbers);

  return numbers;
}

int main()
{
  constexpr size_t n = 10u;
  auto fibonacci = get_fibonacci_numbers(n);
  for (auto & n : fibonacci) {
    printf("%zu\n", n);
  }
  printf("%zu\n", Fibonacci<2>::value);
  printf("the %zuth Fibonacci is %zu\n", n, Fibonacci<n>::value);
  return 0;
}
