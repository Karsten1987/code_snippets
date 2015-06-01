#include <iostream>

/*
 * compile with
 * g++ -fno-elide-constructors
 * to play with rvo
 */
struct C
{
  std::string s_;

  C( std::string s )
    : s_(std::move(s) )
  {
    std::cout << "A default constructor is made" << std::endl;
  }

  C( const C& other )
    : s_(std::move(other.s_))
  {
    std::cout << "A copy of C is made" << std::endl;
  }

  C& operator=( const C& rhs )
  {
    std::cout << "A copy operator= was made" << std::endl;
    if ( this != &rhs )
    {
      this->s_ = rhs.s_;
      return *this;
    }
    return *this;
  }

  C& operator=( C&& rhs )
  {
    std::cout << "A move operator= was made" << std::endl;
    this->s_ = std::move(rhs.s_);
    return *this;
  }

  /** move semantics */
  C( C&& other )
    : s_(std::move(other.s_))
  {
    std::cout << "A move of C is made" << std::endl;
    other.s_.clear();
  }
};

C create_struct()
{
  C obj( "created struct");
  return obj;
}

void renameByRef( C& c )
{
  c.s_ = " renamed by ref";
}

C renameByCopy( C c )
{
  c.s_ = " renamed by copy ";
  return c;
}

int main()
{
  C obj = create_struct();
  std::cout << "new object created with " << obj.s_ << std::endl;

  renameByRef( obj );
  std::cout << "new object name: " << obj.s_ << std::endl;

  C obj2 = renameByCopy( obj );
  std::cout << "new object name: " << obj2.s_ << std::endl;

  std::cout << "size of C " << sizeof(C) << std::endl;

  C obj3( "delete me");
  obj3 = obj2;
  C obj4( "i am never shown" );
  obj4 = std::move(obj2);
  //get_struct( C() );
  //get_struct( obj );
  return 0;
}
