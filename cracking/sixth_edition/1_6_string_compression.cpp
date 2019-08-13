#include <string>

std::string compress_string(const std::string & s)
{
  if (s.size() <= 2) {
    return s;
  }

  std::string compressed_string;
  size_t counter = 1ul;
  for (auto i = 1ul; i < s.size(); ++i) {
    if (s[i] != s[i-1]) {
      compressed_string += s[i-1] + std::to_string(counter);
      counter = 1ul;
    } else {
      ++counter;
    }
  }
  compressed_string += s[s.size() - 1] + std::to_string(counter);

  if (compressed_string.size() < s.size()) {
:xa
:xa
:qa
q
    return compressed_string;
  }
  return s;
}

int main()
{
  std::string s = "aaaabbcccaaaeeedddbbb";
  printf("the compressed string of %s is %s\n", s.c_str(), compress_string(s).c_str());
  return 0;
}
