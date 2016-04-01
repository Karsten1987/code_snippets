#include <stdio.h>
#include <iostream>
#include <vector>

struct A
{
  int a;
  int b;

  friend std::ostream& operator<< ( std::ostream& os, const A& a )
  {
    return os << "a: " << a.a << " b: " << a.b;
  }
};

template<typename T>
T add(T op1, T op2)
{
  return op1 + op2;
}

template<typename T>
T sub(T op1, T op2)
{
  return op1 - op2;
}

template<typename T>
T operate(T op1, T op2, T (*operation)(T,T))
{
  return (*operation)(op1, op2);
}

int doStuff( A* a )
{
  a->a += 1;
  a->b += 2;
}

int main()
{
  A first_struct;
  first_struct.a = 1;
  first_struct.b = 1;

  A second_struct;
  second_struct.a = 2;
  second_struct.b = 2;

  A* const first_pointer = &first_struct;
  const A* second_pointer = &second_struct;

  std::cerr << "first pointer: " << *first_pointer << std::endl;
  first_pointer->a = 100;
  second_pointer = first_pointer;
  first_pointer->a = 1;
  std::cerr << "second pointer: " << *second_pointer << std::endl;

  int* p = new int[10];
  for (int i=0;i<10;++i)
  {
    (p[i]) = i;
  }
  for (int i=0;i<10;++i)
  {
    std::cerr <<i << " " << &p[i] << std::endl;
  }

  auto s = 1.0f;
  std::cerr << "s = " << s << std::endl;

  int* a = new int;
  *a = 1;
  std::cerr << "a " << *a << std::endl;

  std::cerr << "adding 3 and 2 " << operate<int>(3,2, (&add<int>)) << std::endl;
  std::cerr << "subtracting 3 and 2 " << operate<int>(3,2, (&sub<int>)) << std::endl;

  std::vector<const float*> vec;
  float f1(1.0), f2(2.0), f3(3.0);
  vec.push_back(&f1);
  vec.push_back(&f2);
  vec.push_back(&f3);

  std::cerr << "float pointer0 :" << *vec[0] << std::endl;

  auto i = 1;
  auto& ri = i;
  auto* pi = &ri;

  auto** ppi = &pi;
  std::cout << "double deref " << **ppi << std::endl;

  i = 3;
  std::cout << "double deref after setting i to 3 " << **ppi << std::endl;

  *pi = 2;
  std::cout << "double deref after modif " << **ppi << std::endl;

  return 0;
}
