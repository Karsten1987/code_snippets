#include <iostream>

struct Square
{
  int a1;
  int a2;
  int b1;
  int b2;
};

struct Line
{
  //mx + b
  double m;
  double b;
};

Line bisect_squares(const Square & s1, const Square & s2)
{
  auto middle_point = [](const Square & s) -> std::pair<double, double> {
    return {s.a1 + (s.b1 - s.a1) / 2, s.a2 + (s.b2 - s.a2) / 2};
  };

  auto mp1 = middle_point(s1);
  auto mp2 = middle_point(s2);
  if (mp1 == mp2) {
    return {0.0, 0.0};
  }

  Line l;
  l.m = (mp1.second - mp2.second) / (mp1.first - mp2.first);
  l.b = mp1.second - l.m * mp1.first;
  // m x1 + b = y1
  // b = y1 - m * x1

  return l;
}

int main()
{
  Square s1 = {-2, -2, 2, 2};
  Square s2 = {2, 2, 4, 4};

  Line l = bisect_squares(s1, s2);
  std::cout << "found line with m: " << l.m << " and b " << l.b << std::endl;
  return 0;
}
