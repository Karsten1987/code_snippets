#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

void print_vector(const std::vector<std::string> & vec)
{
  for (auto & el : vec) {
    std::cout << "[" << el << "]";
  }
  std::cout << std::endl;
}

void subsequences(std::string s, std::vector<std::string> & vec)
{
  if (s.length() == 1) {
    vec.push_back(s);
    return;
  }

  subsequences(s.substr(1), vec);
  size_t vec_size = vec.size();
  for (auto i = 0lu; i < vec_size; ++i) {
    vec.push_back(s[0] + vec[i]);
  }
  vec.push_back(s.substr(0,1));
}

std::vector<std::string> subsequences(std::string s)
{
  std::vector<std::string> vec;
  vec.reserve(pow(2, s.length()) - 1);
  subsequences(s, vec);
  return vec;
}

int lcs(
  std::string s1, std::string s2,
  std::unordered_map<std::string, int> & memo)
{
  if (s1.empty() || s2.empty()) {
    return 0;
  }

  auto memo_lcs = memo.find(s1 + s2);
  if (memo_lcs != memo.end()) {
    return memo_lcs->second;
  }

  auto sub1 = s1.substr(0, s1.size() -1);
  auto sub2 = s2.substr(0, s2.size() -1);
  if (s1[s1.size() -1] == s2[s2.size() -1]) {
    auto value =  1 + lcs(sub1, sub2, memo);
    memo[s1 + s2] = value;
    return value;
  } else {
    auto value = std::max(lcs(s1, sub2, memo), lcs(sub1, s2, memo));
    memo[s1 +s2] = value;
    return value;
  }
}

int main()
{
  std::string s1 = "ABCDGH";
  std::string s2 = "AEDFHR";
  std::unordered_map<std::string, int> memo;
  std::cout << "max common length " << lcs(s1, s2, memo) << std::endl;
}
