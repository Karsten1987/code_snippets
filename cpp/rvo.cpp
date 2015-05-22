#include <iostream>

/*
 * compile with
 * g++ -fno-elide-constructors
 * to play with rvo
 */
struct C
{
  std::string s_;

  C( std::string s ):
    s_(std::move(s) ) {}

  C( const C& other )
    :s_(std::move(other.s_))
  {
    std::cout << "A copy of C is made" << std::endl;
  }

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
  std::cout << " filling struct " << std::endl;
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
  //get_struct( C() );
  //get_struct( obj );
  return 0;
}
