#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>

template <class T1>
class OuterClass
{
public:
  template <class T2>
  class InnerClass
  {
    public:
    void doStuff()
    {
      T1* t1 = new T1();
      T2* t2 = new T2();
      std::cout << "t1 " << *t1 << std::endl;
      std::cout << "t2 " << *t2 << std::endl;
    }
  };
};

// would be in a header
template <class T>
class MyTemplateClass
{
public:

  MyTemplateClass():
    my_t()
  {
  }

  const T& getT() const
  {
    return my_t;
  }


private:

  T my_t;
};

// implementation file
template <class T>
std::ostream& operator<< (std::ostream& os, MyTemplateClass<T> mc)
{
  os << "MyClassValue: "<< mc.getT();
  return os;
}

template <>
const std::string& MyTemplateClass<std::string>::getT() const
{
  std::cout << "whoot" << std::endl;
  return my_t;
}

struct A
{
  std::string a;
};

struct B
{
  int i;
};

struct C
{
  double d;
};

template<class T>
struct is_awesome : std::integral_constant<bool, std::is_same<B, T>::value
                                                || std::is_same<C, T>::value>
{
};


template<typename T, typename std::enable_if<is_awesome<T>::value>::type* = nullptr>
void doStuff( const T& t )
{
  std::cout << "I am awesome " << typeid(t).name() << std::endl;
}


template<typename T, typename std::enable_if<!is_awesome<T>::value>::type* = nullptr>
void doStuff( const T& t )
{
  std::cout << "I am normal " << typeid(t).name() << std::endl;
}

//template <class T, int Row, int Col>
//void doStuff( const T& t )
//{
//  std::cout << "doing stuff with double " << t << std::endl;
//}


template<typename T>
void hitMe( T t )
{
  std::cout << "General hitme for T " << t << std::endl;
}

template<>
void hitMe<long>( long l )
{
  std::cout << "Specialization for long " << l << std::endl;
}

void hitMe( long l )
{
  std::cout << "Just a normal function for long " << l << std::endl;
}

class TopLevelNode
{
  virtual void
  do_stuff() = 0;
};

template<class T>
class MyNode : public TopLevelNode
{
public:
  using type = T;

  // template<typename std::enable_if<!std::is_same<T, int>::value, T>::type * = nullptr>
  void do_stuff() override
  {
  }
};

int main()
{
  hitMe(213421);
  hitMe(21421432L);

  MyTemplateClass<int> my_int;
  MyTemplateClass<std::string> my_string;

  std::cout << "my_int says " << my_int.getT() << std::endl;
  std::cout << "my_string says " << my_string.getT() << std::endl;

  doStuff(B());
  doStuff(C());
  doStuff(A());
  doStuff(13);
  doStuff("hello");
  doStuff(MyTemplateClass<float>());

  OuterClass<std::string>::InnerClass<double> inner;
  inner.doStuff();

  MyNode<float> mn;
  decltype(mn)::type mn2;
  return 0;
}
