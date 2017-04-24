#include <iostream>
#include <algorithm>
#include <unordered_map>

bool isAnagram_sort( std::string s1, std::string s2 )
{
  if (s1.size() != s2.size())
  {
    return false;
  }

  std::sort( s1.begin(), s1.end() );
  std::sort( s2.begin(), s2.end() );

  for (size_t i=0; i<s1.size(); ++i)
  {
    if ( s1[i] != s2[i] )
    {
      return false;
    }
  }
  return true;
}

bool isAnagram_map( std::string s1, std::string s2 )
{
  if (s1.size() != s2.size()) {
    return false;
  }

  std::unordered_map<char, size_t> map_s1;

  for (auto i = 0; i < s1.size(); ++i)
  {
    if (map_s1.count(s1[i]) > 0) {
      ++map_s1[s1[i]];
    } else {
      map_s1.insert(std::pair<char, int>(s1[i], 1));
    }
  }

  for (auto i = 0; i < s2.size(); ++i)
  {
    if (map_s1.count(s2[i]) == 0) {
      return false;
    } else {
      --map_s1[s2[i]];
    }
  }

  for (auto it = map_s1.begin(); it != map_s1.end(); ++it)
  {
    if (it->second != 0) {
      return false;
    }
  }
  return true;
}

int main()
{
  std::string base_string = "abcd";
  std::string test_string = "ddbd";
  std::cerr << base_string << " and " << test_string << " are anagrams: " << std::boolalpha << isAnagram_map( base_string, test_string ) << std::endl;
  return 0;
}
