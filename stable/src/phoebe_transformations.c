#include <stdlib.h>

#include <gtk/gtk.h>
#include <math.h>

#include "phoebe_error_handling.h"
#include "phoebe_global.h"
#include "phoebe_gui_support.h"

void transform_phase_to_hjd (PHOEBE_data *data, double hjd0, double period)
	{
	int i;
	
	for (i = 0; i < data->ptsno; i++)
		data->indep[i] = hjd0 + data->indep[i] * period;
	}

void transform_hjd_to_phase (PHOEBE_data *data, double hjd0, double period, double dpdt)
	{
	/* This function transforms heliocentric julian date (HJD) with given ori-  */
	/* gin HJD0 and period P to phase on interval [-0.5,0.5].                   */

	int i;

	for (i = 0; i < data->ptsno; i++)
		{
		if (fabs(dpdt) < 1E-15) data->indep[i] = fmod ((data->indep[i]-hjd0)/period, 1.0);
		else              data->indep[i] = fmod (log(1.0+dpdt*((data->indep[i]-hjd0)/period))/dpdt, 1.0);
		/* If HJD0 is larger than HJD, then the difference is negative and we     */
		/* must fix that:                                                         */
		if (data->indep[i] < 0.0) data->indep[i] += 1.0;

		/* Now we have the phase interval [0,1], but we want [-0.5, 0.5]:         */
		if (data->indep[i] > 0.5) data->indep[i] -= 1.0;
		}
	}

void transform_absolute_error_to_weight (PHOEBE_data *data)
	{
	/* This function transforms absolute errors in experimental data files to   */
	/* real-type weights following that an absolute error is inversely propor-  */
	/* tional to weight. The mapped weight interval is [0.1,9.9].               */

	int i;

	double minweight = 1.0/pow(data->weight[0],2);
	double maxweight = 1.0/pow(data->weight[0],2);

	if (maxweight - minweight < 1e-5)
		{
		/* This means that all individual weights are exactly the same.           */
		for (i = 0; i < data->ptsno; i++) data->weight[i] = 1.0;
		return;
		}

	for (i = 0; i < data->ptsno; i++)
		{
		data->weight[i] = 1.0/data->weight[i]/data->weight[i];
		if (data->weight[i] < minweight) minweight = data->weight[i];
		if (data->weight[i] > maxweight) maxweight = data->weight[i];
		}

	for (i = 0; i < data->ptsno; i++)
		data->weight[i] = 0.1 + (9.9-0.1)/(maxweight-minweight)*(data->weight[i]-minweight);
	}

void shift_interval (PHOEBE_data *data, double phmin, double phmax)
{
	/* This function shifts the contents of data phases so that they are cen- */
	/* tered on the [phmin, phmax] interval. We need this for better results  */
	/* if aliasing is not turned on.                                          */

	int i;
	double center = (phmin+phmax)/2.0;
	int factor = center / 1;
	double cphase;

	if (factor == 0)
		cphase = center;
	else
		cphase = fmod (center, (double) factor);

	for (i = 0; i < data->ptsno; i++) {
		if (data->indep[i] >= -0.5000000001 && data->indep[i] < cphase-0.5000000001)
			data->indep[i] += factor+1;
		else
			data->indep[i] += factor;
	}

	return;
}

void alias_phase_to_interval (PHOEBE_data *data, double phmin, double phmax)
	{
	/* This function redimensiones the array of data phases by aliasing points  */
	/* to outside the [-0.5, 0.5] range. If the new interval is narrower, the   */
	/* points are omitted, otherwise they are aliased.                          */

	int i, j;
	PHOEBE_data new_data;
	
	/* Make a new array record to keep the original array, since it will be mo- */
	/* dified at the end:                                                       */
	new_data.ptsno  = data->ptsno;
	new_data.indep  = phoebe_malloc (new_data.ptsno * sizeof (*new_data.indep));
	new_data.dep    = phoebe_malloc (new_data.ptsno * sizeof (*new_data.dep));
	new_data.weight = phoebe_malloc (new_data.ptsno * sizeof (*new_data.weight));

	/* Do the actual copying:                                                   */
	for (i = 0; i < new_data.ptsno; i++)
		{
		new_data.indep[i]  = data->indep[i];
		new_data.dep[i]    = data->dep[i];
		new_data.weight[i] = data->weight[i];
		}

	/* Release the input array record:                                          */
	data->indep = NULL; data->dep = NULL; data->weight = NULL; data->ptsno = 0;

	/* Now make a loop that does the actual aliasing:                           */
	for (i = 0; i < new_data.ptsno; i++)
		{
		for (j = (int) (phmin - 1); j <= (int) (phmax + 1); j++)
			{
			if ( (new_data.indep[i] + j > phmin) && (new_data.indep[i] + j < phmax) )
				{
				data->ptsno++;
				data->indep  = phoebe_realloc (data->indep,  data->ptsno * sizeof (*data->indep));
				data->dep    = phoebe_realloc (data->dep,    data->ptsno * sizeof (*data->dep));
				data->weight = phoebe_realloc (data->weight, data->ptsno * sizeof (*data->weight));
				data->indep[data->ptsno-1]  = new_data.indep[i] + j;
				data->dep[data->ptsno-1]    = new_data.dep[i];
				data->weight[data->ptsno-1] = new_data.weight[i];
				}
			}
		}

	/* Free the temporary array record:                                         */
	free (new_data.indep);
	free (new_data.dep);
	free (new_data.weight);
	new_data.ptsno = 0;
	}

