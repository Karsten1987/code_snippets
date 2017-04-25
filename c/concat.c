#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// static global has internal linkage
static const char * prefix = "rt";

int main()
{
  const char * postfix = "hello/world";

  size_t length = strlen(prefix) + strlen(postfix) + strlen("/");
  char * concat = (char*)malloc(length +1);

  int n = snprintf(concat, length+1, "%s/%s", prefix, postfix);
  if (n < 0) {
    fprintf(stderr, "Snprintf failed\n");
  }
  if (n != length) {
    fprintf(stderr, "something went wrong with concat. Return code: %d\n", n);
  }

  printf("%s\n", concat);

  return 0;
}
