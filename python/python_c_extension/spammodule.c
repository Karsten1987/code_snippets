#include "Python.h"

static PyObject *
py_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return PyLong_FromLong(sts);
}

static PyObject *
py_hello_world(PyObject* self, PyObject* args)
{
  return Py_BuildValue("s", "Hello World");
}


static PyObject* void_callback = NULL;

// set callback function first
static PyObject*
py_set_void_callback(PyObject* self, PyObject* args)
{
    PyObject *result = NULL;
    PyObject *temp;

    if (PyArg_ParseTuple(args, "O:set_callback", &temp)) {
        if (!PyCallable_Check(temp)) {
            PyErr_SetString(PyExc_TypeError, "parameter must be callable");
            return NULL;
        }
        Py_XINCREF(temp);         /* Add a reference to new callback */
        Py_XDECREF(void_callback);  /* Dispose of previous callback */
        void_callback = temp;       /* Remember new callback */
        /* Boilerplate to return "None" */
        Py_INCREF(Py_None);
        result = Py_None;
    }
    return result;
}

static PyObject*
py_trigger_void_callback(PyObject* self, PyObject* args)
{
  PyObject* result = PyObject_CallObject(void_callback, NULL);
  if (result == NULL)
    return NULL;
  return result;
}

static PyMethodDef spam_methods[] = {
    {"system",  py_system, METH_VARARGS, "Execute a shell command."},
    {"hello_world",  py_hello_world, METH_VARARGS, "hello world"},
    {"set_void_callback",  py_set_void_callback, METH_VARARGS, "hello world"},
    {"trigger_void_callback",  py_trigger_void_callback, METH_VARARGS, "hello world"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef spammodule = {
  PyModuleDef_HEAD_INIT,
  "spam",
  NULL, // no doc for now
  -1, // module keeps state in global variables
  spam_methods
};




PyMODINIT_FUNC
PyInit_spam(void) // void parameter is important here (C stuff)
{
  return PyModule_Create(&spammodule);
}
