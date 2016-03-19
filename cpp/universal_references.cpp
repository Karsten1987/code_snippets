#include <iostream>
#include <vector>
using namespace std;


template<class T>
class MyClass
{
public:

  /*
  template<class value_t>
  MyClass& operator()( value_t&& v)
  {
    vec_.emplace_back(std::forward<value_t>(v));
    return *this;
  }
  */
  MyClass& operator()( T&& i )
  {
    std::cout << "emplacing" << std::endl;
    vec_.emplace_back(i);
    return *this;
  }
  
  MyClass& operator()( const T& i)
  {
    std::cout << "pushing back" << std::endl;
    vec_.push_back(i);
    return *this;
  }
  
  std::vector<T> vec_;
};

int main() {
  // your code goes here
  
  const int k = 13;
  MyClass<int> mc;
  mc(1)(2)(3)(4)(k);
  
  for (auto i=mc.vec_.begin(); i!=mc.vec_.end(); ++i)
  {
    std::cout << *i << " ";
  }
  std::cout << k << std::endl;  
  return 0;
}
