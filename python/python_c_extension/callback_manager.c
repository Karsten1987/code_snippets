#include <stdio.h>
#include "callback_manager.h"

static callback_t callback;

void register_callback( void* fcn )
{
  callback.callback_function_ptr = fcn;
}

callback_t* get_callback()
{
  return &callback;
}
