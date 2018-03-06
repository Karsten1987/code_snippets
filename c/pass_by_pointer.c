#include <stdio.h>
#include <stdlib.h>

typedef struct A
{
  int a;
} A;

void call_by_const_ptr(const A * a_ptr)
{
  free(a_ptr);
  a_ptr = NULL;
}

void call_by_ptr(A * a_ptr)
{
  free(a_ptr);
  a_ptr = NULL;
}

void call_by_const_const_ptr(const A * const a_ptr)
{
  free(a_ptr);
}

int main(int argc, char ** argv)
{
  A * a = malloc(sizeof(A));
  a->a = 12;
  //call_by_const_ptr(a);
  //call_by_ptr(a);
  call_by_const_const_ptr(a);

  a->a = 14;
  fprintf(stderr, "new a %d\n", a->a);
}
