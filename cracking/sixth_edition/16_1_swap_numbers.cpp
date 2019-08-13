#include <iostream>

int main()
{
  int a = 13;
  int b = 5;

  printf("before swap: a=%d, b=%d\n", a, b);
  a = a - b;  // a = 8
  b = b + a;  // b = -13
  a = b - a; // a = 5

  printf("after swap: a=%d, b=%d\n", a, b);
}
