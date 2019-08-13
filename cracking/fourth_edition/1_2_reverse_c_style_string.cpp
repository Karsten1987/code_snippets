#include <string>

char * reverse(const char * string)
{
  char * string_reversed = strdup(string);
  auto idx = 0u;
  for (int i = strlen(string) - 1; i >= 0; i--, idx++) {
    string_reversed[idx] = string[i];
  }
  return string_reversed;
}

void reverse_inplace(char * string)
{
  size_t lhs = 0u;
  size_t rhs = strlen(string) - 1;

  while (rhs > lhs) {
    char tmp = string[lhs];
    string[lhs] = string[rhs];
    string[rhs] = tmp;
    ++lhs;
    --rhs;
  }
}

int main()
{
  const char * string = "abcdef";
  char * string_reversed = reverse(string);
  printf("%s reversed is %s\n", string, string_reversed);
  reverse_inplace(string_reversed);
  printf("%s reversed and back is %s\n", string, string_reversed);
  return 0;
}
