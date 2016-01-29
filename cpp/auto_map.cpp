// idea from here:
// https://www.youtube.com/watch?v=J-tA17slViE
//

#include <map>
#include <iostream>

int main()
{
  std::map<std::string, int> m;
  m.insert(std::make_pair("eins", 1));
  m.insert(std::make_pair("zwei", 2));
  m.insert(std::make_pair("drei", 3));
  m.insert(std::make_pair("vier", 4));

  for (std::pair<const std::string, int>& p : m)
  {
    p.second = 10;
  }

  // very bad wrong loop because it makes a copy
  // diff between const std::pair<std::string> and std::pair<const string>
  // this loop copies all the map content into a temporary
  for (const std::pair<std::string, int>& p : m)
  {
    p.second = 10;
  }
  for (const auto& p : m)
  {
    std::cout << "key: " << p.first << "\tvalue: " << p.second << std::endl;
  }

  return 0;
}

