#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <tr1/unordered_map>
#include <bitset>

#include <algorithm>

struct IndexCount
{
  int count;
  int index;
};

int firstNonRepeatingChar( std::string s )
{
  if ( s.empty() )
  {
    return -1;
  }
  if ( s.size() == 1 )
  {
    return 0;
  }

  std::tr1::unordered_map<char, IndexCount> map;
  map.rehash(s.size());
  typedef std::tr1::unordered_map<char, IndexCount>::iterator iter_t;

  for (size_t i=0; i<s.size(); ++i)
  {
    if (map.find(s[i]) == map.end())
    {
      IndexCount idx;
      idx.count = 1;
      idx.index = i;
      map[s[i]] = idx;
    }
    else
    {
      map[s[i]].count +=1;
    }
  }

  int lowest_index = map.begin()->second.index;
  for (iter_t it=map.begin(); it!=map.end(); ++it)
  {
    if ( it->second.count == 1 && it->second.index < lowest_index )
    {
      lowest_index = it->second.index;
    }
  }
  return lowest_index;
}



template<typename T>
T* rotateWithCopy( T s[], size_t k, size_t length )
{
  T* s2 = new T[length+1];
  memcpy(s2, s+k, length-k);
  memcpy(s2+length-k, s, length-k);
  s2[length] = 0;
  return s2;
}

template<typename T>
T* reverse( T s[], int left, int right )
{
  while( left < right )
  {
    T tmp = s[left];
    s[left] = s[right];
    s[right] = tmp;
    left++;
    right--;
  }
  return s;
}

template<typename T>
T* rotateInPlace( T s[], int k, int length )
{
  std::cout << "rotate in place" << std::endl;
  int a = length - k;
  s = reverse<T>( s, 0, a-1 );
  reverse<T>( s, a, length-1 );
  reverse<T>( s, 0, length-1 );
  return s;
}

bool containsOnlyDigits( std::string s )
{
  const int low_range = static_cast<int>('0');
  const int high_range = static_cast<int>('9');

  for (size_t i=0; i<s.size(); ++i)
  {
    int x = static_cast<int>(s[i]);
    if (x< low_range || x>high_range)
    {
      return false;
    }
  }

  return true;
}

std::vector<std::string> getPermutations( std::string s )
{
  std::cout << "get permutations of " << s << " with size " << s.size() << std::endl;
  if (s.empty())
  {
    return std::vector<std::string>();
  }
  if (s.size() == 1)
  {
    return std::vector<std::string>(1, ""+s[0]);
  }
  if (s.size() == 2)
  {
    std::vector<std::string> vec;
    vec.reserve(2);
    vec.push_back( s );
    std::string swap(2, ' ');
    swap[0] = s[1];
    swap[1] = s[0];
    vec.push_back( swap );
    return vec;
  }

  std::vector<std::string> rec_vec = getPermutations( s.substr(1, s.size()-1) );
  std::cout << "found " << rec_vec.size() << "permutations" << std::endl;

  std::vector<std::string> permutations;
  for (size_t i=0; i<rec_vec.size(); ++i)
  {
    for( size_t j=0; j<rec_vec[0].size(); ++j)
    {
      int lhs = j - 0;
      int rhs = rec_vec[0].size() - j;
      std::string permutation_string = rec_vec[i].substr(0,lhs)+s[0]+rec_vec[i].substr(j,rhs);
      permutations.push_back(permutation_string);
    }
    permutations.push_back( rec_vec[i]+s[0] );
  }
  return permutations;
}

std::string unify( std::string s )
{
  std::sort( s.begin(), s.end() ); // n logn

  std::string output;
  output.reserve(s.size());

  for (std::string::iterator it=s.begin();it!=s.end(); ++it)
  {
    if ( *it != *(it-1) )
    {
      output.push_back(*(it));
    }
  }
  return output;
}

