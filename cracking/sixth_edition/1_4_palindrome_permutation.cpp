#include <string>
#include <vector>

bool check_for_palindrome(const std::string & s)
{
  if (s.size() < 1) {
    return true;
  }

  auto table = 0ull;

  for (auto i = 0u; i < s.size(); ++i) {
    table ^= (1 << (static_cast<unsigned long long>(s[i]) - 97ull));
  }

  // check that only one bit is set
  return (table & (table - 1)) == 0;

  // std::vector<size_t> table(256, 0ul);
  // for (auto i = 0u; i < s.size(); ++i) {
  //   // filter out spaces
  //   table[static_cast<size_t>(s[i])]++;
  // }

  // bool is_odd = true;
  // if (s.size() % 2 == 0) {
  //   is_odd = false;
  // }

  // bool found_odd = is_odd ? false : true;
  // for (auto i = 0u; i < s.size(); ++i) {
  //   if (table[static_cast<size_t>(s[i])] % 2 != 0) {
  //     if (!found_odd) {
  //       found_odd = true;
  //     } else {
  //       return false;
  //     }
  //   }
  // }
  // return true;
}

int main()
{
  std::string s = "tactcoac";
  bool is_palindrome = check_for_palindrome(s);

  printf("%s is %sa palindrome\n", s.c_str(), is_palindrome ? "" : "not ");
}
