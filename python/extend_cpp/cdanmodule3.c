// Created by Danil Lykov on 16/07/2018
// Tutorial on extending python with c/c++
//
// This works with python2
#include <Python.h>

static PyObject *SpamError;



static PyObject *
cdan_system(PyObject *self,PyObject *args)
{
	const char * command;
	int sts;
	if (!PyArg_ParseTuple(args, "s", &command))
		return NULL;
	sts = system(command);

	/*
	if (sts < 0) {
		PyErr_SetString(SpamError, "System command failed");
		return NULL;
	}
	*/
	return PyLong_FromLong(sts);
	return PyBuildValue("i",sts);
}

static PyMethodDef SpamMethods[] = {
    {"system",  cdan_system, METH_VARARGS,
     "Execute a shell command."},
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

	     const char *greet = "   _____      __             __ __\n  / ___ \\ ___/ /___ _ ___   / // /__ _  __\n / / _ `// _  // _ `// _ \\ / //  '_/| |/ /\n \\ \\_,_/ \\_,_/ \\_,_//_//_//_//_/\\_\\ |___/\n  \\___/  Greetings! this is a python module written in C by @danlkv! \n ";
	printf("%s",greet);
	return PyModule_Create(&cdanmod);
	/*
	PyObject *m;
	m = PyModule_Create(&cdanmod);
	if (m == NULL)
		return;

	SpamError = PyErr_NewException("cdan.error", NULL, NULL);
	Py_INCREF(SpamError);
	PyModule_AddObject(m, "error", SpamError);
	*/
}

