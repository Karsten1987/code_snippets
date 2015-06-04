#include <iostream>
#include <algorithm>

bool isAnagram( std::string s1, std::string s2 )
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

int main()
{

  std::cerr << " is anagram " << isAnagram( "abcd", "dcba" ) << std::endl;
  return 0;
}
