#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tgmath.h>
typedef struct A
{
  char ** a_strings;
  size_t a_size;
} AStrings;

typedef struct B
{
  char ** b_strings;
  size_t b_size;
} BStrings;

typedef struct string_array
{
  char ** string_array;
  size_t size;
} string_array;

void print_A(const AStrings * a_strings)
{
  for (size_t i = 0; i < a_strings->a_size; ++i)
  {
    printf("#%zu entry: %s\n", i, a_strings->a_strings[i]);
  }
}

void print_array(const string_array * array)
{
  for (size_t i = 0; i < array->size; ++i)
  {
    printf("#%zu entry: %s\n", i, array->string_array[i]);
  }
}

string_array get_zero_initialized_string_array()
{
  static string_array string_array = {NULL, 0};
  return string_array;
}

#define type_idx(T) _Generic( (T), char: 1, int: 2, long: 3, default: 0)

int main(void) {

  AStrings a = {NULL, 3};
  a.a_strings = malloc(a.a_size * sizeof(char*));
  a.a_strings[0] = strdup("Hello");
  a.a_strings[1] = strdup("World");
  a.a_strings[2] = strdup("!");

  printf("%zu\n", type_idx((char)'3'));

  return 0;
}
