#include <Python.h>
#include <numpy/arrayobject.h>
#include <phoebe_phoenix/phoebe.h>
#include <string.h>
#include <math.h>

#if PY_MAJOR_VERSION >= 3
#define PY3K
#endif

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

static PyObject *phoebeRoleReverse(PyObject *self, PyObject *args)
{
    int lcno, rvno, i;
    double pot1, pot2, pot1n, pot2n, q, pshift, perr0, c1, c2;

    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_pot1"), &pot1);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_pot2"), &pot2);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_rm"), &q);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_pshift"), &pshift);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_perr0"), &perr0);

    pot1n = pot2/q + (q-1)/2/q;
    pot2n = pot1/q + (q-1)/2/q;
    q = 1/q;
    pshift = pshift > 0.5 ? pshift - 0.5 : pshift + 0.5;
    perr0 = perr0 > 3.1415926 ? perr0 - 3.1415926 : perr0 + 3.1415926;

    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_lcno"), &lcno);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_rvno"), &rvno);

    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_pot1"), pot1n);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_pot2"), pot2n);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_rm"), q);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_pshift"), pshift);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_perr0"), perr0);

    for (i = 0; i < lcno; i++) {
        phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_hla"), i, &c1);
        phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_cla"), i, &c2);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_hla"), i, c2);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_cla"), i, c1);

        phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_ld_lcx1"), i, &c1);
        phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_ld_lcx2"), i, &c2);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_lcx1"), i, c2);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_lcx2"), i, c1);

        phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_ld_lcy1"), i, &c1);
        phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_ld_lcy2"), i, &c2);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_lcy1"), i, c2);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_lcy2"), i, c1);
    }

    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_teff1"), &c1);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_teff2"), &c2);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_teff1"), c2);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_teff2"), c1);

    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_f1"), &c1);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_f2"), &c2);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_f1"), c2);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_f2"), c1);

    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_alb1"), &c1);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_alb2"), &c2);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_alb1"), c2);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_alb2"), c1);

    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_grb1"), &c1);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_grb2"), &c2);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_grb1"), c2);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_grb2"), c1);

    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_ld_xbol1"), &c1);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_ld_xbol2"), &c2);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_xbol1"), c2);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_xbol2"), c1);

    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_ld_ybol1"), &c1);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_ld_ybol2"), &c2);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_ybol1"), c2);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_ybol2"), c1);

    return Py_BuildValue ("");
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

