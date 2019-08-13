#include <string>

bool check_for_one_away(const std::string & s1, const std::string & s2)
{
  if (s1.size() == 0 && s2.size() == 0) {
    return true;
  }

  int difference = static_cast<int>(s2.size()) - static_cast<int>(s1.size());
  if (std::abs(difference) > 1) {
    return false;
  }
  // check for insertion
  if (difference > 0) {
    bool joker_used = false;
    auto idx_s1 = 0u;
    auto idx_s2 = 0u;
    for (; idx_s2 < s2.size(); ++idx_s2) {
      if (s1[idx_s1] == s2[idx_s2]) {
        ++idx_s1;
      } else {
        if (joker_used) {
          return false;
        }
        joker_used = true;
      }
    }
    return true;
  }
  // check for removal
  if (difference < 0) {
    bool joker_used = false;
    auto idx_s1 = 0u;
    auto idx_s2 = 0u;
    for (; idx_s1 < s1.size(); ++idx_s1) {
      if (s1[idx_s1] == s2[idx_s2]) {
        ++idx_s2;
      } else {
        if (joker_used) {
          return false;
        }
        joker_used = true;
      }
    }
    return true;
  }
  // check for modification
  if (difference == 0) {
    bool joker_used = false;
    auto idx_s1 = 0u;
    auto idx_s2 = 0u;
    for (; idx_s1 < s1.size(); ++idx_s1) {
      if (s1[idx_s1] != s2[idx_s2]) {
        if (joker_used) {
          return false;
        } else {
          joker_used = true;
        }
      }
      ++idx_s2;
    }
    return true;
  }

  return false;
}

int main()
{
  std::string s1 = "pale";
  std::string s2 = "bale";

  bool is_one_away = check_for_one_away(s1, s2);
  printf("%s and %s have %s differences\n", s1.c_str(), s2.c_str(), is_one_away ? "less than one" : "more than one");
  return 0;
}
