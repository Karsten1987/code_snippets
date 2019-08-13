#include <string>

bool is_anagram(const std::string & str1, const std::string & str2)
{
  if (str1.size() != str2.size()) {
    return false;
  }

  auto sum1 = 0u;
  std::for_each(str1.begin(), str1.end(), [&sum1] (char c) {sum1 += static_cast<int>(c);});
  auto sum2 = 0u;
  std::for_each(str2.begin(), str2.end(), [&sum2] (char c) {sum2 += static_cast<int>(c);});

  printf("%s = %u\n", str1.c_str(), sum1);
  printf("%s = %u\n", str2.c_str(), sum2);
  return sum1 == sum2;
}

int main()
{
  std::string str1 = "iceman123";
  std::string str2 = "cinema321";
  printf("%s and %s are %s\n", str1.c_str(), str2.c_str(), is_anagram(str1, str2) ? "anagrams" : "not anagrams");
  return 0;
}
