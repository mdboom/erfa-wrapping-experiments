#include "Python.h"
#include "numpy/arrayobject.h"
#include "numpy/ufuncobject.h"

#include "numpy/npy_3kcompat.h"

#include "numpy/npy_math.h"

#include "erfa.h"

typedef npy_intp intp;

static void
increment_ufunc(intp ndim, char **args, intp *steps)
{
    intp i;
    for (i = 0; i < ndim; ++i) {
        *(args[i]) += steps[i];
    }
}

#define BEGIN_LOOP \
    intp dN = *dimensions++; \
    intp N; \
    for (N = 0; N < dN; N++) { \

#define END_LOOP(x) \
    increment_ufunc((x), args, steps);          \
    }                                           \

/*
 *****************************************************************************
 **                             UFUNC LOOPS                                 **
 *****************************************************************************
 */

/*///////////////////////////////////////////////////////////////////////////
  eraAtco13
*/

static void
eraAtco13_wrapper(char **args, intp *dimensions, intp *steps, void *extra)
{
    int ret;

    BEGIN_LOOP
        ret = eraAtco13(
            *(double *)args[0],
            *(double *)args[1],
            *(double *)args[2],
            *(double *)args[3],
            *(double *)args[4],
            *(double *)args[5],
            *(double *)args[6],
            *(double *)args[7],
            *(double *)args[8],
            *(double *)args[9],
            *(double *)args[10],
            *(double *)args[11],
            *(double *)args[12],
            *(double *)args[13],
            *(double *)args[14],
            *(double *)args[15],
            *(double *)args[16],
            *(double *)args[17],
            (double *)args[18],
            (double *)args[19],
            (double *)args[20],
            (double *)args[21],
            (double *)args[22],
            (double *)args[23]);
        if (ret > 0) {
            PyErr_SetString(PyExc_ValueError, "dubious year");
            return;
        } else if (ret < 0) {
            PyErr_SetString(PyExc_ValueError, "unacceptable date");
            return;
        }
    END_LOOP(24)
}

static PyUFuncGenericFunction eraAtco13_functions[] = { eraAtco13_wrapper };
static void *eraAtco13_data[] = {NULL};
static char eraAtco13_types[] = {
    NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE,
    NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE,
    NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE,
    NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE, NPY_DOUBLE };


static void
eraD2dtf_wrapper(char **args, intp *dimensions, intp *steps, void *extra)
{
    int ret;
    int ihmsf[4];

    BEGIN_LOOP
        ret = eraD2dtf(
            (char *)args[0],
            *(int *)args[1],
            *(double *)args[2],
            *(double *)args[3],
            (int *)args[4],
            (int *)args[5],
            (int *)args[6],
            ihmsf);

        if (ret > 0) {
            PyErr_SetString(PyExc_ValueError, "dubious year");
            return;
        } else if (ret < 0) {
            PyErr_SetString(PyExc_ValueError, "unacceptable date");
            return;
        }

        *(int *)args[7] = ihmsf[0];
        *(int *)args[8] = ihmsf[1];
        *(int *)args[9] = ihmsf[2];
        *(int *)args[10] = ihmsf[3];
    END_LOOP(11)
}

static PyUFuncGenericFunction eraD2dtf_functions[] = { eraD2dtf_wrapper };
static void *eraD2dtf_data[] = {NULL};
static char eraD2dtf_types[] = {
    NPY_STRING, NPY_INT, NPY_DOUBLE, NPY_DOUBLE, NPY_INT, NPY_INT, NPY_INT,
    NPY_INT, NPY_INT, NPY_INT, NPY_INT };


/*///////////////////////////////////////////////////////////////////////////
  module level
*/

#if defined(NPY_PY3K)
static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "c_ufunc",
        NULL,
        -1,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
};
#endif

#if defined(NPY_PY3K)
#define RETVAL m
PyObject *PyInit_c_ufunc(void)
#else
#define RETVAL
PyMODINIT_FUNC
initc_ufunc(void)
#endif
{
    PyObject *m;
    PyObject *d;
    PyObject *f;

#if defined(NPY_PY3K)
    m = PyModule_Create(&moduledef);
#else
    m = Py_InitModule("c_ufunc", NULL);
#endif
    if (m == NULL)
        return RETVAL;

    import_array();
    import_ufunc();

    d = PyModule_GetDict(m);

    f = PyUFunc_FromFuncAndData(
        eraAtco13_functions, eraAtco13_data, eraAtco13_types, 1, 18, 6,
        PyUFunc_None, "eraAtco13", "eraAtco13", 0);
    PyDict_SetItemString(d, "atco13", f);
    Py_DECREF(f);

    f = PyUFunc_FromFuncAndData(
        eraD2dtf_functions, eraD2dtf_data, eraD2dtf_types, 1, 4, 7,
        PyUFunc_None, "eraD2dtf", "eraD2dtf", 0);
    PyDict_SetItemString(d, "eraD2dtf", f);
    Py_DECREF(f);

    return RETVAL;
}
