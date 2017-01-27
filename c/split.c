#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct string_array_t
{
  size_t size;
  char ** data;
} string_array_t;

string_array_t
split(const char * string, char delimiter)
{
  if (!string || strlen(string) == 0)
  {
    string_array_t empty_array = {0, NULL};
    return empty_array;
  }

  size_t offset = 0;
  if (string[strlen(string)-1] == delimiter)
    offset = 1;

  string_array_t tokens;
  tokens.size = 1;
  for (size_t i = 0; i < strlen(string) - offset; ++i)
  {
    if (string[i] == delimiter)
    {
      ++tokens.size;
    }
  }
  tokens.data = malloc(tokens.size * sizeof(char *));

  size_t token_counter = 0;
  size_t lhs = 0;
  size_t rhs = 0;
  for (; rhs < strlen(string) - offset; ++rhs)
  {
    if (string[rhs] == delimiter)
    {
      if (rhs-lhs > 1)
      {
        tokens.data[token_counter] = malloc((rhs - lhs + 1) * sizeof(char));
        snprintf(tokens.data[token_counter], (rhs - lhs + 1), "%s", string+lhs);
        ++token_counter;
        lhs = rhs;
      } else {
        printf("neighbouring delimiter found\n");
        free(tokens.data[--tokens.size -1]);
        tokens.data[tokens.size -1] = 0;
        ++lhs;
        ++rhs;
      }
    }
  }
  tokens.data[token_counter] = malloc((rhs - lhs + 1) * sizeof(char));
  snprintf(tokens.data[token_counter], (rhs - lhs + 1), "%s", string+lhs);
  return tokens;
}

void test(const char * test_string)
{
  string_array_t tokens = split(test_string, '/');
  printf("Found %zu tokens\n", tokens.size);
  for (size_t i = 0; i < tokens.size; ++i)
  {
    printf("%s\n", tokens.data[i]);
  }
}

int main()
{
  test("hello/world//namespace/");
  test("hello/world/namespace");
  test("");
  test("//");
  test(NULL);


  return 0;
}
