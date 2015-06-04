#include <iostream>

using namespace std;

struct S
{
  S( double dd )
    :d(dd)
  {}

  double d;
};

class A
{
public:
  A( double d )
  {
    std::cout << "struct value initialized" << std::endl;
    s_ = new S(d);
  }

  A( const A& other )
  {
    std::cout << "struct value copied" << std::endl;
    s_ = new S( other.s_->d );
  }

  A& operator=( const A& other )
  {
    std::cout << "struct assigned" << std::endl;
    s_ = new S( other.s_->d );
    return *this;
  }

  ~A()
  {
    std::cout << "strcut value deleted" << std::endl;
    delete s_;
    s_ = NULL;
  }

  double getD()
  {
    return s_->d;
  }

private:
  S* s_;
};

A createOne()
{
  double d = 6;
  A a1( d );
  return a1;
}

A createCopy()
{
  double d = 6;
  A a1( d );
  A a2(a1);
  return a2;
}

A createAssignment( )
{
  A a1(123);
  A a2(312);
  a2 = a1;
  return a2;
}

int main()
{
  A a1 = createCopy();
  cout << "a1 says " << a1.getD() << endl;

  A a2 = createAssignment();
  cout << "a2 says " << a2.getD() << endl;

  // your code goes here
  return 0;
}
