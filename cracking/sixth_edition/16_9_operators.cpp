#include <iostream>

int negate(int i)
{
  int neg_i = 0;
  int delta_i = i > 0 ? -1 : 1;

  while (i != 0) {
    neg_i += delta_i;
    i += delta_i;
  }
  return neg_i;
}

int substract(int i, int j)
{
  return i + negate(j);
}

int multiply(int a, int b)
{
  int delta = b > 0 ? a : negate(a);
  b = b > 0 ? b : negate(b);
  int sum = 0;
  for (int i = 0; i < b; ++i) {
    sum += delta;
  }
  return sum;
}

int divide(int a, int b)
{
  int counter = 0;
  int delta = b > 0 ? b : negate(b);
  bool inverse = ((a >= 0 && b >= 0) || (a <=0 && b <= 0)) ? false : true;
  if (a > 0) {
    while (a >= 0) {
      a = substract(a, delta);
      ++counter;
    }
  } else {
    while (a <= 0) {
      a += delta;
      ++counter;
    }
  }
  if (!inverse){
    return counter - 1;
  }
  return negate(counter - 1);
}

int main()
{
  int a = 1234;
  int b = 10;
  std::cout << a << "  " << negate(a) << std::endl;
  std::cout << a << " " << b << " " << substract(a, b) << std::endl;
  std::cout << a << " " << b << " " << multiply(a, b) << std::endl;
  std::cout << a << " " << b << " " << divide(a, b) << std::endl;
}
