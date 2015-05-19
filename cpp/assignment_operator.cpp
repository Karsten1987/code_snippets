#include <stdio.h>
#include <iostream>

struct A
{
  A(int i):
  i_(i)
  {}

private:
  int i_;
};

struct B
{
  B(const A* a, float f):
    a_(a),
    f_(f)
  {}

private:
  const A* a_;
  float f_;
};

int main()
{
  A a(123);
  B b1(&a, 1.3f);
  B b2(&a, 2.3f);
  B b3(b2);

  B b4 = b3;
  b4 = b2;
  A* a_ptr(&a);

  return 0;
}

