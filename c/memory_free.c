#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct my_struct_
{
  size_t size;
  char ** data;
} MyStruct;

size_t my_struct_fini(MyStruct * ms)
{
  if (!ms){
    return 1;
  }

  for (size_t i = 0; i < ms->size; ++i) {
    if (ms->data[i]) {
      free(ms->data[i]);
      ms->data[i] = NULL;
    }
  }

  if (ms->data) {
    free(ms->data);
    ms->data = NULL;
  }

  return 0;
}

int main(int argc, char** argv)
{

  // doesn't work because size_t might be shitty
  MyStruct ms;
  //ms.size = 0;
  my_struct_fini(&ms);

  //unsigned long array_size = 100000000000000;
  //unsigned long memory_size = (array_size*sizeof(int))/1024;
  //printf("expected memory > %lu\n", memory_size);
  //int* data_array = calloc(array_size, sizeof(int));

  //int counter = 0;
  //while(counter != 100)
  //{
  //  long busy_loop = 0;
  //  while (busy_loop < 1000)
  //  {
  //    busy_loop++;
  //  }
  //  counter++;
  //  sleep(1);  // one second
  //}
  //free(data_array);
  return 0;
}
