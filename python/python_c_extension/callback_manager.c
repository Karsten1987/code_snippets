#include <stdio.h>
#include "callback_manager.h"

static callback_t callback;

void register_callback( void* fcn )
{
  fprintf(stderr, "Going to register address %p\n", fcn);
  fflush(stderr);
  callback.callback_function_ptr = fcn;
}

void invoke_callback()
{
  if (callback.callback_function_ptr == NULL)
  {
    return;
  }
  fprintf(stderr, "Going to invoke address %p\n", callback.callback_function_ptr);
  fflush(stderr);
  ((void(*)(void))callback.callback_function_ptr)();
}

callback_t* get_callback()
{
  return &callback;
}