static PyObject *phoebeSave(PyObject *self, PyObject *args)
{
    char *fname;
    int status;

    PyArg_ParseTuple(args, "s", &fname);
    status = phoebe_save_parameter_file(fname);
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

static PyObject *phoebePBLum(PyObject *self, PyObject *args)
{
    int i, index;
    double sigma, num, denom, Lpb, hla;

    PHOEBE_curve *obs, *syn;

    PyArg_ParseTuple(args, "i", &index);

    obs = phoebe_curve_new_from_pars(PHOEBE_CURVE_LC, index);
    phoebe_curve_transform(obs, obs->itype, PHOEBE_COLUMN_FLUX, PHOEBE_COLUMN_SIGMA);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_lc_sigma"), index, &sigma);

    syn = phoebe_curve_new();
    phoebe_curve_compute(syn, obs->indep, index, obs->itype, PHOEBE_COLUMN_FLUX, NULL, NULL, NULL);

    num = 0.0;
    denom = 0.0;
    for (i = 0; i < syn->dep->dim; i++) {
        num += syn->dep->val[i]*obs->dep->val[i]/obs->weight->val[i]/obs->weight->val[i];
        denom += syn->dep->val[i]*syn->dep->val[i]/obs->weight->val[i]/obs->weight->val[i];
    }
    Lpb = num/denom;

    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_hla"), index, &hla);

    return Py_BuildValue("d", Lpb*hla);
}

static PyObject *phoebeCFVal(PyObject *self, PyObject *args)
{
    int i, index, status, lexp, scale, retlum;
    double cf, sigma, num, denom, Lpb = 0.0;
    char *rstr, *ctype;

    PHOEBE_curve *obs, *syn;

    scale = 0;
    PyArg_ParseTuple(args, "si|ii", &ctype, &index, &scale, &retlum);

    if (strcmp(ctype, "lc") == 0 || strcmp(ctype, "LC") == 0) {
        obs = phoebe_curve_new_from_pars(PHOEBE_CURVE_LC, index);
        phoebe_curve_transform(obs, obs->itype, PHOEBE_COLUMN_FLUX, PHOEBE_COLUMN_SIGMA);
        phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_lc_sigma"), index, &sigma);
        phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_lc_levweight"), index, &rstr);
        lexp = intern_get_level_weighting_id(rstr);

        syn = phoebe_curve_new();
        phoebe_curve_compute(syn, obs->indep, index, obs->itype, PHOEBE_COLUMN_FLUX, NULL, NULL, NULL);
    }

    else if (strcmp(ctype, "rv") == 0 || strcmp(ctype, "RV") == 0) {
        obs = phoebe_curve_new_from_pars(PHOEBE_CURVE_RV, index);
        phoebe_curve_transform(obs, obs->itype, obs->dtype, PHOEBE_COLUMN_SIGMA);
        phoebe_parameter_get_value(phoebe_parameter_lookup ("phoebe_rv_sigma"), index, &sigma);
        lexp = 0;

        syn = phoebe_curve_new();
        phoebe_curve_compute(syn, obs->indep, index, obs->itype, obs->dtype, NULL, NULL, NULL);
    }

    else {
        printf("passed curve type %s is invalid, aborting.", ctype);
        return NULL;
    }

    if (scale == 0) {
        status = phoebe_cf_compute(&cf, PHOEBE_CF_CHI2, syn->dep, obs->dep, obs->weight, sigma, lexp, 1.0);
        if (status != SUCCESS) {
            printf("%s", phoebe_error (status));
            return NULL;
        }
    }
    else {
        num = 0.0;
        denom = 0.0;
        for (i = 0; i < syn->dep->dim; i++) {
            num += syn->dep->val[i]*obs->dep->val[i]/obs->weight->val[i]/obs->weight->val[i];
            denom += syn->dep->val[i]*syn->dep->val[i]/obs->weight->val[i]/obs->weight->val[i];
        }
        Lpb = num/denom;

        //~ for (i = 0; i < syn->dep->dim; i++)
            //~ printf("%lf %lf %lf %lf\n", syn->indep->val[i], obs->dep->val[i], syn->dep->val[i], Lpb*syn->dep->val[i]);

        cf = 0.0;
        for (i = 0; i < syn->dep->dim; i++)
            cf += (obs->dep->val[i]-Lpb*syn->dep->val[i])*(obs->dep->val[i]-Lpb*syn->dep->val[i])/obs->weight->val[i]/obs->weight->val[i];
    }

    if (scale == 0 || (scale == 1 && retlum == 0))
        return Py_BuildValue("d", cf/sigma/sigma);
    else
        return Py_BuildValue ("(d,d)", cf/sigma/sigma, Lpb);
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

static PyObject *phoebeGetLim(PyObject *self, PyObject *args)
{
    int status;
    char *parname;
    double parmin, parmax;
    PHOEBE_parameter *par;

    PyArg_ParseTuple(args, "s", &parname);

    par = phoebe_parameter_lookup(parname);
    status = phoebe_parameter_get_limits(par, &parmin, &parmax);
    if (status != SUCCESS) {
        printf ("%s", phoebe_error (status));
        return NULL;
    }

    return Py_BuildValue ("(d,d)", parmin, parmax);
}

static PyObject *phoebeSetPar(PyObject *self, PyObject *args)
{
    int index, status;
    char *parname;
    PyObject *parval;
    PHOEBE_parameter *par;

    PyArg_ParseTuple(args, "sO|i", &parname, &parval, &index);
    par = phoebe_parameter_lookup(parname);
    switch (par->type) {
        case TYPE_INT: {
#ifdef PY3K
            long val;
            if (!PyLong_Check(parval)) {
                printf("error: integer value expected for %s.\n", parname);
				return NULL;
            }
            val = PyLong_AsLong(parval);
#else
			int val;
			if (!PyInt_Check(parval)) {
				printf("error: integer value expected for %s.\n", parname);
				return NULL;
			}
			val = PyInt_AS_LONG(parval);
#endif
            status = phoebe_parameter_set_value(par, (int) val);
            break;
		}
        case TYPE_BOOL: {
			int val;
#ifdef PY3K
			if (!PyLong_Check(parval)) {
				printf("error: boolean value expected for %s.\n", parname);
				return NULL;
			}
			val = PyLong_AsLong(parval);
#else
			if (!PyInt_Check(parval)) {
				printf("error: boolean value expected for %s.\n", parname);
				return NULL;
			}
			val = PyInt_AS_LONG(parval);
#endif
            status = phoebe_parameter_set_value(par, (int) val);
            break;
		}
        case TYPE_DOUBLE: {
			double val;
			if (!PyFloat_Check(parval)) {
				printf("error: float value expected for %s.\n", parname);
				return NULL;
			}
			val = PyFloat_AS_DOUBLE(parval);
            status = phoebe_parameter_set_value(par, val);
            break;
		}
		case TYPE_STRING: {
			char *val;
#ifdef PY3K
			if (!PyUnicode_Check(parval)) {
				printf("error: string value expected for %s.\n", parname);
				return NULL;
			}
			val = PyUnicode_AsUTF8(parval);
#else
			if (!PyString_Check(parval)) {
				printf("error: string value expected for %s.\n", parname);
				return NULL;
			}
			val = PyString_AS_STRING(parval);
#endif
			status = phoebe_parameter_set_value(par, val);
			break;
		}
        case TYPE_INT_ARRAY: {
			int val;
#ifdef PY3K
			if (!PyLong_Check(parval)) {
				printf("error: float value expected for %s.\n", parname);
				return NULL;
			}
			val = PyLong_AsLong(parval);
#else
			if (!PyInt_Check(parval)) {
				printf("error: float value expected for %s.\n", parname);
				return NULL;
			}
			val = PyInt_AS_LONG(parval);
#endif
            status = phoebe_parameter_set_value(par, index, (int) val);
            break;
		}
        case TYPE_BOOL_ARRAY: {
			int val;
#ifdef PY3K
			if (!PyLong_Check(parval)) {
				printf("error: float value expected for %s.\n", parname);
				return NULL;
			}
			val = PyLong_AsLong(parval);
#else
			if (!PyInt_Check(parval)) {
				printf("error: float value expected for %s.\n", parname);
				return NULL;
			}
			val = PyInt_AS_LONG(parval);
#endif
            status = phoebe_parameter_set_value(par, index, (int) val);
            break;
		}
        case TYPE_DOUBLE_ARRAY: {
			double val;
			if (!PyFloat_Check(parval)) {
				printf("error: float value expected for %s.\n", parname);
				return NULL;
			}
			val = PyFloat_AS_DOUBLE(parval);
            status = phoebe_parameter_set_value(par, index, val);
            break;
		}
        case TYPE_STRING_ARRAY: {
			char *val;
#ifdef PY3K
			if (!PyUnicode_Check(parval)) {
				printf("error: string value expected for %s.\n", parname);
				return NULL;
			}
			val = PyUnicode_AsUTF8(parval);
#else
			if (!PyString_Check(parval)) {
				printf("error: string value expected for %s.\n", parname);
				return NULL;
			}
			val = PyString_AS_STRING(parval);
#endif
            status = phoebe_parameter_set_value(par, index, val);
            break;
		}
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
            if (status != SUCCESS) {
                printf ("%s", phoebe_error (status));
                return NULL;
            }
            return Py_BuildValue ("i", ival);
        }
        case TYPE_BOOL: {
			int bval;
			status = phoebe_parameter_get_value(par, &bval);
            if (status != SUCCESS) {
                printf ("%s", phoebe_error (status));
                return NULL;
            }
            return Py_BuildValue ("i", bval);
		}
        case TYPE_DOUBLE:
            status = phoebe_parameter_get_value(par, &val);
            break;
        case TYPE_STRING: {
			const char *strval;
			status = phoebe_parameter_get_value(par, &strval);
            if (status != SUCCESS) {
                printf ("%s", phoebe_error (status));
                return NULL;
            }
            return Py_BuildValue ("s", strval);
		}
        case TYPE_INT_ARRAY: {
            int ival;
            status = phoebe_parameter_get_value(par, index, &ival);
            if (status != SUCCESS) {
                printf ("%s", phoebe_error (status));
                return NULL;
            }
            return Py_BuildValue("i", ival);
        }
        case TYPE_BOOL_ARRAY: {
            int bval;
            status = phoebe_parameter_get_value(par, index, &bval);
            if (status != SUCCESS) {
                printf ("%s", phoebe_error (status));
                return NULL;
            }
            return Py_BuildValue("i", bval);
        }
        case TYPE_DOUBLE_ARRAY:
            status = phoebe_parameter_get_value(par, index, &val);
            break;
        case TYPE_STRING_ARRAY: {
			const char *strval;
			status = phoebe_parameter_get_value(par, index, &strval);
            if (status != SUCCESS) {
                printf ("%s", phoebe_error (status));
                return NULL;
            }
            return Py_BuildValue ("s", strval);
		}
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

static PyObject *phoebeUpdateLD(PyObject *self, PyObject *args)
{
    int lcno, rvno, i;
    char *ldname, *pbname;
    PHOEBE_passband *passband;
    LD_model ldmodel;
    double T1, T2, logg1, logg2, met1, met2;
    double pot1, pot2, sma, P, e, q, F1, F2;
    double xld, yld;

    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_lcno"), &lcno);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_rvno"), &rvno);

    /* LD model: */
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_ld_model"), &ldname);
    ldmodel = phoebe_ld_model_type(ldname);

    printf("LCs: %d; RVs: %d; LD model: %s\n", lcno, rvno, ldname);

    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_teff1"), &T1);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_teff2"), &T2);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_met1"),  &met1);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_met2"),  &met2);

    /* Compute surface gravities: */
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_pot1"),  &pot1);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_pot2"),  &pot2);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_sma"),  &sma);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_period"),  &P);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_ecc"),  &e);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_rm"),  &q);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_f1"),  &F1);
    phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_f2"),  &F2);
    phoebe_calculate_loggs(pot1, pot2, sma, P, e, q, F1, F2, &logg1, &logg2);

    printf("T1=%0.0f, T2=%0.0f; logg1=%3.3f, logg2=%3.3f; met1=%3.3f, met2=%3.3f\n", T1, T2, logg1, logg2, met1, met2);

    /* Bolometric LD coefficients first: */
    xld = yld = 0;
    passband = phoebe_passband_lookup("Bolometric:3000A-10000A");
    phoebe_ld_get_coefficients(ldmodel, passband, met1, T1, logg1, &xld, &yld);
    //~ printf("Primary star -- bolometric LDs: xld=%3.3f, yld=%3.3f\n", xld, yld);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_xbol1"), xld);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_ybol1"), yld);

    xld = yld = 0;
    phoebe_ld_get_coefficients(ldmodel, passband, met2, T2, logg2, &xld, &yld);
    //~ printf("Secondary star -- bolometric LDs: xld=%3.3f, yld=%3.3f\n", xld, yld);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_xbol2"), xld);
    phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_ybol2"), yld);

    /* LC coefficients next: */
    for (i = 0; i < lcno; i++) {
        phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_lc_filter"), i, &pbname);
        passband = phoebe_passband_lookup(pbname);
        xld = yld = 0;
        phoebe_ld_get_coefficients(ldmodel, passband, met1, T1, logg1, &xld, &yld);
        //~ printf("Primary star -- %s LDs: xld=%3.3f, yld=%3.3f\n", pbname, xld, yld);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_lcx1"), i, xld);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_lcy1"), i, yld);

        xld = yld = 0;
        phoebe_ld_get_coefficients(ldmodel, passband, met2, T2, logg2, &xld, &yld);
        //~ printf("Secondary star -- %s LDs: xld=%3.3f, yld=%3.3f\n", pbname, xld, yld);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_lcx2"), i, xld);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_lcy2"), i, yld);
    }

    /* RV coefficients next: */
    for (i = 0; i < rvno; i++) {
        phoebe_parameter_get_value(phoebe_parameter_lookup("phoebe_rv_filter"), i, &pbname);
        passband = phoebe_passband_lookup(pbname);
        xld = yld = 0;
        phoebe_ld_get_coefficients(ldmodel, passband, met1, T1, logg1, &xld, &yld);
        //~ printf("Primary star -- %s LDs: xld=%3.3f, yld=%3.3f\n", pbname, xld, yld);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_rvx1"), xld);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_rvy1"), yld);

        xld = yld = 0;
        phoebe_ld_get_coefficients(ldmodel, passband, met2, T2, logg2, &xld, &yld);
        //~ printf("Secondary star -- %s LDs: xld=%3.3f, yld=%3.3f\n", pbname, xld, yld);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_rvx2"), xld);
        phoebe_parameter_set_value(phoebe_parameter_lookup("phoebe_ld_rvy2"), yld);
    }

    return Py_BuildValue("i", 0);
}

