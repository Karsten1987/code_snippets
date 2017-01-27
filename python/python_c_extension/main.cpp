#include <stdio.h>
#include <functional>

template <typename T, size_t Index>
struct Callback;

template <typename Ret, typename... Params, size_t Index>
struct Callback<Ret(Params...), Index>
{
    template <typename... Args>
    static Ret callback(Args... args)
    {
      return func(args...);
    }
    static std::function<Ret(Params...)> func;
};

// Initialize the static member.
template <typename Ret, typename... Params, size_t Index>
std::function<Ret(Params...)> Callback<Ret(Params...), Index>::func;

typedef void (*register_callback_t)();

template<typename T, size_t Index>
register_callback_t makeCCallback(void (T::*method)(),T* r)
{
  Callback<void(), Index>::func = std::bind(method, r);
  void (*c_function_pointer)() = static_cast<decltype(c_function_pointer)>(Callback<void(), Index>::callback);
  return c_function_pointer;
}

namespace foo
{
  template<int i_t>
  struct Foo
  {
    int i = i_t;
    void on_callback()
    {
      printf("On C++ callback with accessing member i %d\n", i);
    }

    void on_callback2()
    {
      printf("Second callback\n");
    }
  };
}


#if __cplusplus
extern "C"
{
#endif

typedef struct _my_callback
{
  void(*fcn1)(void);
  void(*fcn2)(void);
} my_callback_t;

#if __cplusplus
}
#endif

#include "callback_manager.h"

int main()
{
  //foo::Foo<1> f1;
  //register_callback((void*)makeCCallback<foo::Foo<1>, 1ul>(&decltype(f1)::on_callback, &f1));
  //invoke_callback();

  foo::Foo<2> f2;
  my_callback_t cb_struct2;
  cb_struct2.fcn1 = makeCCallback<foo::Foo<2>, 1ul>(&decltype(f2)::on_callback, &f2);
  cb_struct2.fcn2 = makeCCallback<foo::Foo<2>, 2ul>(&decltype(f2)::on_callback2, &f2);
  cb_struct2.fcn2();
  cb_struct2.fcn1();

  return 0;
}
