#include <numeric>
#include <iostream>
#include <vector>

void fizz_buzz(size_t d1, size_t d2, std::vector<size_t> & input_vec)
{
  for (auto i = 0u; i < input_vec.size(); ++i) {
    auto mod_d1 = (input_vec[i] % d1) == 0;
    auto mod_d2 = (input_vec[i] % d2) == 0;
    if (mod_d1 && mod_d2) {
      printf("FizzBuzz, ");
    } else if (mod_d1) {
      printf("Fizz, ");
    } else if (mod_d2) {
      printf("Buzz, ");
    } else {
      printf("%u, ", i);
    }
  }
  printf("\n");
}

template<size_t N>
struct Number
{
  static constexpr const char * value  = "" + N;
};

struct Fizz
{
  static constexpr const char * value = "Fizz";
};

struct Buzz
{
  static constexpr const char * value = "Buzz";
};

struct FizzBuzz
{
  static constexpr const char * value = "FizzBuzz";
};

template<size_t N, size_t D, class T>
struct is_divisible
{
  using type = T;
  static constexpr bool value = N % D == 0;
};

// template<size_t N, size_t D1, size_t D2, class T>
// struct Value;
// 
// template<size_t N, size_t D1, size_t D2>
// struct Value : std::enable_if<is_divisible<N, D1, Fizz>::value, Fizz>::type
// {
// };
// 
// template<size_t N, size_t D1, size_t D2>
// struct Value<N, D1, D2, std::enable_if<is_divisible<N, D1, Fizz>::value, Fizz>::type>
// {
// };

//};

template<size_t N, bool B, class T>
struct Divisor;

template<size_t N, class T>
struct Divisor<N, false, T> : Number<N>
{};

template<size_t N>
struct Divisor<N, true, Fizz> : Fizz
{};

template<size_t N>
struct Divisor<N, true, Buzz> : Buzz
{};

template<size_t N, size_t D1, size_t D2, class T>
struct Value;

// void -> number
template<size_t N, size_t D1, size_t D2>
struct Value : Divisior<N, is_divisible<N, D1, D1>::value, Fizz>
{
};

int main(int argc, char ** argv)
{
  auto vec = std::vector<size_t>(50);
  std::iota(vec.begin(), vec.end(), 0);
  fizz_buzz(3, 5, vec);

//  printf("%s\n", Value<9, 3, 5>::value);
//  printf("%s\n", Value<10, 3, 5>::value);
  return 0;
}
