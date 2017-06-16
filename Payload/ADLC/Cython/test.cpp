#include <iostream>
#include <opencv2/opencv.hpp>
#include <Python.h>
#include "numpy/arrayobject.h"
#include <ctime>


using namespace cv;
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


int main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pValue, *pArgs;

    std::vector<float> v;
    for(int i= 0; i < 1000000;++i){
      v.push_back(i);
    }

		///TURN THE VECTOR INTO PYTHON OBJECT THAT CAN BE PASSED IN
    PyObject * vec = vectorToTuple_Float(v);
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, vec);

		//
		///name of the file the function is in, no .py extension
    ///
		std::string filename = "test";
		///
		///name of the function in the file
    ///
		std::string funcname = "multiply";


		Py_Initialize();
    pName = PyString_FromString(filename.c_str());
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
		//i think Py_DECREF is deleting memory not used anmore?
    Py_DECREF(pName);
    if (pModule != NULL) {

        pFunc = PyObject_GetAttrString(pModule, funcname.c_str());
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
						//this makes the function call
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {

						//RETURN AS A STRING
						string a = PyBytes_AsString(pValue);

						//RETURN AS A TUPLE
						//std::vector<float> res = listTupleToVector_Float(pValue);
								//delete the value
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }

    Py_Finalize();
    return 0;
}
