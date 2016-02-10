#include <iostream>

struct Data
{
  int i;
  std::string s;
};

class MyClass
{
public:
  std::string my_name_;
  Data* my_data_;

  MyClass( std::string name ):
    my_name_(std::move(name)),
    my_data_(new Data())
  {
    std::cout << "constructor is called" << std::endl;
    my_data_->i = counter++;
    my_data_->s = my_name_;
  }

  MyClass( const MyClass& rhs ):
    my_name_(rhs.my_name_),
    my_data_(new Data())
  {
    std::cout << "copy constructor is called" << std::endl;
    my_data_->i = counter++;
    my_data_->s = rhs.my_name_;
  }

  MyClass& operator=( MyClass rhs )
  {
    std::cout << "operator= is called" << std::endl;
    std::swap(my_name_, rhs.my_name_);
    std::swap(my_data_, rhs.my_data_);
    return *this;
  }

  static int counter;
};

int MyClass::counter = 0;

std::ostream& operator<<( std::ostream& os, const MyClass& mc )
{
  os << "#"<< mc.my_data_->i << " " << mc.my_data_->s;
  return os;
}

int main()
{
  MyClass mc0("karsten");
  MyClass mc1(mc0);
  MyClass mc2 = mc0;
  MyClass mc3("Ally");
  mc3 = mc0;
  std::cout << "initialization" << std::endl;
  std::cout << mc0 << std::endl;
  std::cout << mc1 << std::endl;
  std::cout << mc2 << std::endl;
  std::cout << mc3 << std::endl;

  mc0.my_data_->i = 13;
  std::cout << "changing first instance to " << mc0.my_data_->i << std::endl;
  std::cout << mc0 << std::endl;
  std::cout << mc1 << std::endl;
  std::cout << mc2 << std::endl;
  std::cout << mc3 << std::endl;


  return 0;
}