static PyObject *phoebeData(PyObject *self, PyObject *args)
{
    int i, cidx;
    char *ctype;
    PHOEBE_curve *curve;
    PyObject *x, *y, *z, *ret;

    if (!PyArg_ParseTuple(args, "si", &ctype, &cidx)) {
        printf("parsing failed.\n");
        return NULL;
    }

    if (strcmp(ctype, "lc") == 0 || strcmp(ctype, "LC") == 0) {
        curve = phoebe_curve_new_from_pars(PHOEBE_CURVE_LC, cidx);
    }
    else {
        curve = phoebe_curve_new_from_pars(PHOEBE_CURVE_RV, cidx);
    }

    phoebe_curve_transform(curve, curve->itype, PHOEBE_COLUMN_FLUX, PHOEBE_COLUMN_SIGMA);

    x = PyTuple_New(curve->indep->dim);
    y = PyTuple_New(curve->dep->dim);
    z = PyTuple_New(curve->weight->dim);
    for (i = 0; i < curve->indep->dim; i++) {
        PyTuple_SetItem(x, i, Py_BuildValue("d", curve->indep->val[i]));
        PyTuple_SetItem(y, i, Py_BuildValue("d", curve->dep->val[i]));
        PyTuple_SetItem(z, i, Py_BuildValue("d", curve->weight->val[i]));
    }
    phoebe_curve_free(curve);

    ret = PyTuple_New(3);
    PyTuple_SetItem(ret, 0, x);
    PyTuple_SetItem(ret, 1, y);
    PyTuple_SetItem(ret, 2, z);
    return ret;
}

