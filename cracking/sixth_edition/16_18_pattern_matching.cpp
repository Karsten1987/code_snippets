#include <iostream>
#include <string>
#include <vector>

std::pair<std::string, std::string> get_tokens(const std::string & s, const std::string & pattern, size_t pattern_a_size, size_t pattern_b_size)
{
  std::string token1 = "";
  std::string token2 = "";

  token1 = s.substr(0, pattern_a_size);
  size_t index = token1.size() - 1;
  for (size_t i = 1; i < pattern.size(); ++i) {
    if (pattern[i] == 'b') {
      token2 = s.substr(index + 1, pattern_b_size);
      break;
    }
    index += pattern_a_size;
  }

  return {token1, token2};
}

bool is_equal(const std::string & s, std::string pattern)
{
  if (s.size() <= 1) {
    return false;
  }

  if (pattern[0] == 'b') {
    for (auto & c : pattern) {
      if (c == 'a') {
        c = 'b';
      } else {
        c = 'a';
      }
    }
  }

  auto count = [](const std::string & pattern, char c) -> size_t {
    size_t count = 0;
    for (char p : pattern) {
      if (p == c) { ++count; }
    }
    return count;
  };

  size_t count_a = count(pattern, 'a');
  printf("count of a %zu\n", count_a);
  size_t pattern_a_size = (s.size() + count_a) / (2 * count_a);
  printf("max size of a %zu\n", pattern_a_size);

  size_t count_b = pattern.size() - count_a;
  printf("count of b %zu\n", count_b);
  size_t pattern_b_size = (s.size() - (count_a * pattern_a_size)) / count_b;
  printf("max size of b %zu\n", pattern_b_size);

  auto tokens = get_tokens(s, pattern, pattern_a_size, pattern_b_size);
  std::cout << "token1 " << tokens.first << std::endl;
  std::cout << "token2 " << tokens.second << std::endl;

  std::string compare_string = "";
  for (size_t i = 0; i < pattern.size(); ++i) {
    if (pattern[i] == 'a') {
      compare_string += tokens.first;
    } else {
      compare_string += tokens.second;
    }
  }
  return (s == compare_string);
}

int main()
{
  std::string s = "gogocatcatgogocatcat";
  std::string pattern = "abab";
  //std::string pattern = "baba";

  bool equal = is_equal(s, pattern);
  std::cout << "is equal " << (equal ? "yes!" : "no!") << std::endl;
}
