#include <Python.h>
#include <phoebe/phoebe.h>


static PyObject *phoebeInit(PyObject *self, PyObject *args)
{
	int status = phoebe_init();
	if (status != SUCCESS) {
		printf ("%s", phoebe_error (status));
		return NULL;
	}

	return Py_BuildValue ("i", status);
}

static PyObject *phoebeConfigure(PyObject *self, PyObject *args)
{
	int status = phoebe_configure();
	if (status != SUCCESS) {
		printf ("%s", phoebe_error (status));
		return NULL;
	}

	return Py_BuildValue ("i", status);
}

static PyObject *phoebeQuit(PyObject *self, PyObject *args)
{
    int status = phoebe_quit();
    return Py_BuildValue("i", status);
}

static PyObject *phoebeOpen(PyObject *self, PyObject *args)
{
    char *fname;
    int status;
    
    PyArg_ParseTuple(args, "s", &fname);
    status = phoebe_open_parameter_file(fname);
	if (status != SUCCESS) {
		printf ("%s", phoebe_error (status));
		return NULL;
	}

	return Py_BuildValue ("i", status);
}

static PyObject *phoebeCheck(PyObject *self, PyObject *args)
{
    char *parname;
    PHOEBE_parameter *par;
    
    PyArg_ParseTuple(args, "s", &parname);
    par = phoebe_parameter_lookup(parname);
    
    if (phoebe_parameter_is_within_limits(par))
        return Py_BuildValue("i", 1);
    else
        return Py_BuildValue("i", 0);
}

static PyObject *phoebeCFVal(PyObject *self, PyObject *args)
{
    int index, status, lexp;
    double cf, sigma;
    char *rstr;
    
    PHOEBE_curve *obs, *syn;
    
    PyArg_ParseTuple(args, "d", &index);
    
    obs = phoebe_curve_new_from_pars (PHOEBE_CURVE_LC, index);
    phoebe_curve_transform (obs, obs->itype, PHOEBE_COLUMN_FLUX, PHOEBE_COLUMN_SIGMA);
    phoebe_parameter_get_value (phoebe_parameter_lookup ("phoebe_lc_sigma"), index, &sigma);
    phoebe_parameter_get_value (phoebe_parameter_lookup ("phoebe_lc_levweight"), index, &rstr);
	lexp = intern_get_level_weighting_id (rstr);
    
    syn = phoebe_curve_new ();
    phoebe_curve_compute (syn, obs->indep, index, obs->itype, PHOEBE_COLUMN_FLUX);
    
    status = phoebe_cf_compute (&cf, PHOEBE_CF_CHI2, syn->dep, obs->dep, obs->weight, sigma, lexp, 1.0);
    if (status != SUCCESS) {
		printf ("%s", phoebe_error (status));
		return NULL;
	}
	
	return Py_BuildValue ("d", cf);
}

static PyObject *phoebeSetLim(PyObject *self, PyObject *args)
{
    int status;
    char *parname;
    double parmin, parmax;
    PHOEBE_parameter *par;
    
    PyArg_ParseTuple(args, "sdd", &parname, &parmin, &parmax);
    
    par = phoebe_parameter_lookup(parname);
    status = phoebe_parameter_set_limits(par, parmin, parmax);
    if (status != SUCCESS) {
		printf ("%s", phoebe_error (status));
		return NULL;
	}
	
	return Py_BuildValue ("i", status);
}

static PyObject *phoebeSetPar(PyObject *self, PyObject *args)
{
    int index, status;
    char *parname;
    double val;
    PHOEBE_parameter *par;
    
    PyArg_ParseTuple(args, "sd|i", &parname, &val, &index);
    par = phoebe_parameter_lookup(parname);
    switch (par->type) {
        case TYPE_DOUBLE:
            status = phoebe_parameter_set_value(par, val);
            break;
        case TYPE_DOUBLE_ARRAY:
            status = phoebe_parameter_set_value(par, val, index);
            break;
        default:
            status = 0;
            printf("not yet implemented, sorry.\n");
            break;
    }
    
    if (status != SUCCESS) {
		printf ("%s", phoebe_error (status));
		return NULL;
	}
	
	return Py_BuildValue ("i", status);
}

static PyObject *phoebeGetPar(PyObject *self, PyObject *args)
{
    int index, status;
    char *parname;
    double val;
    PHOEBE_parameter *par;

    PyArg_ParseTuple(args, "s|i", &parname, &index);
    par = phoebe_parameter_lookup(parname);
    switch (par->type) {
        case TYPE_INT: {
            int ival;
            status = phoebe_parameter_get_value(par, &ival);
            val = ival;
            break;
        }
        case TYPE_DOUBLE:
            status = phoebe_parameter_get_value(par, &val);
            break;
        case TYPE_DOUBLE_ARRAY:
            status = phoebe_parameter_get_value(par, index, &val);
            break;
        default:
            status = 0;
            printf("not yet implemented, sorry.\n");
            break;
    }

    if (status != SUCCESS) {
		printf ("%s", phoebe_error (status));
		return NULL;
	}
	
	return Py_BuildValue ("d", val);
}

