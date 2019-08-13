#include <iostream>
#include <math.h>
#include <vector>

double polygon(double x, std::vector<double> coeff, std::vector<double> exponentials)
{
  if (coeff.size() != exponentials.size() + 1) {
    throw std::runtime_error("coeff size doesn't match exponentials");
  }

  double p = 0.0;
  size_t i = 0;
  for (; i < exponentials.size(); ++i) {
    p += coeff[i] * pow(x, exponentials[i]);
  }
  p+= coeff[i];

  return p;
}

int main()
{
  std::vector<double> coeff = {1.1, 2.2, 3.3, 4.4, 5.5, 10};
  std::vector<double> exponentials = {5.5, 4.4, 3.3, 2.2, 1.1};

  double x = 1;
  auto p = polygon(x, coeff, exponentials);

  std::cout << "p = " << p << std::endl;
  return 0;
}
