#include <stdlib.h>
#include <stdio.h>

#include "phoebe_allocations.h"
#include "phoebe_global.h"

void bin_data (PHOEBE_data *data, int bin_no)
	{
	int i, j;

	double bin_step;
	int bin, empty_count;

	PHOEBE_data src;

	/* First, let's copy the contents of data to the newly allocated src:       */
	src.ptsno = data->ptsno; src.indep = NULL; src.dep = NULL; src.weight = NULL;
	allocate_memory_for_data (&src);
	for (i = 0; i < data->ptsno; i++)
		{
		src.indep[i]  = data->indep[i];
		src.dep[i]    = data->dep[i];
		src.weight[i] = data->weight[i];
		}

	/* That's it. Now reallocate memory to data so it contains only binned va-  */
	/* lues:                                                                    */
	free (data->indep); free (data->dep); free (data->weight);
	data->indep = NULL; data->dep = NULL; data->weight = NULL;
	data->ptsno = bin_no;
	allocate_memory_for_data (data);

	/* We take such a step that the binned range is from phase -0.5 + step/2    */
	/* to 0.5 - step/2, so it is not merely an OB1 error:                       */
	bin_step = ( 0.5 - (-0.5) ) / bin_no;
	for (i = 0; i < bin_no; i++)
		{
		data->indep[i] = -0.5 + (1./2. + i) * bin_step;
		data->dep[i]   = data->weight[i] = 0.0;
		}

	/* Binning of points: */
	for (i = 0; i < src.ptsno; i++)
		{
		if (src.indep[i] < -0.5 || src.indep[i] > 0.5)
			{
			phoebe_warning ("phase %lf out of range [-0.5, 0.5], discarding.\n", src.indep[i]);
			continue;
			}
		bin = (int) ((src.indep[i] - (-0.5)) * bin_no / (0.5 - (-0.5)));
		if ( bin == bin_no ) bin = bin_no - 1; /* This takes care of 0.50000 phase. */
		data->dep[bin] += src.dep[i];
		data->weight[bin] += 1.0;           /* We are using .weight for counting. */
		}

	/* Let's get a bin average over all binned values. If there are no points   */
	/* in a particular bin, we set it to zero and discard it later:             */
	for (i = 0; i < bin_no; i++)
		{
		if (data->weight[i] != 0) data->dep[i] /= data->weight[i];
	                       else data->dep[i] = 0.0;
		}

	/* The idea now is to discard all empty bins, since they serve no purpose:  */
	empty_count = 0;
	for (i = 0; i < bin_no - empty_count; i++)
		{
		if (data->weight[i] < 0.1)      /* Actually, == 0, but just to be safe... */
			{
			for (j = i; j < bin_no - empty_count; j++)
				{
				data->indep[j]  = data->indep[j+1];
				data->dep[j]    = data->dep[j+1];
				data->weight[j] = data->weight[j+1];
				}
			empty_count++;
			/* If there are two consecutive empty bins, this takes care of it:      */
			i--;
			}
		}
	data->ptsno = bin_no - empty_count;

	/* Finally, free the copy of original data:                                 */
	free (src.indep); free (src.dep); free (src.weight);
	}
