#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "phoebe_global.h"
#include "phoebe_phsv_pcsv.h"

int compare_doubles (const void *a, const void *b)
	{
	const double *da = (const double *) a;
	const double *db = (const double *) b;

	return (*da > *db) - (*da < *db);
	}

double calculate_median (PHOEBE_data data)
	{
	qsort (data.dep, data.ptsno, sizeof (double), compare_doubles);

	if (data.ptsno % 2 == 0) return data.dep[data.ptsno/2];
	else return 0.5*(data.dep[data.ptsno/2]+data.dep[data.ptsno/2+1]);
	}

double calculate_sum (PHOEBE_data data)
	{
	int i;
	double sum = 0.0;
	
	for (i = 0; i < data.ptsno; i++)
		sum += data.dep[i];
	
	return sum;
	}

int calculate_critical_potentials (double q, double F, double e, double *L1crit, double *L2crit)
	{
	/* This function calculates the value of the gravitational potential \Omega */
	/* (PHSV) in Lagrange points L1 and L2.                                     */
	/*                                                                          */
	/* Input parameters:                                                        */
	/*                                                                          */
	/*   q .. mass ratio                                                        */
	/*   F .. synchronicity parameter                                           */
	/*   e .. eccentricity                                                      */
	/*                                                                          */
	/* Output parameters:                                                       */
	/*                                                                          */
	/*   L1crit .. L1 potential value                                           */
	/*   L2crit .. L2 potential value                                           */

	double D = 1.0 - e;
	double  xL = 0.5;                             /* Initial x coordinate value */
	double dxL = 1.1e-6;                          /* Initial x coordinate step  */
	double Force;                                 /* Gravitational force        */
	double dxLdF;                                 /* Spatial derivative         */

	double xL1;                                   /* L1 x coordinate            */
	double xL2;                                   /* L2 x coordinate            */

	double q2;
	double factor;

	/* First L1: we iterate to the point of accuracy better than 1e-6:          */

	while (fabs(dxL) > 1e-6)
		{
		xL = xL + dxL;
		Force = F*F*(q+1)*xL - 1.0/xL/xL - q*(xL-D)/fabs(pow(D-xL,3)) - q/D/D;
		dxLdF  = 1.0/(F*F*(q+1) + 2.0/xL/xL/xL + 2*q/fabs(pow(D-xL,3)));
		dxL = -Force * dxLdF;
		}
	xL1 = xL;
	*L1crit = calculate_phsv_value (1, D, q, xL1, F, 1.0, 0.0);

	/* Next, L2: we have to make sure that L2 is properly defined, i.e. behind  */
	/* the lower mass star, and that it makes sense to calculate it only in     */
	/* synchronous rotation and circular orbit case:                            */

	if (q > 1.0) q2 = 1.0/q; else q2 = q;
	D = 1.0; F = 1.0; dxL = 1.1e-6;

	factor = pow (q2/3/(q2+1), 1./3.);
	xL = 1 + factor + 1./3. * factor*factor + 1./9. * factor*factor*factor;
	while (fabs(dxL) > 1e-6)
		{
		xL = xL + dxL;
		Force = F*F*(q2+1)*xL - 1.0/xL/xL - q2*(xL-D)/fabs(pow(D-xL,3)) - q2/D/D;
		dxLdF  = 1.0/(F*F*(q2+1) + 2.0/xL/xL/xL + 2*q2/fabs(pow(D-xL,3)));
		dxL = -Force * dxLdF;
		}
	if (q > 1.0) xL = D - xL;
	xL2 = xL;
	*L2crit = 1.0/fabs(xL2) + q*(1.0/fabs(xL2-1)-xL2) + 1./2.*(q+1)*xL2*xL2;
	}

/* Functions for computing critical phases: */

double calculate_eccentric_anomaly_from_true_anomaly (double upsilon, double e)
{
	double E = 2*atan(sqrt((1-e)/(1+e)) * tan(upsilon/2));
	E += M_PI * (int) ((upsilon+M_PI/2)/M_PI);
	return E;
}

double calculate_mean_anomaly_from_eccentric_anomaly (double E, double e)
{
	return E - e*sin(E);
}

int calculate_critical_phases (double omega, double e, double pshift, double *phiper, double *phiconj)
{
	double upsilon = M_PI/2 - omega;
	double E = calculate_eccentric_anomaly_from_true_anomaly (upsilon, e);
	double M = calculate_mean_anomaly_from_eccentric_anomaly (E, e);
/*
	double per  = 1-M/2.0/M_PI;
	printf ("# Tper = %lf\n", upsilon*180.0/M_PI);
	printf ("# Eper = %lf\n", E*180.0/M_PI);
	printf ("# Mper = %lf\n", M*180.0/M_PI);
	printf ("# Pper = %lf\n", per);
*/
	*phiconj = (M+omega-M_PI/2.0)/(2.0*M_PI) + pshift;
	if (*phiconj >= 1.0) *phiconj -= 1.0;
	if (*phiconj < -1.0) *phiconj += 1.0;
	*phiper  = omega/(2.0*M_PI) + 0.75 + pshift;

	return 0;
}
