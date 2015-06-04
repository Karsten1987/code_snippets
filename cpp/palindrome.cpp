#include <iostream>
#include <string>

bool isPalidrome( std::string s )
{
  int lhs = 0;
  int rhs = s.size()-1;
  while ( lhs < rhs )
  {
    if ( s[lhs] != s[rhs] )
    {
      std::cerr << "clash in " << s[lhs] << " and " << s[rhs] << std::endl;
      return false;
    }
    lhs++;
    rhs--;
  }
  std::cerr << s << " is a palindrom " <<  std::endl;
  return true;
}

int main()
{

  const std::string& s = "racecar";
  isPalidrome( "racecar" );
  isPalidrome( "karsten" );

  return 0;
}
