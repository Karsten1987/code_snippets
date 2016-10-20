/*
 * idea here is to only allow templates which have a certain set of functions
 */
#include <stdio.h>
#include <memory>
#include <utility>
#include <type_traits>
#include <typeinfo>

template<class T, typename = void>
struct has_do_stuff
{
  static constexpr bool value = false;
};

template<class T>
struct has_do_stuff<T, typename std::enable_if<std::is_same<void, decltype(std::declval<T>().do_stuff())>::value>::type>
{
  static constexpr bool value = true;
};

template<class T, typename = void>
struct has_do_more
{
  static constexpr bool value = false;
};

template<class T>
struct has_do_more<T, typename std::enable_if<std::is_same<void, decltype(std::declval<T>().do_more())>::value>::type>
{
  static constexpr bool value = true;
};

template<class T, typename = void>
struct is_manageable
{
  static constexpr bool value = false;
};

template<class T>
struct is_manageable<T, typename std::enable_if<   has_do_stuff<T>::value
                                                && has_do_more<T>::value
                                               >::type>
{
  static constexpr bool value = true;
};

template<class T, typename = void>
class Callee
{
public:
  Callee(T&& inst):
    inst_(new T(inst))
  {}

  void do_normal_stuff()
  {
    printf("Doing normal in normal Callee\n");
    inst_->do_normal_stuff();
  }

private:
  std::unique_ptr<T> inst_;
};

template<class T>
class Callee<T, typename std::enable_if<is_manageable<T>::value>::type>
{
public:
  Callee(T&& inst):
    inst_(new T(inst))
  {}

  void do_stuff(){
    inst_->do_stuff();
  }

  void do_normal_stuff()
  {
    printf("Doing normal in Manageable Callee\n");
    inst_->do_normal_stuff();
  }

  private:
  std::unique_ptr<T> inst_;
};

class InstanceBase
{
public:
  void do_normal_stuff()
  {
    printf("I am doing stuff in my base\n");
  }
};

class InstanceA : public InstanceBase
{
public:
  void do_stuff()
  {
    printf("do stuff in InstanceA\n");
  }
};

class InstanceB : public InstanceBase
{
public:
  void do_stuff()
  {
    printf("do stuff in InstanceC\n");
  }

  void do_more()
  {
    printf("do more stuff in InstanceC\n");
  }
};

int main()
{
  InstanceA a;
  Callee callee_a(std::move(a));
  callee_a.do_normal_stuff();

  InstanceB b;
  Callee<decltype(b)> callee_b(std::move(b));
  callee_b.do_normal_stuff();
  //static_assert(decltype(&InstanceA::do_stuff)::dummy_error, "Dump my type");
  //static_assert(decltype(std::declval<InstanceA>().do_stuff())::dummy_error, "Dump my type");

  // work !! bool b = std::is_same<void, decltype(std::declval<InstanceA>().do_stuff())>::value;
  
  //works as well
  bool has_do_stuff = std::is_same<void(InstanceA::*)(), decltype(&InstanceA::do_stuff)>::value;
  //bool b = std::is_same<void(), decltype(free_floating)>::value;
  printf("has to do stuff %d\n", has_do_stuff);

  printf("is manageable %d\n", is_manageable<InstanceA>::value);
  printf("is manageable %d\n", is_manageable<InstanceB>::value);

  //printf("instance %s\n", typeid(decltype(&InstanceA::do_stuff)).name());
  //printf("decltype %s\n", typeid(decltype(std::declval<InstanceA>().do_stuff())).name());

  //printf("InstanceA is manageable? %d\n", is_manageable<InstanceA>::value);
  //InstanceB b;
  //Callee<decltype(b)> callee_b(std::move(b));
  //callee_b.do_stuff();

  return 0;
}
