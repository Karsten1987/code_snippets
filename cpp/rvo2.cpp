#include <iostream>

class C
{
  public:
  std::string s_;

  C( std::string s )
    : s_(std::move(s) )
  {
    std::cout << "A default constructor is made" << std::endl;
  }
};

C create_struct()
{
  C obj( "created struct");
  return obj;
}

int main()
{
  C obj = create_struct();
  return 0;
}
