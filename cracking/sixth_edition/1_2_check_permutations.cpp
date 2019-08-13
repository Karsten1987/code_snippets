#include <string>
#include <unordered_map>
#include <vector>

bool is_permutation(const std::string & s1, const std::string & s2)
{
  if (s1.size() != s2.size()) {
    return false;
  }

  std::vector<size_t> table(256, 0u);
  for (auto s : s1) {
    table[static_cast<size_t>(s)]++;
  }

  for (auto s : s2) {
    auto & key_count = table[static_cast<size_t>(s)];
    if (key_count == 0) {
      return false;
    }
    --key_count;
  }

  return true;
}

int main()
{
  std::string s1 = "cinema1";
  std::string s2 = "iceman1";

  bool is_perm = is_permutation(s1, s2);
  printf("is-perm %s\n", is_perm ? "true" : "false");
  return 0;
}
