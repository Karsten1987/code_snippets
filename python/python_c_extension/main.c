#include <stdio.h>

#include "callback_manager.h"

void on_callback()
{
  printf("on_callback() in c\n");
}

int main()
{
  register_callback(on_callback);
  printf("Going to invoke the callback now\n");
  callback_t* callback = get_callback();
  ((void(*)())callback->callback_function_ptr)();
  return 0;
}
