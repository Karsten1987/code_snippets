#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
  unsigned long array_size = 100000000000000;
  unsigned long memory_size = (array_size*sizeof(int))/1024;
  printf("expected memory > %lu\n", memory_size);
  int* data_array = calloc(array_size, sizeof(int));

  int counter = 0;
  while(counter != 100)
  {
    long busy_loop = 0;
    while (busy_loop < 1000)
    {
      busy_loop++;
    }
    counter++;
    sleep(1);  // one second
  }
  free(data_array);
  return 0;
}
