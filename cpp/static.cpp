#include <iostream>


// begin file.h
namespace A
{
  // not declaration, it's a 'normal' const but static
  static float f;
  class A
  {
  public:
    // declaration
    // but does not reserver memory for this variable
    static const float f;
    static float g;

    float h;
  };

  // reserve memory for this class
  // doesn't care about any namespace here, only .so/.o files
  const float A::f = 0.2f;
}
// end file.h

// begin random.cpp
// globally reserver memory for f 
//const float A::A::f = 0.2f;
float A::A::g = 0.1f;
// end random.cpp


// file.cpp
float f;

int main()
{
  A::A a;
  A::A::g = 0.2f;
// definition in this compilation unit of class variable f
//const float A::A::f = 0.2f;
  std::cerr <<  A::A::f << std::endl;
  std::cerr <<  A::f << std::endl;
  return 0;
}
