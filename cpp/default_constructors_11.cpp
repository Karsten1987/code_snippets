#include <iostream>
#include <vector>

using namespace std;

struct MyStruct
{
  int* data;
  int* lo;
  int* hi;
  size_t size;

  MyStruct( size_t size, int value=0 )
    : size(size)
  {
    cout << "Constructor " << endl;
    data = new int[size];
    for (size_t i=0;i<size;i++)
    {
      data[i] = value;
    }
    lo = data;
    hi = data+size;
  }

  ~MyStruct()
  {
    cout << "Destructor " << endl;
    data = NULL;
    lo = NULL;
    hi = NULL;
    delete[] data;
    delete lo;
    delete hi;
  }

  MyStruct( const MyStruct& other )
    : size(other.size)
  {
    cout << "CopyConstructor " << endl;
    data = new int[other.size];
    lo = data;
    hi = data+size;
  }

  MyStruct( MyStruct&& other )
    : size(other.size)
  {
    cout << "Move Constructor " << endl;
    data = other.data;
    lo = other.lo;
    hi = other.hi;

    // reset other
    other.data = NULL;
    other.lo = NULL;
    other.hi = NULL;
    delete[] other.data;
  }

};

namespace global{
  static vector<MyStruct> all_structs;
}

template<class T>
void printStruct( T&& s )
{
  for (size_t i=0; i<s.size; i++)
  {
    cout << s.data[i] << " ";
  }
  cout << endl;
}


void storeStruct( MyStruct&& s )
{
  global::all_structs.push_back( std::forward<MyStruct>(s));
}

void storeStructRef( const MyStruct& s )
{
}

int main()
{
  MyStruct a(10, 2);
  cout << "first value of A: " << *(a.lo) << endl;

  MyStruct b(a);
  cout << "first value of B: " << *(b.lo) << endl;

  *(a.lo) = 10;
  cout << "changing value of A: " << *(a.lo) << endl;
  cout << "first value of B: " << *(b.lo) << endl;

  cout << "****************************" << endl;
  printStruct( a );
  printStruct( MyStruct(5,1) );
  printStruct( std::move(b) );

  cout << "****************************" << endl;
  storeStructRef( a );
  //MyStruct&& s = MyStruct(4,1);
  //storeStruct( std::forward<MyStruct>(s) );
  storeStruct( std::move(a) );


  return 0;
}
