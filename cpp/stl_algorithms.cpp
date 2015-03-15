#include <algorithm>
#include <numeric>

#include <vector>

#include <iostream>

using namespace std;


// namespace for helper functions (lamdas in c11)
namespace helpers
{

bool isEven( int value )
{
  return value %2 == 0;
}

int countEven( int a, int b )
{
  return isEven(a) ? a+b : b;
}

}


template<typename T>
void printVector( const vector<T>& vec )
{
  cerr << "vector values:";

  typedef typename vector<T>::const_iterator ConstIter;
  for (ConstIter it = vec.begin(); it < vec.end(); ++it )
  {
    cerr << "\t" << *it ;
  }
  cerr << endl;
}

int main( int argc, char** argv )
{
  cerr << "hello algorithm world " << endl;

  vector<int> a;
  a.resize( 10 );

  // std::fill algorithm for initializing a container
  fill( a.begin(), a.end(), 0 );
  printVector<int>( a );

  // std::fill algorithm for partially setting values
  fill( a.begin()+3, a.begin()+5, 1 );
  fill( a.begin()+5, a.begin()+7, 2 );
  printVector<int>( a );

  int sum_all = accumulate( a.begin(), a.end(), 0 );
  cerr << "sum of all values\t" << sum_all << endl;

  int sum_even = accumulate( a.begin(), a.end(), 0, helpers::countEven );
  cerr << "sum of even values\t" << sum_even << endl;

  // count if even
  int count_even = count_if( a.begin(), a.end(), helpers::isEven );
  cerr << "number of even values\t" << count_even << endl;

  // sort
  cerr << "sorting vector ..." << endl;
  sort( a.begin(), a.end() );
  printVector<int>( a );

  // rotate
  cerr << "rotating vector ..." << endl;
  vector<int>::iterator pivot = a.begin()+a.size()/2;
  *pivot = 5;
  rotate( a.begin(), pivot, a.end() );
  printVector<int>( a );

  // partition
  cerr << "partitioning vector ..." << endl;
  vector<int>::iterator bound;
  bound = stable_partition( a.begin(), a.end(), helpers::isEven );
  printVector<int>( a );
  size_t group_one = bound - a.begin();
  cerr << "length of group one " << group_one << endl;
  cerr << "pivot for partitioning " << *bound << endl;
  return 0;
}