int intern_add_mesh_to_dict(PyObject *dict, PHOEBE_mesh *mesh, char *key, int col)
{
    int i, j;
    PyObject *tuple = PyTuple_New(mesh->verts*mesh->elems);

    for (i = 0; i < mesh->verts; i++)
        for (j = 0; j < mesh->elems; j++)
            PyTuple_SetItem(tuple, i*mesh->elems+j, Py_BuildValue("d", mesh->mesh[i][j][col]));
    PyDict_SetItem(dict, Py_BuildValue("s", key), tuple);

    return SUCCESS;
}

int intern_add_horizon_to_dict(PyObject *dict, PHOEBE_horizon *horizon)
{
    int i;
    Py_ssize_t hlen = 0;
    PyObject *rho, *theta;
    PyObject *hAc = PyTuple_New(6);
    PyObject *hAs = PyTuple_New(6);

    /* WD stores rhos and thetas in a fixed size array, but fills only
     * up to a certain element, with the remaining elements being
     * exactly 0. Here we will filter those out.
     */
    while (fabs(horizon->rho[hlen]) > 1e-6)
		hlen++;

    rho = PyTuple_New(hlen);
    theta = PyTuple_New(hlen);

    for (i = 0; i < hlen; i++) {
		PyTuple_SetItem(rho, i, Py_BuildValue("d", horizon->rho[i]));
		PyTuple_SetItem(theta, i, Py_BuildValue("d", horizon->theta[i]));
	}
	for (i = 0; i < 6; i++) {
		PyTuple_SetItem(hAc, i, Py_BuildValue("d", horizon->hAc[i]));
		PyTuple_SetItem(hAs, i, Py_BuildValue("d", horizon->hAs[i]));
	}

    PyDict_SetItem(dict, Py_BuildValue("s", "rho"), rho);
    PyDict_SetItem(dict, Py_BuildValue("s", "theta"), theta);
    PyDict_SetItem(dict, Py_BuildValue("s", "hAc"), hAc);
    PyDict_SetItem(dict, Py_BuildValue("s", "hAs"), hAs);

    return SUCCESS;
}

