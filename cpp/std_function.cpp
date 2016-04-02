#include <iostream>
#include <functional>

template<class return_t, class... Args>
return_t call( std::function<return_t(Args...)> f, Args... args )
{
  return_t ret = f(args...);
  return ret;
}

int add( int n1, int n2 )
{
  return n1+n2;
}

int main()
{
  std::function<int(int, int)> f_add = add;
  auto sum = call(f_add, 1, 2);
  std::cout << "sum of 1 and 2 =" << sum << std::endl;

  std::function<decltype(add)> f_add_decl = add;
  auto sum1 = call(std::function<decltype(add)>(add), 3, 4);
  std::cout << "sum of 3 and 4 = " << sum1 << std::endl;
  return 0;
}
