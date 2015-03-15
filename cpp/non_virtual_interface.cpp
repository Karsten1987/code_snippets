#include <iostream>
#include <vector>

class Shape
{
public:
  Shape( const std::string& name ):
    name_( name )
  {}

  virtual ~Shape() {}

  void const_draw( const std::string& what ) const
  {
    std::cerr << "const draw " << what << std::endl;
  }

  void draw( const std::string& what )
  {
    std::cerr << "instance of " << name_ << std::endl;
    do_draw( what );
    std::cerr << "**** pro-processing *****" << std::endl;
  }

protected:
  std::string name_;

  virtual void do_draw( const std::string& what ) = 0;


// make non-copyable
// prevent slicing
/*
  Base* b = new Derived();
  Base b2 = *b; // slicing
*/
private:
  Shape( const Shape& shape );
  Shape& operator=( const Shape& rhs );

};

class Polygon : public Shape
{
public:
  Polygon( const std::string& name):
    Shape(name)
  {}

private:
  void do_draw( const std::string& what )
  {
    std::cerr << "do_draw invoked inside of polygon : " << name_ << std::endl;
  }
};

class Circle : public Shape
{
public:
  Circle( const std::string& name ):
    Shape( name )
  {}

private:
  void do_draw( const std::string& what )
  {
    std::cerr << "do_draw invoked inside of polygon : " << name_ << std::endl;
  }
};

int main()
{
  std::vector< const Shape* > all_shapes;

  Shape* const p1 = new Polygon( "polygon1" );
  Shape* const p2 = new Polygon( "polygon2" );
  Shape* const p3 = new Polygon( "polygon3" );
  Shape* const p4 = new Polygon( "polygon4" );
  Shape* const p5 = new Polygon( "polygon5" );

  Shape const * c1 = new Circle( "circle1" );
  Shape const * c2 = new Circle( "circle2" );
  Shape const * c3 = new Circle( "circle3" );
  Shape const * c4 = new Circle( "circle4" );
  Shape const * c5 = new Circle( "circle5" );

  p1->draw( "something" );
  c1->const_draw( "somethign" );

  const Polygon p_const( "polygonconst1" );
  p_const.draw( "something" );

  all_shapes.push_back( p1 );
  all_shapes.push_back( p2 );
  all_shapes.push_back( p3 );
  all_shapes.push_back( p4 );
  all_shapes.push_back( p5 );
  all_shapes.push_back( c1 );
  all_shapes.push_back( c2 );
  all_shapes.push_back( c3 );
  all_shapes.push_back( c4 );
  all_shapes.push_back( c5 );
/*
  for ( size_t i=0; i<all_shapes.size(); ++i)
  {
    all_shapes[i]->draw( "what?!" );
  }
*/
  const std::string s = "helloworld"+1;
  std::cerr << s << std::endl;

  return 0;
}
