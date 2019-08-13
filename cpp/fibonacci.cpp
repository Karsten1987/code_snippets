#include <iostream>
#include <unordered_map>

int fibonacci(size_t lhs, size_t rhs, size_t counter, size_t & ticks)
{
  ++ticks;
  if (counter == 0)
  {
    return lhs;
  }
  return fibonacci(rhs, lhs+rhs, --counter, ticks);
}

template<int LHS, int RHS, size_t COUNTER>
struct fibonacci_t
{
  static constexpr int value = fibonacci_t<RHS, LHS + RHS, COUNTER - 1>::value;
};

template<size_t LHS, size_t RHS>
struct fibonacci_t<LHS, RHS, 0>
{
  static constexpr int value = LHS;
};

int fibonacci_alt(size_t counter, size_t & ticks)
{
  ++ticks;
  if (counter == 0) {
    return 0;
  }
  if (counter == 1) {
    return 1;
  }
  // std::cout << "processing n = " << counter << std::endl;
  return fibonacci_alt(counter - 1, ticks) + fibonacci_alt(counter - 2, ticks);
}

int fibonacci_memo(
  size_t counter,
  std::unordered_map<size_t, int> & memo,
  size_t & ticks)
{
  auto entry = memo.find(counter);
  if (entry != memo.end()) {
    return entry->second;
  }

  ++ticks;
  if (counter == 0) {
    memo[counter] = 0;
    return 0;
  }
  if (counter == 1) {
    memo[counter] = 1;
    return 1;
  }

  auto new_entry1 = fibonacci_memo(counter - 1, memo, ticks);
  auto new_entry2 = fibonacci_memo(counter - 2, memo, ticks);
  memo[counter] = new_entry1 + new_entry2;
  return new_entry1 + new_entry2;
}

int main()
{
  size_t ticks = 0;
  std::cout << "recursive function " << fibonacci(0, 1, 10, ticks) << std::endl;
  std::cout << "ticks " << ticks << std::endl;
  std::cout << "recursive template " << fibonacci_t<0, 1, 10>::value << std::endl;
  size_t alt_ticks = 0;
  std::cout << "recursive function alt " << fibonacci_alt(10, alt_ticks) << std::endl;
  std::cout << "alt ticks " << alt_ticks << std::endl;
  std::unordered_map<size_t, int> memo;
  size_t memo_ticks = 0;
  std::cout << "memo function " << fibonacci_memo(10, memo, memo_ticks) << std::endl;
  std::cout << "memo ticks " << memo_ticks << std::endl;
  return 0;
}
