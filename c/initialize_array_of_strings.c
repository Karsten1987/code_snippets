#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct string_array
{
  size_t count;
  char ** strings;
} string_array_t;

void fill_array(string_array_t * array)
{
  array->count = 3;

  array->strings = malloc(3*sizeof(char*));
  //array->strings[0] = malloc(5*sizeof(char));
  //strcpy(array->strings[0], "Hello");
  //array->strings[1] = malloc(6*sizeof(char));
  //strcpy(array->strings[1], "World");
  //array->strings[2] = malloc(2*sizeof(char));
  //strcpy(array->strings[2], "!");
  array->strings[0] = strndup("Hello", 5);
  array->strings[1] = strndup("World", 6);
  array->strings[2] = strndup("!", 2);
}

void destroy_array(string_array_t * array)
{
  for (size_t i = 0; i < array->count; ++i)
  {
    free(array->strings[i]);
  }
  free(array->strings);
}

int main()
{
  string_array_t array;
  fill_array(&array);

  for (size_t i = 0; i < array.count; ++i)
  {
    printf("#%zu\t %s\n", i, array.strings[i]);
  }

  destroy_array(&array);
}
