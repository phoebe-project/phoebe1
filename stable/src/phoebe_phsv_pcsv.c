#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <math.h>

#include "phoebe_gui.h"
#include "phoebe_gui_callbacks.h"
#include "phoebe_gui_support.h"
#include "phoebe_phsv_pcsv.h"

double calculate_phsv_value (int ELLIPTIC, double D, double q, double r, double F, double lambda, double nu)
	{
	if (ELLIPTIC == 0)
		return 1./r + q*pow(D*D+r*r,-0.5) + 0.5*(1.+q)*r*r;
	else
		return 1./r + q*(pow(D*D+r*r-2*r*lambda*D,-0.5)-r*lambda/D/D) + 0.5*F*F*(1.+q)*r*r*(1-nu*nu);
	}
	
double calculate_pcsv_value (int ELLIPTIC, double D, double q, double r, double F, double lambda, double nu)
	{
	double phsv;

	/* We changed the coordinate system, thus q -> 1/q:                         */
	q = 1./q;

	if (ELLIPTIC == 0)
		phsv = calculate_phsv_value (0, D, q, r, 0, 0, 0);
	else
		phsv = calculate_phsv_value (1, D, q, r, F, lambda, nu);

	return phsv/q + 0.5 * (q-1)/q;
	}
