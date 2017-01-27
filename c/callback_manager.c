#include <stdio.h>
#include "callback_manager.h"

static callback_t callback;

void register_callback( void* fcn )
{
  callback.callback_function_ptr = fcn;
}

void invoke_callback()
{
  if (callback.callback_function_ptr == NULL)
  {
    return;
  }
  ((void(*)(void))callback.callback_function_ptr)();
}

callback_t* get_callback()
{
  return &callback;
}
