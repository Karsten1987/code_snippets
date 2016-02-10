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


int main()
{

  std::vector<MyClass> vec_mc = { MyClass(1), MyClass(2), MyClass(3) };

  MyClass mc(13);
  vec_mc.emplace_back(MyClass(13));
  std::cout << "mc has value " << mc.ptr_->i << std::endl;
  return 0;
}
