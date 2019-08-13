#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

bool is_correct(const std::string & s)
{
  int check = 0;

  for (const auto & c : s) {
    if (c == '(') {
      ++check;
    } else {
      if (check == 0) {
        return false;
      }
      --check;
    }
  }

  return (check == 0);
}

std::vector<std::string> permutations(const std::string & s, std::unordered_set<std::string> & set)
{
  if (s.size() == 2) {
    return {std::string("") + s[0] + s[1], std::string("") + s[1] + s[0]};
  }

  std::vector<std::string> vec;

  std::vector<std::string> perms = permutations(s.substr(1), set);
  char front = s[0];
  for (auto & p : perms) {
    for (size_t i = 0; i < p.size(); ++i) {
      auto new_perm = p.substr(0, i) + front + p.substr(i);
      if (set.find(new_perm) == set.end()) {
        vec.push_back(new_perm);
        set.insert(new_perm);
      }
    }
  }

  return vec;
}

int main()
{
  std::string s = "()()()";
  std::unordered_set<std::string> set;
  auto perms = permutations(s, set);
  for (auto s : perms) {
    if (is_correct(s)) {
      std::cout << s << std::endl;
    }
  }
}
