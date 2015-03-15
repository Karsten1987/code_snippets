#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <vector>
#include <map>
#include <string>


#define for_each BOOST_FOREACH
struct Converter
{
  typedef boost::function<void (std::string, int)> Callback_t;

  std::vector<Callback_t> callbacks;

  void registerCallbacks( const Callback_t& cb )
  {
    callbacks.push_back( cb );
  }

  void callAll()
  {
    for_each( Callback_t cb, callbacks )
    {
      cb("Hello World", 123 );
    }
  }
};

struct ObjectA
{
  void f( const std::string& s, int i )
  {
    std::cerr << "ObjectA received " << s << " with integer " << i << std::endl;
  }
};

struct ObjectB
{
  ~ObjectB()
  {
    std::cerr << "ObjectB is shutting down .. " << std::endl;
  }

  int i_;

  void f( const std::string& s, int i )
  {
    std::cerr << "ObjectB with internal state " << i_ << " << received " << s << " with integer " << i << std::endl;
  }

};

void registerObjectA( Converter& conv )
{
  ObjectA a;
  boost::function<void (std::string, int )> f = boost::bind(&ObjectA::f, &a, _1, _2 );
  conv.registerCallbacks( f );
}

void registerObjectB_wrong( Converter& conv )
{
  ObjectB b;
  b.i_ = 1;
  conv.registerCallbacks( boost::bind(&ObjectB::f, &b, _1, _2 ) );
  b.i_ = 2;
}

void registerObjectB_ptr( Converter& conv )
{
  boost::shared_ptr<ObjectB> b_ptr = boost::make_shared<ObjectB>();
  b_ptr->i_ = 1;
  conv.registerCallbacks( boost::bind(&ObjectB::f, b_ptr, _1, _2 ) );
  b_ptr->i_ =2 ;
}

void doStuff(boost::shared_ptr<ObjectB> b_ptr)
{
  Converter conv;
  b_ptr->i_ = 2;
  conv.registerCallbacks( boost::bind(&ObjectB::f, b_ptr, _1, _2 ) );
  std::cerr << "b_ptr used by " << b_ptr.use_count() << std::endl;

  conv.callAll();
}

void doMoreStuff()
{
  boost::shared_ptr<Converter> conv_ptr = boost::make_shared<Converter>();
  registerObjectB_ptr( *conv_ptr );
  conv_ptr->callAll();

  conv_ptr.reset( new Converter() );
  std::cerr << "I want to see a destructor here " << std::endl;
}

int main()
{
  //Converter conv;
  //registerObjectA( conv );
  //registerObjectB_wrong( conv );
  //registerObjectB_ptr( conv );

  //ObjectB b;
  //b.i_ = 1;
  //conv.registerCallbacks( boost::bind(&ObjectB::f, &b, _1, _2 ) );
  //b.i_ = 2;

  //boost::shared_ptr<ObjectB> b_ptr = boost::make_shared<ObjectB>();
  //b_ptr->i_ = 1;
  //conv.registerCallbacks( boost::bind(&ObjectB::f, b_ptr, _1, _2 ) );
  //b_ptr->i_ =2 ;

  //std::cerr << "b_ptr used by " << b_ptr.use_count() << std::endl;

  //doStuff( b_ptr );
  doMoreStuff( );

  //std::cerr << "b_ptr used by " << b_ptr.use_count() << std::endl;
  
  //conv.callAll();
  return 0;
}
