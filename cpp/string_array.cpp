#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <tr1/unordered_map>

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

  std::tr1::unordered_map<std::string, int> map;
  map.rehash(100);
  typedef std::tr1::unordered_map<std::string, int>::iterator iter_t;

  for (size_t i=0; i<s.size(); ++i)
  {
    std::string si(1, s[i]);
    map[si] +=1;
    std::cout << "new value for " << si << " " << map[si] << std::endl;
  }

  // reversing since tr1 balbal
  int idx = 0;
  std::string c;
  for (iter_t it=map.begin(); it!=map.end(); ++it)
  {
    std::cout << "probing it " << it->first <<  " with count " << it->second << std::endl;
    if (it->second == 1)
    {
      idx = it->second;
      c = it->first;
    }
  }
  std::cout << "first no repit " << c << std::endl;
  return idx;
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
  std::cout << "given left and right " << left << " " << right << std::endl;
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
  std::cout << " length a " << a << std::endl;
  s = reverse<T>( s, 0, a-1 );
  reverse<T>( s, a, length-1 );
  reverse<T>( s, 0, length-1 );
  return s;
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


  size_t k = 5;
  std::cout << "rotate HelloWorld with k = " << k << ">> " << rotateWithCopy<char>( "HelloAWorld", 5, 11 ) << std::endl;

  int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  //std::cout << "rotate int vec with k = " << k << " >> " << rotateWithCopy<int>( i, k, 10 )[0] << std::endl;
  int* i = rotateInPlace<int>( arr, k, 10 );
  for (size_t j=0; j<10; ++j)
  {
    std::cout << i[j] << " --> ";
  }
  std::cout << std::endl;



  return 0;
}