void unifyInPlace( std::string& s )
{
  if (s.empty() || s.size()==1)
  {
    return;
  }

  int tail =0;
  for (std::string::iterator it=s.begin()+1; it!=s.end();++it)
  {
    bool seen = false;
    for (size_t i=0; i<tail; ++i)
    {
      if (s[i] == *it)
      {
        std::cout << s[i] << " is already seen" << std::endl;
        seen = true;
        break;
      }
    }

    if (!seen)
    {
      s[tail] = *it;
      ++tail;
    }
  }
  s.resize(tail);
}

void unifyInPlace2( std::string& s )
{
  if (s.empty() || s.size()==1)
  {
    return;
  }

  long long hashmap = 0LL;
  for (size_t i=0; i<s.size(); ++i)
  {
    if ((hashmap & (1LL << (s[i]-'a')) )>0) //duplicate found
    {
      s[i] = 0;
    }
    else
    {
      hashmap |= (1LL << (s[i]-'a'));
    }
  }
}

int isSubstring( std::string s, std::string sub )
{
  if (s.size()<sub.size())
  {
    return -1;
  }
  if (s.size()==0 || sub.size()==0)
  {
    return -1;
  }

  for (int i=0;i<s.size();++i)
  {
    std::cerr << "processing " << s[i] << std::endl;
    bool isSub = true;
    for (int j=0;j<sub.size();++j)
    {
      if (s[i] != sub[j])
      {
        std::cerr << "index don't match" << std::endl;
        isSub = false;
        break;
      }
      else
      {
        ++i;
      }
    }
    if (isSub)
    {
      return i - sub.size();
    }
  }
  return -1;
}

std::string::const_iterator find( const std::string& s, char c )
{
  std::string::const_iterator res = s.end();
  for (std::string::const_iterator it=s.begin();it!=s.end();++it)
  {
    if (*it == c)
    {
      return it;
    }
  }
  return res;
}

int main()
{
  int a = static_cast<int>('a');
  std::cout << a << std::endl;
  int A = static_cast<int>('Z');
  std::cout << A << std::endl;

  std::string s = "swissiswonderful";
  int idx = firstNonRepeatingChar(s);
  std::cout << "first non reapting char in " << s << " = " << s[idx] << std::endl;

/*
  size_t k = 5;
  char ss[s.size()+1];
  strcpy( ss, s.c_str() );
  std::cout << "rotate " << s << " with k = " << k << ">> " << rotateWithCopy<char>( ss, 5, s.size() ) << std::endl;

  int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  //std::cout << "rotate int vec with k = " << k << " >> " << rotateWithCopy<int>( i, k, 10 )[0] << std::endl;
  int* i = rotateInPlace<int>( arr, k, 10 );
  for (size_t j=0; j<10; ++j)
  {
    std::cout << i[j] << " --> ";
  }
  std::cout << std::endl;
*/

  std::string only_digits = "13218373693216032160321";
  std::cout << only_digits << " contains only digits? " << (containsOnlyDigits(only_digits)?"true":"false") << std::endl;

  std::string mixed = "12312sadda321312312.31321321";
  std::cout << mixed << " contains only digits? " << (containsOnlyDigits(mixed)?"true":"false") << std::endl;

  std::vector<std::string> perms = getPermutations( "123" );
  for (size_t i=0;i<perms.size();++i)
  {
    std::cout << perms[i] << std::endl;
  }

  std::string dups = "aazqasdmjjiohyuHaabbbbaaaccccd";
  std::cout << "original string " << dups << std::endl;
  std::cout << "unified string " << unify(dups) << std::endl;
  unifyInPlace2(dups);
  std::cout << "unified string " << dups << std::endl;
  std::cout << "shutting down .." << std::endl;


  std::string s_long = "thisisasuperlongstring";
  std::string s_sub = "string";
  int isSub = isSubstring( s_long, s_sub );
  if (isSub != -1)
  {
    std::cerr << s_long << " does contain " << s_sub << " starting from idx " << isSub << std::endl;
  }
  std::string::const_iterator it = find( s_long, 's' );
  std::cerr << "found first occurance " << (it-s_long.begin()) << std::endl;

  return 0;
}
