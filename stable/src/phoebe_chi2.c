#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "phoebe_global.h"

double calculate_chi2 (PHOEBE_data synthetic_data, PHOEBE_data experimental_data, double sigma, int type)
	{
	/* This function interpolates synthetic curve and experimental data points  */
	/* and calculates standard deviation depending on the type integer:         */
  /*                                                                          */
	/*   type = 0   ...   standard deviation with no weighting applied          */
	/*   type = 1   ...   standard deviation with weighting applied             */
	/*   type = 2   ...   chi2 with no weighting applied                        */
	/*   type = 3   ...   chi2 with weighting applied                           */
  /*                                                                          */
	/* If the function returns a negative value, it means something went wrong. */

	int i, j;
	int breaked;
	double interpolated_y;

	double chi2 = 0.0;
	double weight_sum = 0.0;

	/* First let's do some error checking:                                      */
	if ( (synthetic_data.ptsno <= 1) || (experimental_data.ptsno <= 1) )
		{
		phoebe_warning ("calculate_chi2 routine called with vectors that have dimension <= 1.");
		return -1.0;
		}

	for (i = 0; i < experimental_data.ptsno; i++)
		{
		breaked = 0;
		for (j = 1; j < synthetic_data.ptsno; j++)
			if (synthetic_data.indep[j] > experimental_data.indep[i])
				{
				breaked = 1;
				break;
				}
		if (breaked == 1)
			{
			interpolated_y = synthetic_data.dep[j-1] + (experimental_data.indep[i] - 
			                 synthetic_data.indep[j-1]) / (synthetic_data.indep[j] - 
			                 synthetic_data.indep[j-1]) * (synthetic_data.dep[j] -
			                 synthetic_data.dep[j-1]);

			if ( (type == 0) || (type == 2) ) chi2 += pow (interpolated_y - experimental_data.dep[i], 2);
			if ( (type == 1) || (type == 3) ) chi2 += experimental_data.weight[i] * pow (interpolated_y - experimental_data.dep[i], 2);
			}
		}

	if (type == 0)
		return sqrt (chi2 / (experimental_data.ptsno - 1));
	if (type == 1)
		{
		for (i = 0; i < experimental_data.ptsno; i++)
			weight_sum += experimental_data.weight[i];
		return sqrt (chi2 / (weight_sum - weight_sum / experimental_data.ptsno));
		}
	if (type == 2)
		return chi2 / 2.0 / sigma / sigma;
	if (type == 3)
		{
		for (i = 0; i < experimental_data.ptsno; i++)
			weight_sum += experimental_data.weight[i];
		return chi2 / 2.0 / sigma / sigma / weight_sum;
		}

	return -1.0;
	}
