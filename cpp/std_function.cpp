#include <iostream>
#include <functional>

class events {
private:
    // have a placeholder base-type:
    struct base {
      virtual ~base() {}
    };

    // have a derived type to wrap the 
    //  actual functor object:
    template <typename... Args>
    struct wrapped : base {
      typedef std::function<int(Args...)> func_type;
      func_type f;
      wrapped(func_type aFunc) : f(aFunc) { };
    };

    // Hold a base-type pointer:
    std::unique_ptr<base> p_base;

public:
    // Initialize object with any function:
    template <typename... Args>
    events(std::function<int(Args...)> aFunc) :
           p_base(new wrapped<Args...>(aFunc)) { };

    // Assign object with any function:
    template <typename... Args>
    events& operator=(std::function<int(Args...)> aFunc) {
      p_base = std::unique_ptr<base>(new wrapped<Args...>(aFunc));
      return *this;
    }

    // Call the function by casting the base
    //  pointer back to its derived type:
    template <typename... Args>
    int operator()(Args... args) const {
      wrapped<Args...>* p_wrapped = dynamic_cast< wrapped<Args...>* >(p_base.get());
      if(p_wrapped) // <- if cast successful
        return p_wrapped->f(args...);
      else
        throw std::runtime_error("Invalid arguments to function object call!");
    }
};

template<class return_t, class... Args>
return_t call( std::function<return_t(Args...)> f, Args... args )
{
  return_t ret = f(args...);
  return ret;
}

int add( int n1, int n2 )
{
  return n1+n2;
}

int add3( int n1, int n2, int n3 ) {
  return n1+n2+n3;
};

int main()
{
  std::function<int(int, int)> fc = std::bind(&add3, std::placeholders::_1, std::placeholders::_2, 3);
  //std::function<int(int, int)> fc2 = fc;
  events a(fc);
  std::cout << "sum of 1,2 and 3 is " << a(1, 2) << std::endl;
  //std::function<int(...)> f_add = add;
  //auto sum = call(f_add, 1, 2);
  //std::cout << "sum of 1 and 2 =" << sum << std::endl;

  //std::function<decltype(add)> f_add_decl = add;
  //auto sum1 = call(std::function<decltype(add)>(add), 3, 4);
  //std::cout << "sum of 3 and 4 = " << sum1 << std::endl;
  return 0;
}
