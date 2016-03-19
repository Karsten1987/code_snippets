#include <iostream>
class Foo
{
public:
  // single parameter constructor, can be used as an implicit conversion
  explicit Foo (int foo) : m_foo (foo) 
  {
  }

  int GetFoo () { return m_foo; }

private:
  int m_foo;
};

void DoBar (Foo foo)
{
  int i = foo.GetFoo ();
}

int main ()
{
  DoBar (42);
  return 0;
}

