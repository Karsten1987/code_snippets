#include "Python.h"

#include "callback_manager.h"

static PyObject *my_callback = NULL;

// set callback function first
static PyObject*
py_register_callback(PyObject* self, PyObject* args)
{
  PyObject *result = NULL;
  PyObject *temp;

  //if (PyArg_ParseTuple(args, "O:set_callback", &cb_struct->callback_function_ptr)) {
  if (PyArg_ParseTuple(args, "O:set_callback", &temp)) {
      if (!PyCallable_Check(temp)) {
          PyErr_SetString(PyExc_TypeError, "parameter must be callable");
          return NULL;
      }
      Py_INCREF(temp);
      Py_XDECREF(my_callback);  /* Dispose of previous callback */
      my_callback = temp;       /* Remember new callback */
      /* Boilerplate to return "None" */
      Py_INCREF(Py_None);
      result = Py_None;
      // pass along to the callback manager
      register_callback(my_callback);
  }
  return result;
}

static PyObject*
py_invoke_callback(PyObject* self, PyObject* args)
{
  //callback_t* callback = get_callback();
  return PyObject_CallObject((PyObject*)get_callback()->callback_function_ptr, NULL);
  //invoke_callback();
  //return Py_None;
}

static PyMethodDef py_methods[] = {
    {"register_callback",  py_register_callback, METH_VARARGS, "registering a callback inside the callback manager"},
    {"invoke_callback",  py_invoke_callback, METH_VARARGS, "invoking the registered callback inside the callback manager"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef callbackmodule = {
  PyModuleDef_HEAD_INIT,
  "callbackmodule",
  NULL, // no doc for now
  -1, // module keeps state in global variables
  py_methods
};

PyMODINIT_FUNC
PyInit_callbackmodule(void) // void parameter is important here (C stuff)
{
  return PyModule_Create(&callbackmodule);
}
