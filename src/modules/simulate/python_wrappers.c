/* Provides Python wrappers for functions and classes. */

#include <Python.h>
#include <stdbool.h>
#include "simulate.c"

typedef struct Board_struct {
    PyObject_HEAD
    bool** board;
    int m;
    int n;
} Board;

// Initializes a new Board object with the given type, sets board to NULL, m and n to 0, and returns the newly allocated object.
static PyObject* Board_new(PyTypeObject* type, PyObject* args, PyObject* kwargs) {
    Board* self = NULL;
    if (type == NULL) {
        PyErr_SetString(PyExc_TypeError, "Type is NULL");
        return NULL;
    }
    self = (Board*) type->tp_alloc(type, 0);
    if (self == NULL) {
        PyErr_SetString(PyExc_MemoryError, "Failed to allocate Board");
        return NULL;
    }
    return (PyObject*) self;
}

/**
 * Initializes a Board object with the given dimensions.
 *
 * @param self A pointer to the Board object.
 * @param args A tuple containing two integers: the number of rows and columns.
 * @param kwargs A dictionary of keyword arguments.
 *
 * @return An integer indicating the success of the initialization.
 *         Returns -1 if the arguments cannot be parsed, or if memory allocation fails.
 *
 * @throws PyExc_MemoryError if memory allocation fails.
 */
static int Board_init(Board* self, PyObject* args, PyObject* kwargs) {
    if (!PyArg_ParseTuple(args, "ii", &self->m, &self->n)) {
        return -1;
    }
    self->board = allocate_board(self->m, self->n);
    if (self->board == NULL) {
        PyErr_SetString(PyExc_MemoryError, "Out of memory");
        return -1;
    }
    initialize_board(self->board, self->m, self->n);
    return 0;
}

/**
 * Executes a single iteration of the game of life on the given board.
 *
 * @param self A pointer to the Board object.
 * @param Py_UNUSED(ignored) A PyObject* that is ignored.
 *
 * @return A PyObject* that represents None.
 *
 * @throws PyExc_RuntimeError if the iteration fails.
 */
static PyObject* Board_iterate_once(Board* self, PyObject* Py_UNUSED(ignored)) {
    bool** new_board = iterate_once(self->board, self->m, self->n);
    if (new_board == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "Iteration failed");
    }
    free_board(self->board, self->m, self->n);
    self->board = new_board;
    Py_RETURN_NONE;
}


/**
 * Resizes the board of the given Board object.
 *
 * @param self A pointer to the Board object.
 * @param args A tuple containing two integers: the new number of rows and columns.
 *
 * @return Py_RETURN_NONE if the resizing is successful.
 *         NULL if the arguments cannot be parsed.
 *
 * @throws PyExc_MemoryError if memory allocation fails.
 */
static PyObject* Board_resize(Board* self, PyObject* args) {
    int m, n;
    if (!PyArg_ParseTuple(args, "ii", &m, &n)) {
        return NULL;
    }
    bool** new_board = reallocate_board(self->board, self->m, self->n, m, n);
    if (new_board == NULL) {
        PyErr_SetString(PyExc_MemoryError, "Failed to allocate new board");
        return NULL;
    }
    free_board(self->board, self->m, self->n);
    self->board = new_board;
    self->m = m;
    self->n = n;
    Py_RETURN_NONE;
}

/**
 * Retrieves the value of a cell in the game board.
 *
 * @param self A pointer to the Board object.
 * @param args A tuple containing two integers: the row index and column index.
 *
 * @return A PyBoolObject representing the value of the cell.
 *
 * @throws PyExc_TypeError if the arguments cannot be parsed.
 * @throws PyExc_IndexError if the row or column index is out of bounds.
 */
static PyObject* Board_get_cell(Board* self, PyObject* args) {
    int i, j;
    if (!PyArg_ParseTuple(args, "ii", &i, &j)) {
        return NULL;
    }
    if (i < 0 || i >= self->m || j < 0 || j >= self->n) {
        PyErr_SetString(PyExc_IndexError, "Index out of bounds");
        return NULL;
    }
    return PyBool_FromLong(self->board[i][j]);
}

