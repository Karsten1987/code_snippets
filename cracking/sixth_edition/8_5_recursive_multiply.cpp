#include <iostream>
#include <vector>

long multiply(int prod1, int prod2)
{
  long prod = prod1;
  for (auto i = 1; i < prod2; ++i) {
    prod += prod1;
  }

  return prod;
}

long multiply_rec(int prod1, int prod2)
{
  if (prod1 == 0) {
    return 0;
  }
  if (prod1 == 1) {
    return prod2;
  }

  int prod1_half = prod1 >> 1;
  long prod1_prod = multiply_rec(prod1_half, prod2);

  if (prod1 % 2 == 0) {
    return prod1_prod + prod1_prod;
  }
  return prod1_prod + prod1_prod + prod2;
}

long multiply_short(int prod1, int prod2)
{
  if (prod1 < prod2) {
    return multiply_rec(prod1, prod2);
  }
  return multiply_rec(prod2, prod1);
}

int main()
{
  int prod1 = 12;
  int prod2 = 25;

  long prod = multiply_short(prod1, prod2);
  std::cout << "prod: " << prod << " = " << prod1 * prod2 << std::endl;

  return 0;
}
