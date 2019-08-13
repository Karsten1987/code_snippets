#include <string>
#include <iostream>

void reverse(char * string)
{
  auto length = strlen(string);
  auto lhs = 0lu;
  auto rhs = length - 1;
  while (lhs < rhs) {
    auto tmp = string[lhs];
    string[lhs] = string[rhs];
    string[rhs] = tmp;

    ++lhs;
    --rhs;
  }
}

int main()
{
  std::string stdstring = "Hello World";
  char * string = strdup(stdstring.c_str());
  reverse(string);

  printf("the inverse of %s is %s\n", stdstring.c_str(), string);
}
