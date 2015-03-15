#include <iostream>

struct Woo
{
  friend std::ostream& operator<<( std::ostream& io, const Woo& w )
  {
    return io << "wuff" ;
  }
};

class MainType
{

  struct DataType
  {
    virtual void print() const = 0;
  };

  template<typename T>
  struct DataType_T : DataType
  {
    T data_;

    DataType_T( const T& data ):
      data_(data)
    {}

    virtual void print() const
    {
      std::cout << "data says:\t" << data_ << std::endl;
    }
  };

  DataType* data_;

public:

  template <typename T>
  MainType( const T& data ):
    data_( new DataType_T<T>( data ))
  {}

  void print() const
  {
    data_->print();
  }
};

int main()
{
  MainType mtInt( 12 );
  mtInt.print();

  Woo w;
  MainType mtWoo( w );
  mtWoo.print();

  return 0;
}
