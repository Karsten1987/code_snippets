#include <iostream>
#include <memory>
#include <vector>

struct MyData
{
  MyData(int i_):
    i(i_)
  {};
  int i;
};

auto mydata_deleter = [](MyData* md)
{
  std::cout << "deleting " << md->i << std::endl;
  delete md;
};

class MyClass
{
public:

  MyClass( int i ):
    ptr_(new MyData(i), mydata_deleter)
  {
  };

  //MyClass( const MyClass& other ):
  //  ptr_(new MyData(*other.ptr_->i))
  //{}

  std::unique_ptr<MyData, decltype(mydata_deleter)> ptr_;
};

template <class T>
void doStuff( std::unique_ptr<T> ptr )
{
  std::cout << "I totally have ownership over " << *ptr << std::endl;
}

template <>
void doStuff<int>( std::unique_ptr<int> ptr )
{
  std::cout << "I totally have ownership over integer " << *ptr << std::endl;
}

int main()
{

  //std::vector<MyClass> vec_mc = { MyClass(1), MyClass(2), MyClass(3) }; // fails!
  std::vector<MyClass> vec_mc;

  MyClass mc(13);
  vec_mc.emplace_back(MyClass(13));
  std::cout << "mc has value " << mc.ptr_->i << std::endl;

  std::unique_ptr<int> ptr(new int(15));
  doStuff(std::move(ptr));

  return 0;
}
