// Created by Danil Lykov on 16/07/2018
// Tutorial on extending python with c/c++
//
// This works with python2
#include "simd.c"
#include <Python.h>
// Use simd testing functions

static PyObject *SpamError;

void Parce_List(PyObject *pya,PyObject *pyb, float *a,float *b)
{
	PyObject *v;
	double x;
	for (int i =0; i<4;i++)
	{
		v = PyList_GetItem(pya, i);
		x = PyFloat_AsDouble(v);
		a[i] = x;

		v = PyList_GetItem(pyb, i);
		x = PyFloat_AsDouble(v);
		b[i] = x;
	}
}

static PyObject *
cdan_simd_add(PyObject *self,PyObject *arga)
{
	PyObject *pya;
	PyObject *pyb;
	PyObject *ret;
	ret = PyList_New(4);
	float a[4];
	float b[4];
	if (!PyArg_ParseTuple(arga, "O|O", &pya,&pyb))
		return NULL;
	Parce_List(pya,pyb,a,b);

	float * c;
	c = SIMD_add(a,b);

	for (int i =0; i<4;i++)
	{
		PyList_SetItem(ret, i,
				PyFloat_FromDouble((double)c[i]) );
	}
	return ret;
}

static PyObject *
cdan_loop_add(PyObject *self,PyObject *arga)
{
	PyObject *pya;
	PyObject *pyb;
	PyObject *ret;
	ret = PyList_New(4);
	float a[4];
	float b[4];
	if (!PyArg_ParseTuple(arga, "O|O", &pya,&pyb))
		return NULL;
	Parce_List(pya,pyb,a,b);

	float * c;
	c = just_add(a,b);

	for (int i =0; i<4;i++)
	{
		PyList_SetItem(ret, i,
				PyFloat_FromDouble((double)c[i]) );
	}
	return ret;
}

static PyObject *
cdan_system(PyObject *self,PyObject *args)
{
	const char * command;
	int sts;
	if (!PyArg_ParseTuple(args, "s", &command))
		return NULL;
	sts = system(command);

	if (sts < 0) {
		PyErr_SetString(SpamError, "System command failed");
		return NULL;
	}
	return PyLong_FromLong(sts);
}

static PyMethodDef SpamMethods[] = {
    {"system",  cdan_system, METH_VARARGS,
     "Execute a shell command."},
    {"simd_add",  cdan_simd_add, METH_VARARGS,
     "SIMD add. pass len-4 list"},
    {"loop_add",  cdan_loop_add, METH_VARARGS,
     "Loop add. pass len-4 list"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef cdanmod =
{
	PyModuleDef_HEAD_INIT,
	"cdan",
	":documantation: this is a test module for system calls",
	-1,
	SpamMethods
};


PyMODINIT_FUNC
PyInit_cdan(void)
{
	 const char *greet = "   _____      __             __ __\n  / ___ \\ ___/ /___ _ ___   / // /__ _  __\n / / _ `// _  // _ `// _ \\ / //  '_/| |/ /\n \\ \\_,_/ \\_,_/ \\_,_//_//_//_//_/\\_\\ |___/\n  \\___/  Greetings! this is a python module written in C by @danlkv! \n\n";

	printf("%s",greet);
	//return PyModule_Create(&cdanmod);
	PyObject *m;
	m = PyModule_Create(&cdanmod);
	if (m == NULL)
		Py_RETURN_NONE;
	//SpamError = PyErr_NewException("cdan.error", NULL, NULL);
	//Py_INCREF(SpamError);
	//PyModule_AddObject(m, "error", SpamError);
}

