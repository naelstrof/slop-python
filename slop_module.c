#include "slop_module.h"

PyObject* slop_python_select( PyObject* self, PyObject* args, PyObject* keywords ) {
    struct slop_options options = slop_options_default(options);
    static char *skeywords[] = {"border",
                                "padding",
                                "tolerance",
                                "highlight",
                                "noopengl",
                                "nokeyboard",
                                "nodecorations",
                                "shaders",
                                "r",
                                "g",
                                "b",
                                "a",
                                "xdisplay",
                                "quiet",
                                NULL};
    PyObject* shaderlist = NULL;
    if (!PyArg_ParseTupleAndKeywords(args, keywords, "|$fffiiiiOffffsi", skeywords,
         &(options.border),
         &(options.padding),
         &(options.tolerance),
         &(options.highlight),
         &(options.noopengl),
         &(options.nokeyboard),
         &(options.nodecorations),
         &(shaderlist),
         &(options.r),
         &(options.g),
         &(options.b),
         &(options.a),
         &(options.xdisplay),
         &(options.quiet))) {
        return NULL;
    }

    // Concat all of the strings in the shader list.
    char* line = malloc(1);
    if ( shaderlist ) {
        Py_ssize_t numLines;
        line[0] = '\0';
        const char* element = NULL;
        PyObject* strObj;  
        numLines = PyList_Size(shaderlist);
        if ( numLines <= 0 ) {
            PyErr_SetString(SlopError, "`shaders` must have a type of list, and contain strings if given.");
            return NULL;
        }
        for (Py_ssize_t i=0; i<numLines; i++) {
            strObj = PyList_GetItem(shaderlist, i);
            if (!PyUnicode_Check( strObj )) {
                PyErr_SetString(SlopError, "Contents of list `shaders` must have a type of string if given.");
                return NULL;
            }
            PyObject* pyString = PyUnicode_AsEncodedString(strObj, "utf-8", "Error ~");
            element = PyBytes_AS_STRING(pyString);
            if ( line[0] == '\0' ) {
                line = malloc(strlen(element)+1);
                memcpy( line, element, strlen(element) );
                line[strlen(element)+1] = '\0';
                continue;
            }
            char* comma = ",";
            char* new_str;
            new_str = malloc(strlen(line)+strlen(element)+strlen(comma)+2);
            new_str[0] = '\0';
            strcat(new_str,line);
            strcat(new_str,comma);
            strcat(new_str,element);
            free( line );
            line = new_str;
        }
        options.shaders = line;
    }

    struct slop_selection selection = slop_select(&options);
    PyObject* returnDict = PyDict_New();
    PyDict_SetItemString( returnDict, "x", PyLong_FromLong( selection.x ) );
    PyDict_SetItemString( returnDict, "y", PyLong_FromLong( selection.y ) );
    PyDict_SetItemString( returnDict, "w", PyLong_FromLong( selection.w ) );
    PyDict_SetItemString( returnDict, "h", PyLong_FromLong( selection.h ) );
    PyDict_SetItemString( returnDict, "id", PyLong_FromLong( selection.id ) );
    PyDict_SetItemString( returnDict, "cancelled", PyLong_FromLong( selection.cancelled ) );
    free( line );
    return returnDict;
}
