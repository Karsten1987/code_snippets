#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>
#include <timing.h>

struct Item
{
  std::string name;
  long id;
};

template < typename T >
T getInstance( )
{
  T instance( 10 );
  return instance;
}

template <>
Item getInstance<Item> ( )
{
  Item item;
  item.name = "Name";
  item.id = 1;
  return item;
}

template <typename T>
void benchmark( const long& loop_size )
{
  long before = timing::getTime();
  std::vector< T > collection;
  for ( long i = 0; i < loop_size; ++i )
  {
    T item = getInstance< T >();
    collection.push_back( item );
  }
  long after = timing::getTime();
  std::cerr << "time for push back init:\t " << after - before << std::endl;

  before = timing::getTime();
  std::vector< T > collection_preinit;
  collection_preinit.resize( loop_size );
  for ( long i = 0; i < loop_size; ++i )
  {
    T item = getInstance< T >();
    collection_preinit[i] = item;
  }
  after = timing::getTime();
  std::cerr << "time for resize init:\t " << after - before << std::endl;

  before = timing::getTime();
  std::vector< T > collection_assign;
  for ( long i = 0; i < loop_size; ++i )
  {
    T item = collection[i];
    collection_assign.push_back( item );
  }
  after = timing::getTime();
  std::cerr << "time for push back copy:\t" << after - before << std::endl;

  before = timing::getTime();
  std::vector< T > collection_ref;
  for ( long i = 0; i < loop_size; ++i )
  {
    T& item = collection[i];
    collection_ref.push_back( item );
  }
  after = timing::getTime();
  std::cerr << "time for push back refereince:\t" << after - before << std::endl;

  before = timing::getTime();
  std::vector< T* > collection_ptr;
  typedef typename std::vector< T >::iterator iter_t;
  for (iter_t it = collection.begin(); it != collection.end(); ++it)
  {
    collection_ptr.push_back( &(*it) );
  }
  after = timing::getTime();
  std::cerr << "time for push back iterator:\t" << after - before << std::endl;
}

int main()
{
  long loop_size = 10000000;
  long before, after;

  std::cerr << "benchmarking structs" << std::endl;
  benchmark< Item >( loop_size );
  std::cerr << "*********************" << std::endl;
  std::cerr << "benchmarking int" << std::endl;
  benchmark< int > ( loop_size );
/*
  initialize the collection_struct where to copy from
*/
/*
  Struct values
*/


/*
  Integer values
*/
/*
  before = timing::getTime();
  std::vector< int > collection_int;
  for ( long i = 0; i < loop_size; ++i )
  {
    int integer = i;
    collection_int.push_back( integer );
  }
  after = timing::getTime();
  std::cerr << "init time for integer " << after - before << std::endl;

  before = timing::getTime();
  std::vector< int > collection_int_preint;
  collection_int_preint.resize( loop_size );
  for ( long i = 0; i < loop_size; ++i )
  {
    int integer = i;
    collection_int_preint[i] = integer;
  }
  after = timing::getTime();
  std::cerr << "init time for integer preinit" << after - before << std::endl;

  before = timing::getTime();
  std::vector< int > collection_int_assign;
  for ( long i = 0; i < loop_size; ++i )
  {
    int integer = collection_int[i];
    collection_int_assign.push_back( integer );
  }
  after = timing::getTime();
  std::cerr << "assignment int time" << after - before << std::endl;

  before = timing::getTime();
  std::vector< int > collection_int_ref;
  for ( long i = 0; i < loop_size; ++i )
  {
    int& integer = collection_int[i];
    collection_int_ref.push_back( integer );
  }
  after = timing::getTime();
  std::cerr << "reference int time " << after - before << std::endl;


  Float values

  before = timing::getTime();
  std::vector< float > collection_float;
  for ( long i = 0; i < loop_size; ++i )
  {
    float f = i;
    collection_float.push_back( f );
  }
  after = timing::getTime();
  std::cerr << "init time for float " << after - before << std::endl;

  before = timing::getTime();
  std::vector< float > collection_float_preint;
  collection_float_preint.resize( loop_size );
  for ( long i = 0; i < loop_size; ++i )
  {
    float f = i;
    collection_float_preint[i] = f;
  }
  after = timing::getTime();
  std::cerr << "init time for float preinit" << after - before << std::endl;

  before = timing::getTime();
  std::vector< float > collection_float_assign;
  for ( long i = 0; i < loop_size; ++i )
  {
    float f = collection_float[i];
    collection_float_assign.push_back( f );
  }
  after = timing::getTime();
  std::cerr << "assignment float time" << after - before << std::endl;

  before = timing::getTime();
  std::vector< float > collection_float_ref;
  for ( long i = 0; i < loop_size; ++i )
  {
    float& f = collection_float[i];
    collection_float_ref.push_back( f );
  }
  after = timing::getTime();
  std::cerr << "reference float time " << after - before << std::endl;

  Item& a = collection_struct[0];
  Item aa;
  aa.name = "item";
  aa.id = 1;

  int& i = collection_int[0];
  int ii = 10;

  float& f = collection_float[0];
  float ff = 10.0f;

  std::cerr << "size of struct&: " << sizeof(&a) << std::endl;
  std::cerr << "size of struct: " << sizeof(aa) << std::endl;
  std::cerr << "size of int&: " << sizeof(i) << std::endl;
  std::cerr << "size of int: " << sizeof(ii) << std::endl;
  std::cerr << "size of f&: " << sizeof(f) << std::endl;
  std::cerr << "size of f: " << sizeof(ff) << std::endl;
*/
  return 0;
}
