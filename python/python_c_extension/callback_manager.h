#ifndef CALLBACK_MANAGER_H_
#define CALLBACK_MANAGER_H_

typedef struct _callback
{
  //void(*callback_function_ptr)();
  void* callback_function_ptr;
} callback_t;

void register_callback( void* fcn );

callback_t* get_callback( void );

#endif
