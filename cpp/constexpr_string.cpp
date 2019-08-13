#include <iostream>

template<const char * T>
struct FirstChar
{
  static constexpr char c = T[0];
};

static constexpr const char * const str = "hello world";

int main()
{
  std::cout << "first char " << FirstChar<"Hello World">::c << std::endl;
  return 0;
}