int intern_add_feedback_to_dict(PyObject *dict, PHOEBE_minimizer_feedback *feedback)
{
    int i, dim = feedback->qualifiers->dim;
    PyObject *qualifiers, *initvals, *newvals, *ferrors;

    qualifiers = PyTuple_New(dim);
    initvals = PyTuple_New(dim);
    newvals = PyTuple_New(dim);
    ferrors = PyTuple_New(dim);

    for (i = 0; i < feedback->qualifiers->dim; i++) {
        PyTuple_SetItem(qualifiers, i, Py_BuildValue("s", feedback->qualifiers->val.strarray[i]));
        PyTuple_SetItem(initvals, i, Py_BuildValue("d", feedback->initvals->val[i]));
        PyTuple_SetItem(newvals, i, Py_BuildValue("d", feedback->newvals->val[i]));
        PyTuple_SetItem(ferrors, i, Py_BuildValue("d", feedback->ferrors->val[i]));
    }

    PyDict_SetItem(dict, Py_BuildValue("s", "qualifiers"), qualifiers);
    PyDict_SetItem(dict, Py_BuildValue("s", "initvals"), initvals);
    PyDict_SetItem(dict, Py_BuildValue("s", "newvals"), newvals);
    PyDict_SetItem(dict, Py_BuildValue("s", "ferrors"), ferrors);

    return SUCCESS;
}

