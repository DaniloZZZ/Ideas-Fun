// Created by Danil Lykov on 16/07/2018
// Tutorial on extending python with c/c++
//
// This works with python2
#include <Python.h>

static PyObject *SpamError;



static PyObject *
spam_system(PyObject *self,PyObject *args)
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
    {"system",  spam_system, METH_VARARGS,
     "Execute a shell command."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef spammod =
{
	PyModuleDef_HEAD_INIT,
	"spam",
	":documantation: this is a test module for system calls",
	-1,
	SpamMethods
};


PyMODINIT_FUNC
PyInit_spam(void)
{

	return PyModule_Create(&spammod);
	/*
	PyObject *m;
	m = PyModule_Create(&spammod);
	if (m == NULL)
		return;

	SpamError = PyErr_NewException("spam.error", NULL, NULL);
	Py_INCREF(SpamError);
	PyModule_AddObject(m, "error", SpamError);
	*/
}

