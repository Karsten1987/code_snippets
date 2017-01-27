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

  // does it start with a delmiter?
  size_t lhs_offset = 0;
  if (string[0] == delimiter)
    lhs_offset = 1;

  // does it end with a delimiter?
  size_t rhs_offset = 0;
  if (string[strlen(string)-1] == delimiter)
    rhs_offset = 1;

  string_array_t tokens;
  tokens.size = 1;
  for (size_t i = lhs_offset; i < strlen(string) - rhs_offset; ++i)
  {
    if (string[i] == delimiter)
    {
      ++tokens.size;
    }
  }
  tokens.data = malloc(tokens.size * sizeof(char *));

  size_t token_counter = 0;
  int lhs = 0 + lhs_offset;
  int rhs = 0 + lhs_offset;
  for (; rhs < strlen(string) - rhs_offset; ++rhs)
  {
    if (string[rhs] == delimiter)
    {
      if (rhs - lhs < 1)
      {
        --tokens.size;
        free(tokens.data[tokens.size]);
        tokens.data[tokens.size] = NULL;
      } else {
        tokens.data[token_counter] = malloc((rhs - lhs + 2) * sizeof(char));
        snprintf(tokens.data[token_counter], (rhs - lhs + 1), "%s", string + lhs);
        ++token_counter;
      }
      lhs = rhs;
      ++lhs;
    }
  }
  if (rhs - lhs < 1)
  {
    --tokens.size;
    free(tokens.data[tokens.size]);
    tokens.data[tokens.size] = NULL;
  } else {
    tokens.data[token_counter] = malloc((rhs - lhs + 2) * sizeof(char));
    snprintf(tokens.data[token_counter], (rhs - lhs + 1), "%s", string + lhs);
  }
  return tokens;
}

void test(const char * test_string)
{
  string_array_t tokens = split(test_string, '/');
  printf("Found %zu tokens\n", tokens.size);
  for (size_t i = 0; i < tokens.size; ++i)
  {
    printf("#%zu: %s\n", i, tokens.data[i]);
  }
}

int main()
{
  test("hello/world/namespace/");
  test("hello/world/namespace");
  test("/hello/world/namespace");
  test("/hello/world/namespace/");
  test("/hello//world/namespace//");
  test("");
  test("//");
  test(NULL);


  return 0;
}
