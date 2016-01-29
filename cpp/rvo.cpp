#include <iostream>

/*
 * compile with
 * g++ -fno-elide-constructors
 * to play with rvo
 */
class C
{
  public:
  std::string s_;

  C( std::string s )
    : s_(std::move(s) )
  {
    std::cout << "A default constructor is made" << std::endl;
  }

  /*
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

  // move semantics
  C( C&& other )
    : s_(std::move(other.s_))
  {
    std::cout << "A move of C is made" << std::endl;
    other.s_.clear();
  }
  */
};

C create_struct()
{
  C obj( "created struct");
  return obj;
}
/*
void renameByRef( C& c )
{
  c.s_ = " renamed by ref";
}

C renameByCopy( C c )
{
  c.s_ = " renamed by copy ";
  return c;
}
*/
int main()
{
  C obj = create_struct();

  /*
  renameByRef( obj );

  renameByCopy( obj );
  */
  return 0;
}
