#include <iostream>
#include <sstream>

struct X
{
  X( int i ): i_(i)
  {}

  operator int() const
  {
    return i_;
  }

  operator float() const
  {
    return float(i_);
  }

  operator std::string() const
  {
    return static_cast<std::ostringstream*>( &(std::ostringstream() << i_) )->str();
  }

  int i_;
};

int main()
{
  X x(123);
  int i = static_cast<int>(x);
  std::cout << "received an int " << i << std::endl;

  float f = static_cast<float>(x);
  std::cout << "received a float " << f << std::endl;

  std::string s = static_cast<std::string>(x);
  std::cout << "received a string " << s << std::endl;


  return 0;
}