static PyObject *phoebeLC(PyObject *self, PyObject *args)
{
    int index, tlen, i, status;
    PyObject *obj, *ret;
    char *rstr;
    
    PHOEBE_column_type itype;
    PHOEBE_vector *indep;
    PHOEBE_curve *curve;
    
    if (!PyArg_ParseTuple(args, "Oi", &obj, &index) || !PyTuple_Check(obj))
        return NULL;
    
    tlen = PyTuple_Size(obj);
    indep = phoebe_vector_new();
    phoebe_vector_alloc(indep, tlen);
    for (i = 0; i < tlen; i++)
        indep->val[i] = PyFloat_AsDouble(PyTuple_GetItem(obj, i));    
    
    phoebe_parameter_get_value (phoebe_parameter_lookup ("phoebe_indep"), &rstr);
	status = phoebe_column_get_type (&itype, rstr);
	
	curve = phoebe_curve_new();
	status = phoebe_curve_compute(curve, indep, index, itype, PHOEBE_COLUMN_FLUX);

    ret = PyTuple_New(tlen);
    for (i = 0; i < tlen; i++)
        PyTuple_SetItem(ret, i, Py_BuildValue("d", curve->dep->val[i]));

	phoebe_curve_free(curve);
	phoebe_vector_free(indep);

    return ret;
}

static PyObject *phoebeParameter (PyObject *self, PyObject *args)
{
	/**
	 * phoebeParameter:
	 * 
	 * Packs all PHOEBE_parameter properties into a list to be parsed in
	 * python into the parameter class. The following fields are parsed:
	 *
	 *   parameter->qualifier
	 *   parameter->description
	 *   parameter->kind
	 *   parameter->format
	 */
	
	PyObject *list;
	PHOEBE_parameter *par;
	char *qualifier;
	int i;
	
	PyArg_ParseTuple (args, "s", &qualifier);
	par = phoebe_parameter_lookup (qualifier);
	if (!par) return Py_BuildValue ("");
	
	list = PyList_New (8);

	PyList_SetItem (list, 0, Py_BuildValue ("s", par->qualifier));
	PyList_SetItem (list, 1, Py_BuildValue ("s", par->description));
	PyList_SetItem (list, 2, Py_BuildValue ("i", par->kind));
	PyList_SetItem (list, 3, Py_BuildValue ("s", par->format));
	PyList_SetItem (list, 4, Py_BuildValue ("d", par->min));
	PyList_SetItem (list, 5, Py_BuildValue ("d", par->max));
	PyList_SetItem (list, 6, Py_BuildValue ("d", par->step));

	switch (par->type) {
		case TYPE_INT:
			PyList_SetItem (list, 7, Py_BuildValue ("i", par->value.i));
		break;
		case TYPE_BOOL:
			PyList_SetItem (list, 7, Py_BuildValue ("b", par->value.b));
		break;
		case TYPE_DOUBLE:
			PyList_SetItem (list, 7, Py_BuildValue ("d", par->value.d));
		break;
		case TYPE_STRING:
			PyList_SetItem (list, 7, Py_BuildValue ("s", par->value.str));
		break;
		case TYPE_INT_ARRAY: {
			int i;
			PyObject *array = PyList_New (par->value.array->dim);
			for (i = 0; i < par->value.array->dim; i++)
				PyList_SetItem (array, i, Py_BuildValue ("i", par->value.array->val.iarray));
			PyList_SetItem (list, 7, array);
		}
		break;
		case TYPE_BOOL_ARRAY: {
			PyObject *array = PyList_New (par->value.array->dim);
			for (i = 0; i < par->value.array->dim; i++)
				PyList_SetItem (array, i, Py_BuildValue ("b", par->value.array->val.barray));
			PyList_SetItem (list, 7, array);
		}
		break;
		case TYPE_DOUBLE_ARRAY: {
			PyObject *array = PyList_New (par->value.array->dim);
			for (i = 0; i < par->value.array->dim; i++)
				PyList_SetItem (array, i, Py_BuildValue ("d", par->value.array->val.darray));
			PyList_SetItem (list, 7, array);
		}
		break;
		case TYPE_STRING_ARRAY: {
			PyObject *array = PyList_New (par->value.array->dim);
			for (i = 0; i < par->value.array->dim; i++)
				PyList_SetItem (array, i, Py_BuildValue ("s", par->value.array->val.strarray));
			PyList_SetItem (list, 7, array);
		}
		break;
		default:
			/* If we end up here, yell and scream! */
			printf ("exception encountered in phoebe_backend.c, phoebeParameter().\n");
		break;
	}

	return list;
}

static PyMethodDef PhoebeMethods[] = {
	{"init",             phoebeInit,       METH_VARARGS, "Initialize PHOEBE backend"},
	{"configure",        phoebeConfigure,  METH_VARARGS, "Configure all internal PHOEBE structures"},
	{"quit",             phoebeQuit,       METH_VARARGS, "Quit PHOEBE"},
	{"open",             phoebeOpen,       METH_VARARGS, "Open PHOEBE parameter file"},
	{"cfval",            phoebeCFVal,      METH_VARARGS, "Compute a cost function value of the passed curve"},
    {"check",            phoebeCheck,      METH_VARARGS, "Check whether the parameter is within bounds"},
    {"setpar",           phoebeSetPar,     METH_VARARGS, "Set the value of the parameter"},
    {"getpar",           phoebeGetPar,     METH_VARARGS, "Get the value of the parameter"},
    {"setlim",           phoebeSetLim,     METH_VARARGS, "Set parameter limits"},
    {"lc",               phoebeLC,         METH_VARARGS, "Compute light curve"},
	{"parameter",        phoebeParameter,  METH_VARARGS, "Return a list of parameter properties"},
	{NULL,               NULL,             0,            NULL}
};

PyMODINIT_FUNC initphoebeBackend (void)
{
	PyObject *backend = Py_InitModule ("phoebeBackend", PhoebeMethods);
	if (!backend)
		return;
}
