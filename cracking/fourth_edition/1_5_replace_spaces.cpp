#include <string>

std::string replace_spaces(std::string & str)
{
  size_t space_count = 0u;
  std::for_each(str.begin(), str.end(), [&space_count](char c) {if (c == ' ') ++space_count;;});

  std::string return_str;
  return_str.reserve(str.size() + space_count * 2);  // 2 for two extra characters
  for (auto i = 0u; i < str.size(); ++i) {
    if (str[i] == ' ') {
      return_str.push_back('%');
      return_str.push_back('2');
      return_str.push_back('0');
    } else {
      return_str.push_back(str[i]);
    }
  }

  return return_str;
}

int main()
{
  std::string hello_world = "Hello WOrld, this is wonderful";
  printf("%s\n", replace_spaces(hello_world).c_str());
  return 0;
}
