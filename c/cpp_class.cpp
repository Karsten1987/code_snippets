#include <stdio.h>
#include <functional>

template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)> {
    template <typename... Args>
    static Ret callback(Args... args)
    {
      return func(args...);
    }
    static std::function<Ret(Params...)> func;
};

// Initialize the static member.
template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;

typedef void (*register_callback_t)();

template<typename T>
register_callback_t makeCCallback(void (T::*method)(),T* r){
  Callback<void()>::func = std::bind(method, r);
  void (*c_function_pointer)() = static_cast<decltype(c_function_pointer)>(Callback<void()>::callback);
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
  };
}

/*
#if __cplusplus
extern "C"
{
#endif

typedef struct _callback
{
  void(*fcn)(void);
} callback_t;

#if __cplusplus
}
#endif
*/

#include "callback_manager.h"

int main()
{
  foo::Foo<1> f1;
  register_callback((void*)makeCCallback(&decltype(f1)::on_callback, &f1));

  invoke_callback();
  /*
  foo::Foo<2> f2;
  callback_t cb_struct2;
  cb_struct2.fcn = makeCCallback(&decltype(f2)::on_callback, &f2);
  cb_struct2.fcn();
  */
  return 0;
}
