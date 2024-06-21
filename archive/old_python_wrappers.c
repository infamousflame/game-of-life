/* Provides Python wrappers for some functions. */

#include <Python.h>
#include "simulate.c"


/**
 * Executes a single iteration of the Game of Life on a given board represented as a list of lists of booleans.
 *
 * @param self A pointer to the Python object.
 * @param args A tuple containing a single element, a list of lists of booleans representing the board.
 * @return None.
 * @throws TypeError if the input is not a list of lists of booleans.
 * @throws ValueError if the input is empty or not a square board.
 * @throws MemoryError if memory allocation fails.
 * @throws RuntimeError if the iteration fails.
 */
static PyObject* py_iterate_once(PyObject* self, PyObject* args) {
    PyObject* py_board;
    if (!PyArg_ParseTuple(args, "O", &py_board)) {
        return NULL;
    }

    if (!PyList_Check(py_board)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list of lists of booleans");
        return NULL;
    }

    int m = PyList_Size(py_board);
    if (m == 0) {
        PyErr_SetString(PyExc_ValueError, "Expected a non-empty list");
        return NULL;
    }

    int n = PyList_Size(PyList_GetItem(py_board, 0));
    if (n == 0) {
        PyErr_SetString(PyExc_ValueError, "Expected a non-empty list");
        return NULL;
    }

    bool** board = allocate_board(m, n);
    if (board == NULL) {
        PyErr_SetString(PyExc_MemoryError, "Out of memory");
        return NULL;
    }

    for (int i = 0; i < m; i++) {
        PyObject* py_row = PyList_GetItem(py_board, i);
        if (!PyList_Check(py_row)) {
            free_board(board, m, n);
            PyErr_SetString(PyExc_TypeError, "Expected a list of lists of booleans");
            return NULL;
        }

        if (PyList_Size(py_row) != n) {
            free_board(board, m, n);
            PyErr_SetString(PyExc_ValueError, "Expected a square board");
            return NULL;
        }

        for (int j = 0; j < n; j++) {
            board[i][j] = PyObject_IsTrue(PyList_GetItem(py_row, j));
        }
    }

    bool** new_board = iterate_once(board, m, n);
    free_board(board, m, n);
    if (new_board == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "Iteration failed");
        return NULL;
    }

    for (int i = 0; i < m; i++) {
        PyObject* py_row = PyList_GetItem(py_board, i);
        for (int j = 0; j < n; j++) {
            PyObject_SetItem(py_row, PyLong_FromLong(j), PyBool_FromLong(new_board[i][j]));
        }
    }

    free_board(new_board, m, n);
    Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
    {"iterate_once", py_iterate_once, METH_VARARGS, "Update a board in place and return None."},
    {NULL, NULL, 0, NULL},
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "simulate",
    "A simulation of Conway's game of life.",
    -1,
    methods,
};


/**
 * Initializes the `simulate` module and returns a pointer to the created module object.
 *
 * @return A pointer to the created module object.
 */
PyMODINIT_FUNC PyInit_simulate(void) {
    return PyModule_Create(&module);
}
