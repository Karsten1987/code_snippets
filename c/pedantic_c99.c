#include <stdio.h>

int main()
{
  for (size_t i = 0; i < 10; ++i) {
    fprintf(stderr, "Hello %zu\n", i);
  }
  return 0;
}