void transform_magnitude_to_flux (PHOEBE_data *data, double mnorm)
	{
	int i;

	for (i = 0; i < data->ptsno; i++)
		data->dep[i] = pow (10, -2./5. * (data->dep[i] - mnorm));
	}

void transform_flux_to_magnitude (PHOEBE_data *data, double mnorm)
	{
	int i;

	for (i = 0; i < data->ptsno; i++)
		data->dep[i] = mnorm - 5./2. * log10 (data->dep[i]);
	}

void transform_100kms_to_kms (PHOEBE_data *data)
	{
	int i;
	
	for (i = 0; i < data->ptsno; i++)
		data->dep[i] *= 100.0;
	}

void transform_kms_to_100kms (PHOEBE_data *data)
	{
	int i;
	
	for (i = 0; i < data->ptsno; i++)
		data->dep[i] /= 100.0;
	}

void remove_reddening_from_data (PHOEBE_data *data, double lambda, double R, double EBV)
	{
	/* This function calculates the reddening coefficient A_\lambda following   */
	/* the Allen's Astrophysical Quantities 3rd Ed., pg. 264:                   */

	double extinction = R * EBV * 0.68 * (1000./lambda - 0.35);
	int i;

	for (i = 0; i < data->ptsno; i++)
		data->dep[i] = data->dep[i] - extinction;
	}

void remove_reddening_from_fluxes (PHOEBE_data *data, double lambda, double R, double EBV)
	{
	double extinction = R * EBV * 0.68 * (1000./lambda - 0.35);
	int i;

	for (i = 0; i < data->ptsno; i++)
		data->dep[i] = data->dep[i] * pow (10.0, 2./5. * extinction);
	}

void normalize_rv_to_orbit (PHOEBE_data *data, double sma, double period)
	{
	int i;

	const double R_SUN = 696000.0;
	const double SEC_IN_DAY = 24.0 * 3600.0;
	
	for (i = 0; i < data->ptsno; i++)
		data->dep[i] = data->dep[i] * period * SEC_IN_DAY / 2.0 / M_PI / R_SUN / sma;
	}

void transform_flux_sigma_to_magnitude_sigma (double flux_sigma, double mag_sigma)
	{
	mag_sigma = -5./2. * log10 (flux_sigma);
	}

void transform_magnitude_sigma_to_flux_sigma (double mag_sigma, double flux_sigma)
	{
	flux_sigma = pow (10, -2./5. * mag_sigma);
	}

void get_plot_limits_of_data (PHOEBE_data data, double *xmin, double *ymin, double *xmax, double *ymax)
{
	/*
	 * This function scans data and finds (x_min, y_min), (x_max, y_max) values.
	 */

	int i;

	*xmin = 0; *xmax = 0;
	*ymin = 0; *ymax = 0;

	if (data.ptsno == 0) return;

	*xmin = data.indep[0]; *xmax = data.indep[0];
	*ymin = data.dep[0];   *ymax = data.dep[0];
	
	for (i = 1; i < data.ptsno; i++) {
		if (*xmin > data.indep[i]) *xmin = data.indep[i];
		if (*xmax < data.indep[i]) *xmax = data.indep[i];
		if (*ymin > data.dep[i]  ) *ymin = data.dep[i];
		if (*ymax < data.dep[i]  ) *ymax = data.dep[i];
	}

	return;
}

void calculate_residuals (PHOEBE_data *set1, PHOEBE_data *set2)
	{
	/* This function calculates residuals between synthetic (set1) and experi-  */
	/* mental (set2) data and outputs them to set2. At the time it uses linear  */
	/* interpolation, which isn't good; it will be changed when BBL routine     */
	/* from WD will be called directly.                                         */

	int i, j;
	int breaked;

	double synthetic_value;
	
	for (i = 0; i < set2->ptsno; i++)
		{
		breaked = 0;
		for (j = 1; j < set1->ptsno; j++)
			{
			if (set1->indep[j] > set2->indep[i])
				{
				breaked = 1;
				break;
				}
			}
		if (breaked == 1)
			{
			synthetic_value = set1->dep[j-1] + (set2->indep[i] - 
			                  set1->indep[j-1]) / (set1->indep[j] - 
			                  set1->indep[j-1]) * (set1->dep[j] -
			                  set1->dep[j-1]);
			set2->dep[i] = set2->dep[i] - synthetic_value;
			}
		}

	/* Finally, let's set all synthetic data points to 0 for residual reference */
	for (i = 0; i < set1->ptsno; i++)
		set1->dep[i] = 0.0;

	return;
	}