static PyObject *phoebeDC(PyObject *self, PyObject *args)
{
    /*
     * phoebeDC:
     * @self:
     * @args:
     *
     * Runs a single iteration of differential corrections.
     */

    int status;
    PHOEBE_minimizer_feedback *feedback;
    PyObject *dict;

    feedback = phoebe_minimizer_feedback_new();
    status = phoebe_minimize_using_dc (NULL, feedback);

    if (status != SUCCESS) {
		printf("%s", phoebe_error(status));
        return Py_BuildValue ("i", status);
	}
	else {
        dict = PyDict_New();
        intern_add_feedback_to_dict(dict, feedback);
        return dict;
	}

}

static PyObject *phoebeLC(PyObject *self, PyObject *args)
{
    int status;
    int index, i;
    PyObject *obj, *lc, *combo = NULL, *ts = NULL;
    char *rstr;

    Py_ssize_t mswitch = 0, hswitch = 0;
    PHOEBE_column_type itype;
    PHOEBE_vector *indep;
    PHOEBE_curve *curve;
    PHOEBE_mesh *mesh1 = NULL, *mesh2 = NULL;
    PHOEBE_horizon *horizon = NULL;

    if (!PyArg_ParseTuple(args, "Oi|ii", &obj, &index, &mswitch, &hswitch)) {
        printf("parsing failed: call with lc(t_array, curve_index [, mswitch, hswitch]).\n");
        return NULL;
    }

    // printf("array type: %s\n", obj->ob_type->tp_name);

    // if (!PyArray_Check(obj)) {
    //     printf("timestamps need to be provided as a numpy-compatible array.\n");
    //     return NULL;
    // }

    // tlen = PyTuple_Size(obj);
    ts = PyArray_FromObject(obj, NPY_DOUBLE, 0, 0);
    indep = phoebe_vector_new_from_copied_data(PyArray_DATA(ts), PyArray_SIZE(ts));

    // printf("dim=%d\n", indep->dim);

    phoebe_parameter_get_value (phoebe_parameter_lookup ("phoebe_indep"), &rstr);
    phoebe_column_get_type (&itype, rstr);

    /* If mswitch is turned on, we need to store the computed meshes. */
    if (mswitch) {
        mesh1 = phoebe_mesh_new();
        mesh2 = phoebe_mesh_new();
    }

    /* If hswitch is turned on, we need to store the horizon. */
    if (hswitch) {
        horizon = phoebe_horizon_new();
    }

    curve = phoebe_curve_new();
    status = phoebe_curve_compute(curve, indep, index, itype, PHOEBE_COLUMN_FLUX, mesh1, mesh2, horizon);

    if (status != SUCCESS) {
        printf("%s", phoebe_error(status));
        return NULL;
    }

    lc = PyTuple_New(indep->dim);
    for (i = 0; i < indep->dim; i++)
        PyTuple_SetItem(lc, i, Py_BuildValue("d", curve->dep->val[i]));

	  if (mswitch || hswitch) {
        combo = PyTuple_New(1 + mswitch + hswitch);
        PyTuple_SetItem(combo, 0, lc);
	  }

    if (mswitch) {
        /* Now we need to wrap this into something nice. */
        PyObject *dict = PyDict_New();

        intern_add_mesh_to_dict(dict, mesh1, "vcx1",   0);
        intern_add_mesh_to_dict(dict, mesh1, "vcy1",   1);
        intern_add_mesh_to_dict(dict, mesh1, "vcz1",   2);
        intern_add_mesh_to_dict(dict, mesh1, "rad1",   3);
        intern_add_mesh_to_dict(dict, mesh1, "grx1",   4);
        intern_add_mesh_to_dict(dict, mesh1, "gry1",   5);
        intern_add_mesh_to_dict(dict, mesh1, "grz1",   6);
        intern_add_mesh_to_dict(dict, mesh1, "fr1",    7);
        intern_add_mesh_to_dict(dict, mesh1, "slump1", 8);
        intern_add_mesh_to_dict(dict, mesh1, "glump1", 9);
        intern_add_mesh_to_dict(dict, mesh1, "gmag1",  10);
        intern_add_mesh_to_dict(dict, mesh1, "glog1",  11);
        intern_add_mesh_to_dict(dict, mesh1, "csbt1",  12);
        intern_add_mesh_to_dict(dict, mesh1, "tloc1",  13);
        intern_add_mesh_to_dict(dict, mesh1, "Inorm1", 14);

        intern_add_mesh_to_dict(dict, mesh2, "vcx2",   0);
        intern_add_mesh_to_dict(dict, mesh2, "vcy2",   1);
        intern_add_mesh_to_dict(dict, mesh2, "vcz2",   2);
        intern_add_mesh_to_dict(dict, mesh2, "rad2",   3);
        intern_add_mesh_to_dict(dict, mesh2, "grx2",   4);
        intern_add_mesh_to_dict(dict, mesh2, "gry2",   5);
        intern_add_mesh_to_dict(dict, mesh2, "grz2",   6);
        intern_add_mesh_to_dict(dict, mesh2, "fr2",    7);
        intern_add_mesh_to_dict(dict, mesh2, "slump2", 8);
        intern_add_mesh_to_dict(dict, mesh2, "glump2", 9);
        intern_add_mesh_to_dict(dict, mesh2, "gmag2",  10);
        intern_add_mesh_to_dict(dict, mesh2, "glog2",  11);
        intern_add_mesh_to_dict(dict, mesh2, "csbt2",  12);
        intern_add_mesh_to_dict(dict, mesh2, "tloc2",  13);
        intern_add_mesh_to_dict(dict, mesh2, "Inorm2", 14);

        PyTuple_SetItem(combo, 1, dict);
    }

	if (hswitch) {
		PyObject *dict = PyDict_New();

		intern_add_horizon_to_dict(dict, horizon);

        PyTuple_SetItem(combo, 1+mswitch, dict);
	}

    phoebe_curve_free(curve);
    phoebe_vector_free(indep);
    phoebe_mesh_free(mesh1);
    phoebe_mesh_free(mesh2);
	phoebe_horizon_free(horizon);

	if (mswitch || hswitch)
        return combo;

    return lc;
}

