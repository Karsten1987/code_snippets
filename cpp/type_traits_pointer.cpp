#include <iostream>
#include <memory>
#include <vector>
struct X
{
  static constexpr auto text = "Yay";
};

template<class T>
struct is_pointer
{
  static constexpr auto value = false;
};

template<class T>
struct is_pointer<T*>
{
  static constexpr auto value = true;
};

template<class T>
struct is_ref
{
  static constexpr auto value = false;
};

template<class T>
struct is_ref<T&>
{
  static constexpr auto value = true;
};

template<bool, class T>
struct enable_if;

template<class T>
struct enable_if<true, T>
{
  typedef T type;
};

template<bool, class T>
struct enable_if_not;

template<class T>
struct enable_if_not<false, T>
{
  typedef T type;
};


template<class T, typename enable_if<is_ref<T>::value, T>::type* = nullptr>
void f(const T sp, const std::vector<int>& v)
{
  std::cout << v.size() << " doing reference stuff with " << sp->text << std::endl;
  std::cout << "ref count inside function: " << sp.use_count() << std::endl;
}

template<class T, typename enable_if_not<is_pointer<T>::value, T>::type* = nullptr>
void f(const T sp, const std::vector<int>& v)
{
  std::cout << v.size() << " doing non pointer stuff with " << sp->text << std::endl;
  std::cout << "ref count inside function: " << sp.use_count() << std::endl;
}

template<class T, typename enable_if<is_pointer<T>::value, T>::type* = nullptr>
void f(const T sp,
      const std::vector<int>& v)
{
  std::cout << v.size() << "doing pointer stuff with " << (*sp)->text << std::endl;
  std::cout << "ref count inside function: " << sp->use_count() << std::endl;
}

int main()
{
  std::shared_ptr<X> sp = std::make_shared<X>();
  std::cout << "ref count before function: " << sp.use_count() << std::endl;
  std::cout << "should be a pointer " << std::boolalpha << is_pointer<decltype(&sp)>::value << std::endl;
  std::cout << "should be a pointer " << std::boolalpha << is_pointer<decltype(sp)>::value << std::endl;
  f(&sp, {1,2,3,4,5});
  f(sp, {1,2,3,4,5});
};
