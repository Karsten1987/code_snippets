#include <iostream>


class Whatever
{

public:
  template <class T>
  Whatever(T item):
    inst_(new Interface_t<T>(item))
  {}

  void print() const
  {
    inst_->print();
  }

private:
  struct Interface
  {
    virtual void print() const = 0;
  };

  template<class T>
  struct Interface_t : Interface
  {
    T obj_;

    Interface_t( const T& obj ):
      obj_(obj)
    {}

    void print() const
    {
      obj_.print();
    }
  };

  Interface* inst_;

};

struct PrintyStruct
{
  int i;

  void print() const
  {
    std::cout << "PrintyStruct says " << i << std::endl;
  }
};

struct PrintyClass
{
public:
  std::string s;

  void print() const
  {
    std::cout << "PrintyClass says " << s << std::endl;
  }
};

int main()
{
  PrintyStruct ps;
  ps.i = 13;

  PrintyClass pc;
  pc.s = "Ally";

  Whatever w1(ps);
  w1.print();

  Whatever w2(pc);
  w2.print();
  return 0;
}
