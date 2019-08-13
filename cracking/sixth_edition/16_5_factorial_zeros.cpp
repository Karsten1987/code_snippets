#include <cmath>
#include <iostream>
#include <vector>

template<size_t N>
struct Factorial
{
  static constexpr unsigned long value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<1>
{
  static constexpr unsigned long value = 1;
};

template<size_t M, size_t N>
struct Pow
{
  static constexpr unsigned long value = M * Pow<M, N-1>::value;
};

template<size_t M>
struct Pow<M, 1>
{
  static constexpr unsigned long value = M;
};

template<unsigned long N, size_t CounterT, bool Condition>
struct Modulo;

template<unsigned long N, size_t CounterT>
struct Modulo<N, CounterT, false>
{
  static constexpr size_t value = CounterT -1;
};

template<unsigned long N, size_t CounterT>
struct Modulo<N, CounterT, true>
{
  static constexpr size_t value = Modulo<N, CounterT + 1, ((Factorial<N>::value % Pow<10, CounterT + 1>::value) == 0)>::value;
};

template<size_t N, size_t CounterT = 1>
struct TrailingZeros
{
  static constexpr size_t value = Modulo<N, CounterT, Factorial<N>::value % Pow<10, CounterT>::value == 0>::value;
};

size_t count_trailing_zeros(unsigned long value)
{
  size_t n = 1;
  while (true) {
    auto value_n = value % static_cast<unsigned long>(pow(10, n));
    if (value_n != 0) {
      return n-1;
    }
    ++n;
  }
}

int main()
{
  constexpr size_t n = 10;
  auto fn = Factorial<n>::value;

  std::cout << "fn: " << fn << std::endl;
  auto trailing_zeros = count_trailing_zeros(fn);
  std::cout << "got n trailing zeros: " << trailing_zeros << std::endl;

  std::cout << "TrailingZeros::value " << TrailingZeros<10>::value << std::endl;
}
