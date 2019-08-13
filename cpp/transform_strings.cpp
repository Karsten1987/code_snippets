#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

enum class Operations : std::uint8_t
{
  REMOVE = 0,
  INSERT = 1,
  REPLACE = 2,
};

int minimal_operations(
  std::string s1, std::string s2, std::unordered_map<std::string, int> & memo)
{
  auto lookup = memo.find(s1 + s2);
  if (lookup != memo.end()) {
    return lookup->second;
  }

  if (s1.empty()) {
    return s2.size();
  }
  if (s2.empty()) {
    return s1.size();
  }

  if (s1[s1.size() - 1] == s2[s2.size() - 1]) {
    return minimal_operations(s1.substr(0, s1.size() - 1), s2.substr(0, s2.size() -1), memo);
  }

  // remove
  auto removed_s1 = s1.substr(0, s1.size() - 1);
  auto removed_minimal = minimal_operations(removed_s1, s2, memo);

  // insert
  auto inserted_s1 = s1 + s2[s2.size() -1];
  auto inserted_minimal = minimal_operations(inserted_s1, s2, memo);

  // replace
  auto replaced_s1 = s1.substr(0, s1.size() - 1) + s2[s2.size() - 1];
  auto replaced_minimal = minimal_operations(replaced_s1, s2, memo);

  auto minimal = removed_minimal;
  Operations minimal_action = Operations::REMOVE;

  if (inserted_minimal < minimal) {
    minimal = inserted_minimal;
    minimal_action = Operations::INSERT;
  }
  if (replaced_minimal < minimal) {
    minimal = replaced_minimal;
    minimal_action = Operations::REPLACE;
  }

  memo[s1 + s2] = 1 + minimal;
  return 1 + minimal;
}

int main()
{
  std::string s1 = "sunday";
  std::string s2 = "saturday";

  std::unordered_map<std::string, int> memo;
  auto val = minimal_operations(s1, s2, memo);
  std::cout << "ops needed " << val << std::endl;

}
