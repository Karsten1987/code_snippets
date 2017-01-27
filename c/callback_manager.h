#ifndef CALLBACK_MANAGER_H_
#define CALLBACK_MANAGER_H_

#if __cplusplus
extern "C"
{
#endif

typedef struct _callback
{
  //void(*callback_function_ptr)();
  void* callback_function_ptr;
} callback_t;

void register_callback( void* fcn );

void invoke_callback();

callback_t* get_callback( void );

#if __cplusplus
}
#endif

#endif