/**
 * Sets the value of a cell in the game board.
 *
 * @param self A pointer to the Board object.
 * @param args A tuple containing three integers: the row index, column index, and the value to set.
 * @return Py_RETURN_NONE if the cell is successfully set, or NULL if the arguments cannot be parsed.
 *
 * @throws PyExc_IndexError if the row or column index is out of bounds.
 * @throws PyExc_TypeError if the value is not 0 or 1.
 */
static PyObject* Board_set_cell(Board* self, PyObject* args) {
    int i, j, value;
    if (!PyArg_ParseTuple(args, "iii", &i, &j, &value)) {
        return NULL;
    }
    if (i < 0 || i >= self->m || j < 0 || j >= self->n) {
        PyErr_SetString(PyExc_IndexError, "Index out of bounds");
        return NULL;
    }
    if (value != 0 && value != 1) {
        PyErr_SetString(PyExc_TypeError, "Value must be 0 or 1");
        return NULL;
    }
    self->board[i][j] = (bool) value;
    Py_RETURN_NONE;
}

/**
 * Retrieves the value of the 'm' attribute from the given Board object and returns it as a Python long integer.
 *
 * @param self A pointer to the Board object.
 * @param Py_UNUSED(ignored) An unused parameter.
 *
 * @return A Python long integer representing the value of the 'm' attribute.
 *
 * @throws None.
 */
static PyObject* Board_get_m(Board* self, PyObject* Py_UNUSED(ignored)) {
    return PyLong_FromLong(self->m);
}

/**
 * Retrieves the value of the 'n' attribute from the given Board object and returns it as a Python long integer.
 *
 * @param self A pointer to the Board object.
 * @param Py_UNUSED(ignored) An unused parameter.
 *
 * @return A Python long integer representing the value of the 'n' attribute.
 *
 * @throws None.
 */
static PyObject* Board_get_n(Board* self, PyObject* Py_UNUSED(ignored)) {
    return PyLong_FromLong(self->n);
}

/**
 * Deallocates the memory used by the Board object.
 *
 * @param self A pointer to the Board object to be deallocated.
 *
 * @return None.
 *
 * @throws None.
 */
static void Board_dealloc(Board* self) {
    free_board(self->board, self->m, self->n);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyMethodDef Board_methods[] = {
    {
        "iterate_once",
        (PyCFunction) Board_iterate_once,
        METH_NOARGS,
        "Executes a single iteration of the Game of Life on a given board represented as a list of lists of booleans."
    },
    {
        "resize",
        (PyCFunction) Board_resize,
        METH_VARARGS,
        "Resizes the board to the given dimensions."
    },
    {
        "get_cell",
        (PyCFunction) Board_get_cell,
        METH_VARARGS,
        "Returns the value of a cell in the board."
    },
    {
        "set_cell",
        (PyCFunction) Board_set_cell,
        METH_VARARGS,
        "Sets the value of a cell in the board."
    },
    {
        "get_m",
        (PyCFunction) Board_get_m,
        METH_NOARGS,
        "Returns the number of rows in the board."
    },
    {
        "get_n",
        (PyCFunction) Board_get_n,
        METH_NOARGS,
        "Returns the number of columns in the board."
    },
    {NULL, NULL, 0, NULL}
};

static PyTypeObject BoardType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "Board",
    .tp_doc = "Representation of the board of the game of life.",
    .tp_basicsize = sizeof(Board),
    .tp_new = (newfunc) Board_new,
    .tp_init = (initproc) Board_init,
    .tp_dealloc = (destructor) Board_dealloc,
    .tp_methods = Board_methods
};

static struct PyModuleDef simulate = {
    PyModuleDef_HEAD_INIT,
    "simulate",
    "A simulation of Conway's game of life.",
    -1
};

/**
 * Initializes the `simulate` module and returns a pointer to the created module object.
 *
 * @return A pointer to the created module object.
 */
PyMODINIT_FUNC PyInit_simulate(void) {
    PyObject* module;

    if (PyType_Ready(&BoardType) < 0) {
        return NULL;
    }

    module = PyModule_Create(&simulate);
    if (module == NULL) {
        return NULL;
    }

    Py_INCREF(&BoardType);
    if (PyModule_AddObject(module, "Board", (PyObject*) &BoardType) < 0) {
        Py_DECREF(&BoardType);
        Py_DECREF(module);
        return NULL;
    }
    return module;
}
