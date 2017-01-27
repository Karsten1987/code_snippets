#include <stdio.h>

#define bool int
#define false 0
#define true 1

void* callback_function_ptr = NULL;

bool on_function()
{
  printf("yay! Totally invoking on function\n");
  return true;
}

void register_callback()
{
  callback_function_ptr = on_function;
}

void invoke_callback()
{
  if (callback_function_ptr != NULL)
  {
    ((bool(*)())callback_function_ptr)();
  }
}

int main()
{
  register_callback();

  invoke_callback();

  return 0;
}