static PyObject *phoebeRV1(PyObject *self, PyObject *args)
{
    int index, i, status;
    PyObject *obj, *ret, *ts = NULL;
    char *rstr;

    PHOEBE_column_type itype;
    PHOEBE_vector *indep;
    PHOEBE_curve *curve;

    if (!PyArg_ParseTuple(args, "Oi", &obj, &index)) {
        printf("parsing failed: call with rv1(t_array, curve_index).\n");
        return NULL;
    }

    ts = PyArray_FromObject(obj, NPY_DOUBLE, 0, 0);
    indep = phoebe_vector_new_from_copied_data(PyArray_DATA(ts), PyArray_SIZE(ts));

    phoebe_parameter_get_value (phoebe_parameter_lookup ("phoebe_indep"), &rstr);
    phoebe_column_get_type (&itype, rstr);

    curve = phoebe_curve_new();
    status = phoebe_curve_compute(curve, indep, index, itype, PHOEBE_COLUMN_PRIMARY_RV, NULL, NULL, NULL);
    if (status != SUCCESS) {
        printf("%s", phoebe_error(status));
        return NULL;
    }

    ret = PyTuple_New(indep->dim);
    for (i = 0; i < indep->dim; i++)
        PyTuple_SetItem(ret, i, Py_BuildValue("d", curve->dep->val[i]));

    phoebe_curve_free(curve);
    phoebe_vector_free(indep);

    return ret;
}

static PyObject *phoebeRV2(PyObject *self, PyObject *args)
{
    int index, i;
    PyObject *obj, *ret, *ts;
    char *rstr;

    PHOEBE_column_type itype;
    PHOEBE_vector *indep;
    PHOEBE_curve *curve;

    if (!PyArg_ParseTuple(args, "Oi", &obj, &index)) {
        printf("parsing failed: call with rv2(t_array, curve_index).\n");
        return NULL;
    }

    ts = PyArray_FromObject(obj, NPY_DOUBLE, 0, 0);
    indep = phoebe_vector_new_from_copied_data(PyArray_DATA(ts), PyArray_SIZE(ts));

    phoebe_parameter_get_value (phoebe_parameter_lookup ("phoebe_indep"), &rstr);
    phoebe_column_get_type (&itype, rstr);

    curve = phoebe_curve_new();
    phoebe_curve_compute(curve, indep, index, itype, PHOEBE_COLUMN_SECONDARY_RV, NULL, NULL, NULL);

    ret = PyTuple_New(indep->dim);
    for (i = 0; i < indep->dim; i++)
        PyTuple_SetItem(ret, i, Py_BuildValue("d", curve->dep->val[i]));

    phoebe_curve_free(curve);
    phoebe_vector_free(indep);

    return ret;
}

