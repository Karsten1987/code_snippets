#include <iostream>

#include <vector>

#include <tr1/unordered_map>
#include <unordered_map>
#include <boost/unordered_map.hpp>

template<typename Map>
void countChar( const std::string& s, Map& map )
{
  if ( (int x =1) != 0 )
  {
    std::cerr << "works" << std::endl;
  }
  for (size_t i=0;i<s.size();++i)
  {
    map[ s[i] ] +=1;
  }
}

template<typename Map>
void printMap( const Map& map )
{
  typedef typename Map::const_iterator iter_t;
  for (iter_t it=map.begin(); it!=map.end(); ++it)
  {
    std::cerr << "key in map " << it->first << std::endl;
  }
  std::cerr << "*********" << std::endl;
}

template<typename Map>
int getFirstNonRepeatedChar( const std::string& s, Map& map )
{
  for (size_t i=0; i<s.size(); ++i)
  {
    if (map[s[i]] == 1)
    {
      return i;
    }
  }
  return -1;
}

int main()
{

  const std::string& s = "swissiswonderful";

  typedef std::tr1::unordered_map<char, int> tr1_map_t;
  tr1_map_t tr1_map;
  countChar<tr1_map_t>( s, tr1_map );
  printMap<tr1_map_t>( tr1_map );
  std::cerr << "first non repeat char " << s[getFirstNonRepeatedChar(s,tr1_map)] << std::endl;

  typedef std::unordered_map<char, int> std_map_t;
  std_map_t std_map;
  countChar<std_map_t>( s, std_map );
  printMap<std_map_t>( std_map );
  std::cerr << "first non repeat char " << s[getFirstNonRepeatedChar(s, std_map)] << std::endl;

  typedef boost::unordered_map<char, int> boost_map_t;
  boost_map_t boost_map;
  countChar<boost_map_t>( s, boost_map );
  printMap<boost_map_t>( boost_map );
  std::cerr << "first non repeat char " << s[getFirstNonRepeatedChar(s, boost_map)] << std::endl;


  return 0;
}
