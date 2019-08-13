#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> get_permuations(const std::string & s)
{
  std::vector<std::string> permuations;
  if (s.size() == 2) {
    permuations.push_back(std::string("") + s[0] + s[1]);
    permuations.push_back(std::string("") + s[1] + s[0]);
    return permuations;
  }

  auto sub_perm = get_permuations(s.substr(1));
  for (const auto & p : sub_perm) {
    for (size_t i = 0; i <= p.size(); ++i) {
      std::string sub_p = p.substr(0, i) + s[0] + p.substr(i);
      permuations.push_back(sub_p);
    }
  }

  return permuations;
}

int main()
{
  //std::string s = "hello_world";
  std::string s = "abcd";
  auto permuations = get_permuations(s);
  std::cout << "size of permutaitons " << permuations.size() << std::endl;
  //for (const auto & p : permuations) {
  //  std::cout << p << std::endl;
  //}

  return 0;
}
