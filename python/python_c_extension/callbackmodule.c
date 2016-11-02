#include "Python.h"

#include "callback_manager.h"

// set callback function first
static PyObject*
py_register_callback(PyObject* self, PyObject* args)
{
  PyObject *temp;

  if (PyArg_ParseTuple(args, "O:set_callback", &temp)) {
      if (!PyCallable_Check(temp)) {
          PyErr_SetString(PyExc_TypeError, "parameter must be callable");
          return NULL;
      }
      // pass along to the callback manager
      register_callback(temp);
  }
  return Py_None;
}

static PyObject*
py_invoke_callback(PyObject* self, PyObject* args)
{
  callback_t* callback = get_callback();
  return PyObject_CallObject((PyObject*)callback->callback_function_ptr, NULL);
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
