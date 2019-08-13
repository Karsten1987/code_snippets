#include <string>

size_t get_substring(const std::string & search_string, const std::string & sub_string)
{
  if (sub_string.size() == 0) {
    return 0;
  }
  if (sub_string.size() > search_string.size()) {
    return 0;
  }

  for (auto i = 0lu; i < search_string.size(); ++i) {
    auto j = 0lu;
    for (; j < sub_string.size(); ++j) {
      if (search_string[i+j] != sub_string[j]) {
        break;
      }
    }
    if (j == sub_string.size()) {
      return i;
    }
  }

  return 0u;
}
int main()
{
  std::string search_string = "karsten is a big hero";
  std::string sub_string = "hero";

  size_t index = get_substring(search_string, sub_string);
  printf("start index %zu [%c]\n", index, search_string[index]);
}
