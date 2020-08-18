#pragma once

#include <iostream>

template<
  bool verbose,
  class T = size_t
>
class POD
{
public:
  /// Default constructor
  explicit POD()
  {
    //if (verbose) { std::cout << "POD default constructor" << std::endl; }
    ++default_constructor_count;
  }

  explicit POD(T _data)
  : data(std::move(_data))
  {
    //if (verbose) { std::cout << "POD default (value) constructor" << std::endl; }
    ++default_constructor_count;
  }

  /// Destructor
  ~POD()
  {
    //if (verbose) { std::cout << "POD destructor" << std::endl; }
    ++destructor_count;
  }

  /// copy constructor
  POD(const POD & other)
  {
    if (verbose) { std::cout << "POD copy constructor" << std::endl; }
    ++copy_constructor_count;

    this->data = other.data;
  }

  /// move constructor
  POD(POD && other)
  {
    if (verbose) { std::cout << "POD move constructor" << std::endl; }
    ++move_constructor_count;

    this->data = std::move(other.data);
  }

  /// copy assignment operator
  POD & operator=(const POD & other)
  {
    if (verbose) { std::cout << "POD assignment operator" << std::endl; }
    ++copy_assignment_count;

    if (&other != this) {
      this->data = other.data;
    }
    return *this;
  }

  /// move assignment operator
  POD & operator=(POD && other)
  {
    if (verbose) { std::cout << "POD move assignment operator" << std::endl; }
    ++move_assignment_count;

    this->data = std::move(other.data);
    return *this;
  }

  T data = {};

  static void print_statistics()
  {
    std::cout << "**** Constructor Statistics for POD ****" << std::endl;
    std::cout << "default constructor calls: " << default_constructor_count << std::endl;
    std::cout << "destructor calls: " << destructor_count << std::endl;
    std::cout << "copy constructor calls: " << copy_constructor_count << std::endl;
    std::cout << "move constructor calls: " << move_constructor_count << std::endl;
    std::cout << "copy assignment calls: " << copy_assignment_count << std::endl;
    std::cout << "move assignment calls: " << move_assignment_count << std::endl;
    std::cout << "****************************************" << std::endl;
  }

  static uint64_t default_constructor_count;
  static uint64_t destructor_count;
  static uint64_t copy_constructor_count;
  static uint64_t move_constructor_count;
  static uint64_t copy_assignment_count;
  static uint64_t move_assignment_count;
};

template<
  bool verbose,
  class T = size_t
>
inline std::ostream & operator << (std::ostream & out, const POD<verbose, T> & pod)
{
  out << "POD(";
  out << pod.data;
  out << ")";
  return out;
}

template<> uint64_t POD<true>::default_constructor_count = 0u;
template<> uint64_t POD<true>::destructor_count = 0u;
template<> uint64_t POD<true>::copy_constructor_count = 0u;
template<> uint64_t POD<true>::move_constructor_count = 0u;
template<> uint64_t POD<true>::copy_assignment_count = 0u;
template<> uint64_t POD<true>::move_assignment_count = 0u;

template<> uint64_t POD<false>::default_constructor_count = 0u;
template<> uint64_t POD<false>::destructor_count = 0u;
template<> uint64_t POD<false>::copy_constructor_count = 0u;
template<> uint64_t POD<false>::move_constructor_count = 0u;
template<> uint64_t POD<false>::copy_assignment_count = 0u;
template<> uint64_t POD<false>::move_assignment_count = 0u;
