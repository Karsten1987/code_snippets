#include <iostream>

template<class T>
struct is_type
{
  typedef T type;
};

//template<>
//struct is_type<double>
//{
//  typedef const double type;
//};

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

// is_type with const T doesn not work because it wil be const const in the end
//template<class T, class = typename enable_if<is_type<T>::type, is_const<is_type<T>::type>::value>::type >
template<class T, class = typename enable_if<T, is_const<T>::value>::type >
struct is_awesome
{
  typedef T type;
};


int main()
{

  is_type<int>::type i = 11;
  is_type<const double>::type d = 12;
  //d = 13;
  std::cout << "got a value of " << i << std::endl;

  //std::cout << "i is const: " << std::boolalpha << is_const<decltype(i)>::value << std::endl;
  std::cout << "d is const: " << std::boolalpha << is_const<decltype(d)>::value << std::endl;

  //enable_if<is_type<double>::type, is_const<is_type<double>::type>::value>::type awesome_d = 13;
  //is_awesome<double>::type awesome_d_d = 15;
  is_awesome<const double>::type aawesome_d_d = 15;
  //is_awesome<int>::type udsaaawesome_d_d = 15;
}

