#include <iostream>

template<class T>
struct is_type
{
  typedef T type;
};

template<class T>
struct is_const
{
  typedef T type;
  static constexpr bool value = false;
};

template<class T>
struct is_const<const T>
{
  typedef T type;
  static constexpr bool value = true;
};

template<class T, bool>
struct enable_if
{
};

template<class T>
struct enable_if<T, true>
{
  typedef T type;
};

template<class T, class = typename enable_if<typename is_type<T>::type, is_const<typename is_type<T>::type>::value>::type>
struct is_awesome
{
  typedef T type;
};

// declaration only
template<class T, class ... P0ToN>
struct is_valid;

template<class T>
struct is_valid<T>
{
};

template<class T, class ... P1ToN>
struct is_valid<T,T,P1ToN...>
{
  typedef T type;
};

template<class T, class P0, class ... P1ToN>
struct is_valid<T, P0, P1ToN...> : is_valid<T, P1ToN...>
{};

template<class T, class = typename is_valid<T, int, float, double>::type>
struct is_number
{
  typedef T type;
};

int main()
{

  is_type<int>::type i = 11;
  is_type<const double>::type d = 12;
  //d = 13; // const value
  std::cout << "got a value of " << i << std::endl;

  //std::cout << "i is const: " << std::boolalpha << is_const<decltype(i)>::value << std::endl;
  std::cout << "d is const: " << std::boolalpha << is_const<decltype(d)>::value << std::endl;

  enable_if<is_type<const double>::type, is_const<is_type<const double>::type>::value>::type awesome_d = 13;

  //is_awesome<double>::type awesome_d_d = 15; // does not compile!
  is_awesome<const double>::type aawesome_d_d = 15;

  is_number<double>::type n_d = 15;
  is_number<float>::type n_f = 15;
  is_number<int>::type n_i = 15;
  //is_number<std::string>::type n_s = "hello"; // does not compile!
}


