#ifndef PY_UTIL_H
#define PY_UTIL_H
#include <Python.h>
#include <vector>


PyObject* vectorToTuple_Float(const std::vector<float> &data);
std::vector<float> listTupleToVector_Float(PyObject* in);
#endif
