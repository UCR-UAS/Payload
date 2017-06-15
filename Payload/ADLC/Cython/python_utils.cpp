#include "python_utils.h"
#include <vector>
#include <iostream>
#include <Python.h>

using namespace std;

PyObject* vectorToTuple_Float(const vector<float> &data) {
	PyObject* tuple = PyTuple_New( data.size() );
	if (!tuple) throw logic_error("Unable to allocate memory for Python tuple");
	for (unsigned int i = 0; i < data.size(); i++) {
		PyObject *num = PyFloat_FromDouble( (double) data[i]);
		if (!num) {
			Py_DECREF(tuple);
			throw logic_error("Unable to allocate memory for Python tuple");
		}
		PyTuple_SET_ITEM(tuple, i, num);
	}

	return tuple;
}


// PyObject -> Vector
vector<float> listTupleToVector_Float(PyObject* incoming) {
	vector<float> data;
	if (PyTuple_Check(incoming)) {
		for(Py_ssize_t i = 0; i < PyTuple_Size(incoming); i++) {
			PyObject *value = PyTuple_GetItem(incoming, i);
			data.push_back( PyFloat_AsDouble(value) );
		}
	} else {
		if (PyList_Check(incoming)) {
			for(Py_ssize_t i = 0; i < PyList_Size(incoming); i++) {
				PyObject *value = PyList_GetItem(incoming, i);
				data.push_back( PyFloat_AsDouble(value) );
			}
		} else {
			throw logic_error("Passed PyObject pointer was not a list or tuple!");
		}
	}
	return data;
}
