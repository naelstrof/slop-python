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
    if (!PyArg_ParseTupleAndKeywords(args, keywords, "|$fffiiiiO!ffffsi", skeywords,
         &(options.border),
         &(options.padding),
         &(options.tolerance),
         &(options.highlight),
         &(options.noopengl),
         &(options.nokeyboard),
         &(options.nodecorations),
         &PyList_Type,
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
        int numLines;
        line[0] = '\0';
        char* element;
        PyObject* strObj;  
        numLines = PyList_Size(shaderlist);
        if ( numLines < 0 ) {
            PyErr_SetString(SlopError, "`shaders` must have a type of list if given.");
            return NULL;
        }
        for (int i=0; i<numLines; i++){
            strObj = PyList_GetItem(shaderlist, i);
            element = PyBytes_AsString( strObj );

            char* comma = ",";
            char* new_str;
            new_str = malloc(strlen(line)+strlen(element)+2);
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