static PyObject *phoebeCritPot(PyObject *self, PyObject *args)
{
    /**
     * phoebeCritPot:
     *
     * Calculates critical surface potentials in L1 and L2 and returns
     * them in a 2-element tuple.
     */

    int status;
    double q, F, e, L1, L2;
    PyObject *retval;

    if (!PyArg_ParseTuple(args, "ddd", &q, &F, &e)) {
        printf("parsing failed.\n");
        return NULL;
    }

    status = phoebe_calculate_critical_potentials(q, F, e, &L1, &L2);
    if (status != SUCCESS)
        printf("%s", phoebe_error(status));

    retval = PyTuple_New(2);
    PyTuple_SetItem(retval, 0, Py_BuildValue("d", L1));
    PyTuple_SetItem(retval, 1, Py_BuildValue("d", L2));
    return retval;
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

struct ModuleState {
    PyObject *error;
};

#ifdef PY3K
#define GETSTATE(m) ((struct ModuleState *) PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct ModuleState _state;
#endif

static PyObject *phoebeError(PyObject *m) {
    struct ModuleState *st = GETSTATE(m);
    PyErr_SetString(st->error, "phoebeBackendPhoenix module failed to load.");
    return NULL;
}

static PyMethodDef PhoebeMethods[] = {
    {"error", (PyCFunction) phoebeError,       METH_NOARGS,  NULL},
    {"init",                phoebeInit,        METH_VARARGS, "Initialize PHOEBE backend"},
    {"configure",           phoebeConfigure,   METH_VARARGS, "Configure all internal PHOEBE structures"},
    {"quit",                phoebeQuit,        METH_VARARGS, "Quit PHOEBE"},
    {"open",                phoebeOpen,        METH_VARARGS, "Open PHOEBE parameter file"},
    {"save",                phoebeSave,        METH_VARARGS, "Save PHOEBE parameter file"},
    {"cfval",               phoebeCFVal,       METH_VARARGS, "Compute a cost function value of the passed curve"},
    {"pblum",               phoebePBLum,       METH_VARARGS, "Compute passband luminosity of the passed curve"},
    {"check",               phoebeCheck,       METH_VARARGS, "Check whether the parameter is within bounds"},
    {"setpar",              phoebeSetPar,      METH_VARARGS, "Set the value of the parameter"},
    {"getpar",              phoebeGetPar,      METH_VARARGS, "Get the value of the parameter"},
    {"setlim",              phoebeSetLim,      METH_VARARGS, "Set parameter limits"},
    {"getlim",              phoebeGetLim,      METH_VARARGS, "Get parameter limits"},
    {"updateLD",            phoebeUpdateLD,    METH_VARARGS, "Update limb darkening coefficients"},
    {"lc",                  phoebeLC,          METH_VARARGS, "Compute light curve"},
    {"dc",                  phoebeDC,          METH_VARARGS, "Run one iteration of the differential corrections minimizer"},
    {"rv1",                 phoebeRV1,         METH_VARARGS, "Compute primary radial velocity curve"},
    {"rv2",                 phoebeRV2,         METH_VARARGS, "Compute secondary radial velocity curve"},
    {"data",                phoebeData,        METH_VARARGS, "Return light or RV curve data"},
    {"parameter",           phoebeParameter,   METH_VARARGS, "Return a list of parameter properties"},
    {"role_reverse",        phoebeRoleReverse, METH_VARARGS, "Reverses the role of the primary and the secondary"},
    {"critpot",             phoebeCritPot,     METH_VARARGS, "Computes critical surface potentials in L1 and L2"},
    {NULL,                  NULL,              0,            NULL}
};

#ifdef PY3K

static int PhoebeTraverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int PhoebeClear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "phoebeBackendPhoenix",
    NULL,
    sizeof(struct ModuleState),
    PhoebeMethods,
    NULL,
    PhoebeTraverse,
    PhoebeClear,
    NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC PyInit_phoebeBackendPhoenix(void)
#else

#define INITERROR return

void initphoebeBackendPhoenix(void)
#endif
{
    import_array();
    struct ModuleState *st;
#ifdef PY3K
    PyObject *backend = PyModule_Create(&moduledef);
#else
    PyObject *backend = Py_InitModule("phoebeBackendPhoenix", PhoebeMethods);
#endif

    if (!backend)
        INITERROR;
    
    st = GETSTATE(backend);

    st->error = PyErr_NewException("phoebeBackendPhoenix.Error", NULL, NULL);
    if (!st->error) {
        Py_DECREF(backend);
        INITERROR;
    }

#ifdef PY3K
    return backend;
#endif
}
