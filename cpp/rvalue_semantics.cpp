#include <iostream>

std::string getString()
{
  std::string s = "hello world";
  return s;
}

void printString( std::string s ) // copy as always
{
  std::cout << "I will print by copy " << s << std::endl;
}

// does not compile of ambiguity
//void printString( std::string&& s ) // move 
//{
//  std::cout << "I will print by move " << s << std::endl;
//}

int main()
{
  std::string original = "goodby world";
  std::string original_copy = original; // actual copy
  std::string original_move = std::move( original ); // move
  std::cout << "original " << original << std::endl;

  printString( "temporary" );
  printString( original_copy );
  printString( std::move(original_copy) );

  std::string s_copy = getString();
  std::cout << "s : " << getString() << std::endl;
  return 0;
}
