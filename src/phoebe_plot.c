#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>

#include "phoebe_allocations.h"
#include "phoebe_chi2.h"
#include "phoebe_error_handling.h"
#include "phoebe_fortran_implementations.h"
#include "phoebe_global.h"
#include "phoebe_gui_accessories.h"
#include "phoebe_gui_support.h"
#include "phoebe_transformations.h"

#include "config.h"

/* SuperMongo support:                                                        */
#ifdef PHOEBE_SM_SUPPORT
	#include <sm_declare.h>
#endif

int scan_temporary_directory_for_lci_file_index (char *prefix)
	{
	/* This function accesses the temporary PHOEBE directory and checks all     */
	/* present filenames to extract the latest filename number. We want this to */
	/* avoid overwriting a particular older configuration file with the newer   */
	/* one, because the user might want to keep it.                             */

	char working_string[255];
	char *working_str = working_string;
	int i = 0;

	sprintf (working_str, "%s/%s_%03d.lci", PHOEBE_TEMP_DIR, prefix, i);
	while (file_exists (working_str))
		{
		/* The file for given i exists; therefore we increase the counter to find */
		/* the first i for which there is no file:                                */
		i++;
		sprintf (working_str, "%s/%s_%03d.lci", PHOEBE_TEMP_DIR, prefix, i);
		}
	/* Here we have the first i for which there is no filename.                 */

	return i - 1;
	}

int scan_temporary_directory_for_dci_file_index (char *prefix)
	{
	/* This function accesses the temporary PHOEBE directory and checks all     */
	/* present filenames to extract the latest filename number. We want this to */
	/* avoid overwriting a particular older configuration file with the newer   */
	/* one, because the user might want to keep it.                             */

	char working_string[255];
	char *working_str = working_string;
	int i = 0;

	sprintf (working_str, "%s/%s_%03d.dci", PHOEBE_TEMP_DIR, prefix, i);
	while (file_exists (working_str))
		{
		/* The file for given i exists; therefore we increase the counter to find */
		/* the first i for which there is no file:                                */
		i++;
		sprintf (working_str, "%s/%s_%03d.dci", PHOEBE_TEMP_DIR, prefix, i);
		}
	/* Here we have the first i for which there is no filename.                 */

	return i - 1;
	}

void create_lci_input_file (char *prefix,
                            PHOEBE_main_parameters main,
                            PHOEBE_switches switches,
                            PHOEBE_limb_darkening ld,
														PHOEBE_spots spots,
														PHOEBE_curve_parameters curve,
                            PHOEBE_wl_dependent_parameters mono)
	{
	/* This function creates an LCI file, where we want to be careful not to    */
	/* overwrite already existing LCI files, which the user may want to keep:   */

	char working_string[255];
	char *working_str = working_string;

	int i;

	phoebe_debug ("entering 'create_lci_input_file ()' function.\n");

	i = scan_temporary_directory_for_lci_file_index (prefix);

	sprintf (working_str, "%s/%s_%03d.lci", PHOEBE_TEMP_DIR, prefix, i+1);
	create_lci_file (working_str, main, switches, ld, spots, curve, mono);

	phoebe_debug ("leaving 'create_lci_input_file ()' function.\n");
	}

void create_dci_input_file (double DEL[35], int KEP[35], PHOEBE_main_parameters main, PHOEBE_limb_darkening ld, PHOEBE_spots spots, PHOEBE_switches switches, PHOEBE_mms mms)
	{
	char working_string[255];
	char *working_str = working_string;

	int i;

	i = scan_temporary_directory_for_dci_file_index ("phoebe_dc");

	sprintf (working_str, "%s/%s_%03d.dci", PHOEBE_TEMP_DIR, "phoebe_dc", i+1);
	create_dci_file (working_str, DEL, KEP, main, ld, spots, switches, mms);
	}

void calculate_plot_limits (PHOEBE_data synthetic_data, PHOEBE_data experimental_data, double *xmin, double *ymin, double *xmax, double *ymax, int plot_synthetic, int plot_experimental, double x_offset, double y_offset, double zoom)
	{
	double xmin1, xmax1, ymin1, ymax1;              /* Synthetic data limits    */
	double xmin2, xmax2, ymin2, ymax2;              /* Experimental data limits */

	if (plot_synthetic == 1)    get_plot_limits_of_data (synthetic_data,    &xmin1, &ymin1, &xmax1, &ymax1);
	if (plot_experimental == 1) get_plot_limits_of_data (experimental_data, &xmin2, &ymin2, &xmax2, &ymax2);

	if (plot_synthetic == 1)
		{
		*xmin = xmin1 + x_offset * (xmax1 - xmin1) - (0.1 + zoom) * (xmax1 - xmin1);
		*xmax = xmax1 + x_offset * (xmax1 - xmin1) + (0.1 + zoom) * (xmax1 - xmin1);
		*ymin = ymin1 + y_offset * (ymax1 - ymin1) - (0.1 + zoom) * (ymax1 - ymin1);
		*ymax = ymax1 + y_offset * (ymax1 - ymin1) + (0.1 + zoom) * (ymax1 - ymin1);
		xmin1 = *xmin; xmax1 = *xmax; ymin1 = *ymin; ymax1 = *ymax;
		}

	if (plot_experimental == 1)
		{
		*xmin = xmin2 + x_offset * (xmax2 - xmin2) - (0.1 + zoom) * (xmax2 - xmin2);
		*xmax = xmax2 + x_offset * (xmax2 - xmin2) + (0.1 + zoom) * (xmax2 - xmin2);
		*ymin = ymin2 + y_offset * (ymax2 - ymin2) - (0.1 + zoom) * (ymax2 - ymin2);
		*ymax = ymax2 + y_offset * (ymax2 - ymin2) + (0.1 + zoom) * (ymax2 - ymin2);
		xmin2 = *xmin; xmax2 = *xmax; ymin2 = *ymin; ymax2 = *ymax;
		}

	if ( (plot_synthetic == 1) && (plot_experimental == 1) )
		{
		if (xmin1 < xmin2) *xmin = xmin1; else *xmin = xmin2;
		if (xmax1 > xmax2) *xmax = xmax1; else *xmax = xmax2;
		if (ymin1 < ymin2) *ymin = ymin1; else *ymin = ymin2;
		if (ymax1 > ymax2) *ymax = ymax1; else *ymax = ymax2;
		}
	}

void create_lc_plot_using_sm (PHOEBE_plot_device device, char *filename, PHOEBE_data synthetic_data, PHOEBE_data experimental_data, int indep, int dep, int grid, int box, double x_offset, double y_offset, double zoom, int plot_synthetic, int plot_experimental)
	{
	#ifdef PHOEBE_SM_SUPPORT
	char working_string[255];
	char *working_str = working_string;

	int i;

	/* Plot limits; values are assigned in case this function would ever be     */
	/* called with both plot_synthetic and plot_experimental switches off.      */
	double xmin = 0.0, xmax = 0.0, ymin = 0.0, ymax = 0.0;

	/* Point type is assigned to each point individually, thus an array:        */
	double *ptype = NULL;

	FILE *plot_file;

	if (plot_synthetic == 1)
		{
		printf ("points: %d\n", synthetic_data.ptsno);
		for (i = 0; i < synthetic_data.ptsno; i++)
			printf ("%3d:   indep: %10lf dep: %10lf weight: %10lf\n", i, synthetic_data.indep[i], synthetic_data.dep[i], synthetic_data.weight[i]);
		}

	/* If the output is ascii table, write it out now and exit:                 */
	if (device == ascii)
		{
		plot_file = fopen (filename, "w");
		if (plot_synthetic == 1)
			{
			fprintf (plot_file, "# indep\t# dep\t# weight\n");
			for (i = 0; i < synthetic_data.ptsno; i++)
				fprintf (plot_file, "%lf\t%lf\t%lf\n", synthetic_data.indep[i], synthetic_data.dep[i], synthetic_data.weight[i]);
			}
		if (plot_experimental == 1)
			{
			fprintf (plot_file, "# indep\t\t# dep\t\t# weight\n");
			for (i = 0; i < experimental_data.ptsno; i++)
				fprintf (plot_file, "%lf\t%lf\t%lf\n", experimental_data.indep[i], experimental_data.dep[i], experimental_data.weight[i]);
			}
		fclose (plot_file);
		return;
		}

	/* Set point type for all points to be medium sized filled circles:         */
	if (plot_experimental == 1)
		{
		ptype = phoebe_malloc (experimental_data.ptsno * sizeof (*ptype));
		for (i = 0; i < experimental_data.ptsno; i++) ptype[i] = 103;
		}

	/* Set the terminal to graphical state:                                     */
	sm_graphics ();

	/* Initialize the file into which we are plotting to:                       */
	if (device == x11)
		sprintf (working_str, "aspectxpm %s/phoebe_lc_%03d.xpm", PHOEBE_TEMP_DIR, scan_temporary_directory_for_lci_file_index ("phoebe_lc"));
	if (device == eps)
		sprintf (working_str, "postfile %s", filename);
	if (device == xpm)
		sprintf (working_str, "aspectxpm %s", filename);
	if (device == gif)
		sprintf (working_str, "aspectgif %s", filename);
	if (device == ppm)
		sprintf (working_str, "ppm %s", filename);
	if (device == tinygif)
		sprintf (working_str, "tinygif %s", filename);

	sm_device (working_str);

	/* Set the main plot characteristics:                                       */
	sm_expand (1.0001);
	sm_ptype (ptype, 3);
	sm_defvar("TeX_strings", "1");

	/* Calculate and set plotting limits:                                       */
	calculate_plot_limits (synthetic_data, experimental_data, &xmin, &ymin, &xmax, &ymax, plot_synthetic, plot_experimental, x_offset, y_offset, zoom);
	if (dep == 8) sm_limits (xmin, xmax, ymax, ymin);             /* Magnitudes */
	else          sm_limits (xmin, xmax, ymin, ymax);             /* Fluxes     */

	if (box  == 1) sm_box (1, 2, 4, 4);
	if (box  == 0) sm_box (1, 2, 0, 0);
	if (grid == 1) { sm_ltype (1); sm_grid (0, 0); sm_ltype (0); }
	if (grid == 2) { sm_ltype (1); sm_grid (1, 0); sm_ltype (0); }

	if (plot_experimental == 1)
		{
		sm_ctype ("blue");
		sm_points  (experimental_data.indep, experimental_data.dep, experimental_data.ptsno);
		}

	if (plot_synthetic == 1)
		{
		sm_ctype ("red");
		sm_connect (synthetic_data.indep, synthetic_data.dep, synthetic_data.ptsno);
		}

	sm_ctype ("black");
	if (indep == 1) sm_xlabel ("HJD");
	if (indep == 2) sm_xlabel ("Phase");
	if (  dep == 3) sm_ylabel ("Primary Star Flux");
	if (  dep == 4) sm_ylabel ("Secondary Star Flux");
	if (  dep == 5) sm_ylabel ("Total Flux");
	if (  dep == 6) sm_ylabel ("Normalized Flux");
	if (  dep == 8) sm_ylabel ("Magnitude");

	/* Flush graphics output to screen:                                         */
	sm_gflush ();

	/* Set the terminal back to normal state:                                   */
	sm_hardcopy ();
	sm_alpha ();

	free (ptype);
	#endif
	}

void create_rv_plot_using_sm (PHOEBE_plot_device device, char *filename, PHOEBE_data synthetic_data, PHOEBE_data experimental_data, int indep, int dep, int grid, int box, double x_offset, double y_offset, double zoom, int plot_synthetic, int plot_experimental)
	{
	#ifdef PHOEBE_SM_SUPPORT
	char working_string[255];
	char *working_str = working_string;

	int i;

	/* Plot limits; values are assigned in case this function would ever be     */
	/* called with both plot_synthetic and plot_experimental switches off.      */
	double xmin = 0.0, xmax = 0.0, ymin = 0.0, ymax = 0.0;

	/* Point type is assigned to each point individually, thus an array:        */
	double *ptype = NULL;

	FILE *plot_file;

	/* If the output is ascii table, write it out now and exit:                 */
	if (device == ascii)
		{
		plot_file = fopen (filename, "w");
		if (plot_synthetic == 1)
			{
			fprintf (plot_file, "# indep\t\t# dep\t\t# weight\n");
			for (i = 0; i < synthetic_data.ptsno; i++)
				fprintf (plot_file, "%lf\t%lf\t%lf\n", synthetic_data.indep[i], synthetic_data.dep[i], synthetic_data.weight[i]);
			}
		if (plot_experimental == 1)
			{
			fprintf (plot_file, "# indep\t# dep\t# weight\n");
			for (i = 0; i < experimental_data.ptsno; i++)
				fprintf (plot_file, "%lf\t%lf\t%lf\n", experimental_data.indep[i], experimental_data.dep[i], experimental_data.weight[i]);
			}
		fclose (plot_file);
		return;
		}

	/* Set point type for all points to be medium sized filled circles:         */
	if (plot_experimental == 1)
		{
		ptype = phoebe_malloc (experimental_data.ptsno * sizeof (*ptype));
		for (i = 0; i < experimental_data.ptsno; i++) ptype[i] = 103;
		}

	/* Set the terminal to graphical state:                                     */
	sm_graphics ();

	/* Initialize the file into which we are plotting to:                       */
	if (device == x11)
		sprintf (working_str, "aspectxpm %s/phoebe_rv_%03d.xpm", PHOEBE_TEMP_DIR, scan_temporary_directory_for_lci_file_index ("phoebe_rv"));
	if (device == eps)
		sprintf (working_str, "postfile %s", filename);
	if (device == xpm)
		sprintf (working_str, "aspectxpm %s", filename);
	if (device == gif)
		sprintf (working_str, "aspectgif %s", filename);
	if (device == ppm)
		sprintf (working_str, "ppm %s", filename);
	if (device == tinygif)
		sprintf (working_str, "tinygif %s", filename);

	sm_device (working_str);

	/* Set the main plot characteristics:                                       */
	sm_expand (1.0001);
	sm_ptype (ptype, 3);
	sm_defvar("TeX_strings", "1");

	/* Calculate and set plotting limits:                                       */
	calculate_plot_limits (synthetic_data, experimental_data, &xmin, &ymin, &xmax, &ymax, plot_synthetic, plot_experimental, x_offset, y_offset, zoom);
	sm_limits (xmin, xmax, ymin, ymax);

	if (box  == 1) sm_box (1, 2, 4, 4);
	if (box  == 0) sm_box (1, 2, 0, 0);
	if (grid == 1) { sm_ltype (1); sm_grid (0, 0); sm_ltype (0); }
	if (grid == 2) { sm_ltype (1); sm_grid (1, 0); sm_ltype (0); }

	if (plot_experimental == 1)
		{
		sm_ctype ("blue");
		sm_points  (experimental_data.indep, experimental_data.dep, experimental_data.ptsno);
		}

	if (plot_synthetic == 1)
		{
		sm_ctype ("red");
		if (dep != 9) sm_connect (synthetic_data.indep, synthetic_data.dep, synthetic_data.ptsno);
		else
			{
			/* If we want both RV curves, we have to play some tricks with SM:      */

			sm_connect (synthetic_data.indep, synthetic_data.dep, synthetic_data.ptsno / 2);
			for (i = 0; i < synthetic_data.ptsno / 2; i++)
				{
				synthetic_data.indep[i]  = synthetic_data.indep[synthetic_data.ptsno/2+i];
				synthetic_data.dep[i]    = synthetic_data.dep[synthetic_data.ptsno/2+i];
				synthetic_data.weight[i] = synthetic_data.weight[synthetic_data.ptsno/2+i];
				}
			sm_connect (synthetic_data.indep, synthetic_data.dep, synthetic_data.ptsno / 2);
			}
		}

	sm_ctype ("black");
	if (indep == 1) sm_xlabel ("HJD");
	if (indep == 2) sm_xlabel ("Phase");
	if (  dep == 3) sm_ylabel ("Normalized Primary Star RV");
	if (  dep == 4) sm_ylabel ("Normalized Secondary Star RV");
	if (  dep == 5) sm_ylabel ("Primary Star Eclipse Corrections");
	if (  dep == 6) sm_ylabel ("Secondary Star Eclipse Corrections");
	if (  dep == 7) sm_ylabel ("Primary Star RV");
	if (  dep == 8) sm_ylabel ("Secondary Star RV");
	if (  dep == 9) sm_ylabel ("Both RVs");

	/* Flush graphics output to screen:                                         */
	sm_gflush();

	/* Set the terminal back to normal state:                                   */
	sm_hardcopy ();
	sm_alpha ();

	free (ptype);
	#endif
	}

void create_chi2_plot_using_sm (PHOEBE_plot_device device, char *filename, PHOEBE_3D_data chi2)
	{
	#ifdef PHOEBE_SM_SUPPORT
	char working_string[255];
	char *working_str = working_string;

	int i, j;
	double min_x, max_x, min_y, max_y;

	float **data = NULL;
	float chi2_min, chi2_max;

	int dimx = chi2.ptsx;
	int dimy = chi2.ptsy;

	FILE *chi2_file;

	/* If the output is ascii table, write it out now and exit:                 */
	if (device == ascii)
		{
		chi2_file = fopen (filename, "w");
		fprintf (chi2_file, "# This table contains chi2 values for your parameter table.\n");
		fprintf (chi2_file, "#\n");
		for (i = 0; i < dimx; i++)
			{
			for (j = 0; j < dimy; j++)
				fprintf (chi2_file, "%lf\t", chi2.z[dimx*i+j]);
			fprintf (chi2_file, "\n");
			}
		fclose (chi2_file);
		return;
		}

	/* Set the terminal to graphical state:                                     */
	sm_graphics ();

	/* Initialize the file into which we are plotting to:                       */
	if (device == x11)
		sprintf (working_str, "tinyxpm %s", filename);
	if (device == eps)
		sprintf (working_str, "postfile %s", filename);
	if (device == xpm)
		sprintf (working_str, "aspectxpm %s", filename);
	if (device == gif)
		sprintf (working_str, "aspectgif %s", filename);
	if (device == ppm)
		sprintf (working_str, "ppm %s", filename);
	if (device == tinygif)
		sprintf (working_str, "tinygif %s", filename);
	if (device == tinyxpm)
		sprintf (working_str, "tinyxpm %s", filename);

	sm_device (working_str);

	/* Set the main plot characteristics:                                       */
	sm_expand (1.0001);
	sm_defvar("TeX_strings", "1");

	/* Let's find the limits of surface:                                        */
	min_x = max_x = chi2.x[0];
	for (i = 1; i < chi2.ptsx; i++)
		{
		if (chi2.x[i] < min_x) min_x = chi2.x[i];
		if (chi2.x[i] > max_x) max_x = chi2.x[i];
		}
	min_y = max_y = chi2.y[0];
	for (i = 1; i < chi2.ptsy; i++)
		{
		if (chi2.y[i] < min_y) min_y = chi2.y[i];
		if (chi2.y[i] > max_y) max_y = chi2.y[i];
		}

	/* Now the tricky part: we create an array of pointers:                     */
	data = phoebe_malloc (dimx * sizeof (*data));

	/* Next, we allocate space for the pointers in array:                       */
	for (i = 0; i < dimx; i++) data[i] = phoebe_malloc (dimy * sizeof (**data));

	/* Fill in the values:                                                      */
	for (i = 0; i < dimx; i++)
		for (j = 0; j < dimy; j++)
			data[i][j] = (float) chi2.z[i*dimy+j];

	/* Let's find the minimum and the maximum value of chi2 in a table:         */
	chi2_min = chi2_max = data[0][0];
	for (i = 0; i < dimx; i++)
		for (j = 0; j < dimy; j++)
			{
			if (chi2_min > data[i][j]) chi2_min = data[i][j];
			if (chi2_max < data[i][j]) chi2_max = data[i][j];
			}

	/* We have everything set. Now we create an image, where we have to be ca-  */
	/* reful, since SuperMongo library defines tables differently, e.g. changes */
	/* the roles of x and y in a data matrix:                                   */
	set_viewpoint_params (0, 1, 1);
	sm_defimage (data, min_y, max_y, min_x, max_x, dimy, dimx);
	sm_draw_surface (3, chi2_min, chi2_max, chi2.y, chi2.ptsy, chi2.x, chi2.ptsx);

	/* Finally, let's free the space of pointers in array:                      */
	for (i = 0; i < dimx; i++) free (data[i]);
	free (data);

	/* Flush graphics output to screen:                                         */
	sm_gflush();

	/* Set the terminal back to normal state:                                   */
	sm_hardcopy ();
	sm_alpha ();
	#endif
	}

void create_3d_image_plot_using_sm (PHOEBE_plot_device device, char *filename, PHOEBE_data data)
	{
	#ifdef PHOEBE_SM_SUPPORT
	FILE *plot_file;

	int i;
	double *ptype = NULL;

	double xmin, xmax;

	char working_string[255];
	char *working_str = working_string;

	/* If the output is ascii table, write it out now and exit:                 */
	if (device == ascii)
		{
		plot_file = fopen (filename, "w");
		fprintf (plot_file, "# y\t# z\n");
		for (i = 0; i < data.ptsno; i++)
			fprintf (plot_file, "%lf\t%lf\n", data.indep[i], data.dep[i]);
		fclose (plot_file);
		}

	/* Initialise point type to dots:                                           */
	ptype = phoebe_malloc (data.ptsno * sizeof (*ptype));
	for (i = 0; i < data.ptsno; i++) ptype[i] = 11;

	if (device == x11)
		{
		/* This transformation will fix aspect ratio problems:                      */
		for (i = 0; i < data.ptsno; i++) data.dep[i] *= 1.666667;
		sprintf (working_str, "starxpm %s/phoebe_3d_%03d.xpm", PHOEBE_TEMP_DIR, scan_temporary_directory_for_lci_file_index ("phoebe_3d"));
		}
	if (device == eps)
		sprintf (working_str, "postfile %s", filename);
	if (device == xpm)
		{
		/* This transformation will fix aspect ratio problems:                      */
		for (i = 0; i < data.ptsno; i++) data.dep[i] *= 2.0;
		sprintf (working_str, "aspectxpm %s", filename);
		}
	if (device == gif)
		sprintf (working_str, "aspectgif %s", filename);
	if (device == ppm)
		sprintf (working_str, "ppm %s", filename);
	if (device == tinygif)
		{
		/* This transformation will fix aspect ratio problems:                      */
		for (i = 0; i < data.ptsno; i++) data.dep[i] *= 1.5;
		sprintf (working_str, "tinygif %s", filename);
		}
	sm_graphics ();
	sm_device (working_str);

	/* Set the main plot characteristics:                                       */
	sm_expand (1.0001);
	sm_ptype (ptype, 3);
	sm_defvar ("TeX_strings", "1");

	for (i = 0; i < data.ptsno; i++)
		{
		if (data.indep[i] < xmin) xmin = data.indep[i];
		if (data.indep[i] > xmax) xmax = data.indep[i];
		}

	sm_limits (-1.3, 1.3, -1.3, 1.3);
	sm_box (1, 4, 4, 4);
	
	sm_points (data.indep, data.dep, data.ptsno);
	
	sm_gflush ();
	sm_hardcopy ();
	sm_alpha ();
	
	free (ptype);
	#endif
	}

void create_lc_plot_using_gnuplot (PHOEBE_plot_device device, char *filename, PHOEBE_data synthetic_data, PHOEBE_data experimental_data, int indep, int dep, int grid, int box, double x_offset, double y_offset, double zoom, int plot_synthetic, int plot_experimental)
{
#ifdef PHOEBE_GNUPLOT_SUPPORT
	int i;

	/*
	 * Plot limits; values are assigned in case this function would ever be
	 * called with both plot_synthetic and plot_experimental switches off.
	 */

	double xmin = 0.0, xmax = 0.0, ymin = 0.0, ymax = 0.0;

	FILE *plot_file;

	char name0[255];
	char name1[255];
	char name2[255];
	char outfile[255];
	char line[255];
	int	tmpfd0, tmpfd1, tmpfd2;

	/* If the output is ascii table, write it out now and exit:               */
	if (device == ascii) {
		plot_file = fopen (filename, "w");
		if (plot_synthetic == 1) {
			fprintf (plot_file, "# indep\t# dep\t# weight\n");
			for (i = 0; i < synthetic_data.ptsno; i++)
				fprintf (plot_file, "%lf\t%lf\t%lf\n", synthetic_data.indep[i], synthetic_data.dep[i], synthetic_data.weight[i]);
		}
		if (plot_experimental == 1) {
			fprintf (plot_file, "# indep\t\t# dep\t\t# weight\n");
			for (i = 0; i < experimental_data.ptsno; i++)
				fprintf (plot_file, "%lf\t%lf\t%lf\n", experimental_data.indep[i], experimental_data.dep[i], experimental_data.weight[i]);
		}
		fclose (plot_file);
		return;
	}

	/* Open temporary data file(s) for output:                                */
	if (plot_synthetic == 1 && plot_experimental == 1) {
		sprintf(name1, "%s/gnuplot-i-XXXXXX", PHOEBE_TEMP_DIR);
		if ( (tmpfd1 = mkstemp (name1)) == -1) {
			phoebe_warning ("cannot create temporary file: exiting plot");
			return;
		}

		/* Write data to this file  */
		for (i=0 ; i<synthetic_data.ptsno; i++) {
			sprintf(line, "%lf\t%lf\t%lf\n", synthetic_data.indep[i], synthetic_data.dep[i], synthetic_data.weight[i]) ;
			write(tmpfd1, line, strlen(line));
		}
		close(tmpfd1) ;

		sprintf(name2, "%s/gnuplot-i-XXXXXX", PHOEBE_TEMP_DIR);
		if ( (tmpfd2 = mkstemp (name2)) == -1) {
			phoebe_warning ("cannot create temporary file: exiting plot") ;
			return;
		}

		/* Write data to this file  */
		for (i=0 ; i<experimental_data.ptsno; i++) {
			sprintf(line, "%lf\t%lf\t%lf\n", experimental_data.indep[i], experimental_data.dep[i], experimental_data.weight[i]);
			write(tmpfd2, line, strlen(line));
		}
		close(tmpfd1) ;

	}
	else {
		sprintf(name1, "%s/gnuplot-i-XXXXXX", PHOEBE_TEMP_DIR);
		if ((tmpfd1=mkstemp(name1))==-1) {
			phoebe_warning ("cannot create temporary file: exiting plot") ;
			return;
		}

		if (plot_synthetic == 1) {
	 	   	/* Write data to this file  */
			for (i=0 ; i<synthetic_data.ptsno; i++) {
				sprintf(line, "%lf\t%lf\t%lf\n", synthetic_data.indep[i], synthetic_data.dep[i], synthetic_data.weight[i]) ;
				write(tmpfd1, line, strlen(line));
			}
		    close(tmpfd1) ;
		}

		if (plot_experimental == 1) {
			/* Write data to this file  */
			for (i=0 ; i<experimental_data.ptsno; i++) {
				sprintf (line, "%lf\t%lf\t%lf\n", experimental_data.indep[i], experimental_data.dep[i], experimental_data.weight[i]);
				write(tmpfd1, line, strlen(line));
			}
		    close(tmpfd1) ;
  		}
	}

	/* Open temporary file for gnuplot commands   */
	sprintf(name0, "%s/gnuplot-i-gnu-XXXXXX", PHOEBE_TEMP_DIR);
	if ((tmpfd0=mkstemp(name0))==-1) {
		phoebe_warning ("cannot create temporary file: exiting plot");
		return;
	}

	/* Write commands to this file  */
	if (device == x11)
		sprintf(line, "set size 0.8,0.53; set terminal pbm small color\n");
	if (device == eps) {
		sprintf(line, "set output \"%s\"\n",filename);
		write(tmpfd0, line, strlen(line));
		sprintf(line, "set terminal postscript eps enhanced colour \n");
	}
	if (device == xpm) {
		sprintf(line, "set output \"%s\"\n",filename);
		write(tmpfd0, line, strlen(line));
		sprintf(line, "set terminal pbm small color\n");
	}
	if (device == ppm) {
		sprintf(line, "set output \"%s\"\n",filename);
		write(tmpfd0, line, strlen(line));
		sprintf(line, "set terminal pbm small color\n");
	}
	if (device == png) {
		sprintf(line, "set output \"%s\"\n",filename);
		write(tmpfd0, line, strlen(line));
		sprintf(line, "set terminal png small\n");
	}
	write(tmpfd0, line, strlen(line));

	sprintf(line, "set mxtics\n");
	write(tmpfd0, line, strlen(line));
	sprintf(line, "set mytics\n");
	write(tmpfd0, line, strlen(line));

	/* Calculate and set plotting limits:                                     */
	calculate_plot_limits (synthetic_data, experimental_data, &xmin, &ymin, &xmax, &ymax, plot_synthetic, plot_experimental, x_offset, y_offset, zoom);
	if (dep == 8) {       /* Magnitudes */
		if (!isnan(xmin) && !isnan(xmax) && !isinf(xmax) && !isinf(xmin)) {
			sprintf (line,"set xrange[%f:%f]\n",xmin,xmax);
			write(tmpfd0, line, strlen(line));
		}
		if (!isnan(ymin) && !isnan(ymax) && !isinf(ymax) && !isinf(ymin)) {
			sprintf (line,"set yrange[%f:%f]\n",ymax,ymin);
			write(tmpfd0, line, strlen(line));
		}
	}
	else {                /* Fluxes     */
		if (!isnan(xmin) && !isnan(xmax) && !isinf(xmax) && !isinf(xmin)) {
			sprintf (line,"set xrange[%f:%f]\n",xmin,xmax);
			write(tmpfd0, line, strlen(line));
		}
		if (!isnan(ymin) && !isnan(ymax) && !isinf(ymax) && !isinf(ymin)) {
			sprintf (line,"set yrange[%f:%f]\n",ymin,ymax);
			write(tmpfd0, line, strlen(line));
		}
	}
	if (box == 1) { /* just xy-axes */
		sprintf (line,"set border 3\n");
		write(tmpfd0, line, strlen(line));
		sprintf (line,"set xtics border nomirror\n");
		write(tmpfd0, line, strlen(line));
		sprintf (line,"set ytics border nomirror\n");
		write(tmpfd0, line, strlen(line));
	}
	if (box  == 0) { /* box */
		sprintf (line,"set border 31\n");
		write(tmpfd0, line, strlen(line));
		sprintf (line,"set xtics border mirror\n");
		write(tmpfd0, line, strlen(line));
		sprintf (line,"set ytics border mirror\n");
		write(tmpfd0, line, strlen(line));
	}

	if (grid == 1) { /* grid */
		sprintf (line,"set grid nomxtics nomytics lt 0\n");
		write(tmpfd0, line, strlen(line));
	}
	if (grid == 2) { /* fine grid */
		sprintf (line,"set grid xtics ytics mxtics mytics lt 0\n");
		write(tmpfd0, line, strlen(line));
	}

	if (indep == 1) {
		sprintf (line,"set xlabel \"HJD\"\n");
		write(tmpfd0, line, strlen(line));
	}
	if (indep == 2) {
		sprintf (line,"set xlabel \"Phase\"\n");
		write(tmpfd0, line, strlen(line));
	}
	if (  dep == 3) {
		sprintf (line,"set ylabel \"Primary Star Flux\"\n");
		write(tmpfd0, line, strlen(line));
	}
	if (  dep == 4) {
		sprintf (line,"set ylabel \"Secondary Star Flux\"\n");
		write(tmpfd0, line, strlen(line));
	}
	if (  dep == 5) {
		sprintf (line,"set ylabel \"Total Flux\"\n");
		write(tmpfd0, line, strlen(line));
	}
	if (  dep == 6) {
		sprintf (line,"set ylabel \"Normalized Flux\"\n");
		write(tmpfd0, line, strlen(line));
	}
	if (  dep == 8) {
		sprintf (line,"set ylabel \"Magnitude\"\n");
		write(tmpfd0, line, strlen(line));
	}

	if (plot_synthetic == 1 && plot_experimental == 1) {
		sprintf(line,"plot \"%s\"  t\"\" with points lt 3 lw 1 pt 6, \"%s\" t \"\" with lines 1\n",name2,name1);
		write(tmpfd1, line, strlen(line));
	}
	else {
		if (plot_synthetic == 1) {
			sprintf(line,"plot \"%s\" t \"\" with lines 1\n",name1);
			write(tmpfd1, line, strlen(line));
		}
		if (plot_experimental == 1) {
			sprintf(line,"plot \"%s\" t \"\" with points lt 3 lw 1 pt 6\n",name1);
			write(tmpfd1, line, strlen(line));
		}
	}

	sprintf(line, "set output\n");
	write(tmpfd1, line, strlen(line));
	sprintf(line, "quit\n");
	write(tmpfd1, line, strlen(line));

	sprintf (outfile, "%s/phoebe_lc_%03d.xpm", PHOEBE_TEMP_DIR,
		scan_temporary_directory_for_lci_file_index ("phoebe_lc"));

	if (device == x11) {
		phoebe_debug ("device=x11\n");
		sprintf(line,"gnuplot \"%s\" | ppmtoxpm > %s",name0,outfile);
	}
	else {
		phoebe_debug ("device!=x11\n");
		sprintf(line,"gnuplot \"%s\"",name0);
	}

	system(line);
	remove(name0);

	if (plot_synthetic == 1 && plot_experimental == 1) {
		remove(name1);
		remove(name2);
	}
	else {
		remove(name1);
	}
#endif
}

void create_rv_plot_using_gnuplot (PHOEBE_plot_device device, char *filename, PHOEBE_data synthetic_data, PHOEBE_data experimental_data, int indep, int dep, int grid, int box, double x_offset, double y_offset, double zoom, int plot_synthetic, int plot_experimental)
        {
	#ifdef PHOEBE_GNUPLOT_SUPPORT
	char working_string[255];
	char *working_str = working_string;

	int i;

	/* Plot limits; values are assigned in case this function would ever be     */
	/* called with both plot_synthetic and plot_experimental switches off.      */
	double xmin = 0.0, xmax = 0.0, ymin = 0.0, ymax = 0.0;

	/* Point type is assigned to each point individually, thus an array:        */
	double *ptype = NULL;

	FILE *plot_file;

    	char    name0[255];
    	char    name1[255];
    	char    name2[255];
        char    outfile[255];
	char    line[255];
	int	tmpfd0, tmpfd1, tmpfd2;

	/* If the output is ascii table, write it out now and exit:                 */
	if (device == ascii)
		{
		plot_file = fopen (filename, "w");
		if (plot_synthetic == 1)
			{
			fprintf (plot_file, "# indep\t\t# dep\t\t# weight\n");
			for (i = 0; i < synthetic_data.ptsno; i++)
				fprintf (plot_file, "%lf\t%lf\t%lf\n", synthetic_data.indep[i], synthetic_data.dep[i], synthetic_data.weight[i]);
			}
		if (plot_experimental == 1)
			{
			fprintf (plot_file, "# indep\t# dep\t# weight\n");
			for (i = 0; i < experimental_data.ptsno; i++)
				fprintf (plot_file, "%lf\t%lf\t%lf\n", experimental_data.indep[i], experimental_data.dep[i], experimental_data.weight[i]);
			}
		fclose (plot_file);
		return;
		}

	/* Open temporary data file(s) for output   */
	if (plot_synthetic == 1 && plot_experimental == 1)
		{
		sprintf(name1, "%s/gnuplot-i-XXXXXX", PHOEBE_TEMP_DIR);
		if ((tmpfd1=mkstemp(name1))==-1)
			{
			phoebe_warning ("cannot create temporary file: exiting plot") ;
			return ;
			}

		/* Write data to this file  */
		for (i=0 ; i<synthetic_data.ptsno; i++)
			{
			if (dep == 9 && i == (int)(synthetic_data.ptsno/2))
				{
				sprintf(line,"     \n");
				write(tmpfd1, line, strlen(line));
				sprintf(line,"     \n");
				write(tmpfd1, line, strlen(line));
				}
			sprintf(line, "%lf\t%lf\t%lf\n", synthetic_data.indep[i], synthetic_data.dep[i], synthetic_data.weight[i]);
			write(tmpfd1, line, strlen(line));
			}
		close(tmpfd1) ;

		sprintf(name2, "%s/gnuplot-i-XXXXXX", PHOEBE_TEMP_DIR);
		if ((tmpfd2=mkstemp(name2))==-1)
			{
        		phoebe_warning ("cannot create temporary file: exiting plot") ;
        		return ;
			}

		/* Write data to this file  */
		for (i=0 ; i<experimental_data.ptsno; i++)
			{
        		sprintf(line, "%lf\t%lf\t%lf\n", experimental_data.indep[i], experimental_data.dep[i], experimental_data.weight[i]);
			write(tmpfd2, line, strlen(line));
			}
		close(tmpfd1) ;

		}
	else
		{
		sprintf(name1, "%s/gnuplot-i-XXXXXX", PHOEBE_TEMP_DIR);
	    	if ((tmpfd1=mkstemp(name1))==-1)
			{
			phoebe_warning ("cannot create temporary file: exiting plot");
        		return ;
			}

		if (plot_synthetic == 1 )
			{
	 	   	/* Write data to this file  */
    			for (i=0 ; i<synthetic_data.ptsno; i++)
				{
                                if (dep == 9 && i == (int)(synthetic_data.ptsno/2))
                                        {
                                        sprintf(line,"     \n");
                                        write(tmpfd1, line, strlen(line));
                                        sprintf(line,"     \n");
                                        write(tmpfd1, line, strlen(line));
                                        }
        			sprintf(line, "%lf\t%lf\t%lf\n", synthetic_data.indep[i], synthetic_data.dep[i], synthetic_data.weight[i]) ;
				write(tmpfd1, line, strlen(line));
				}
		    	close(tmpfd1) ;
			}

		if (plot_experimental == 1 )
			{
		    	/* Write data to this file  */
    			for (i=0 ; i<experimental_data.ptsno; i++)
				{
				sprintf (line, "%lf\t%lf\t%lf\n", experimental_data.indep[i], experimental_data.dep[i], experimental_data.weight[i]);
				write(tmpfd1, line, strlen(line));
				}
		    	close(tmpfd1) ;
  			}
		}

    	/* Open temporary file for gnuplot commands   */
	sprintf(name0, "%s/gnuplot-i-gnu-XXXXXX", PHOEBE_TEMP_DIR);
    	if ((tmpfd0=mkstemp(name0))==-1)
		{
        	phoebe_warning ("cannot create temporary file: exiting plot") ;
        	return ;
	    	}

    	/* Write commands to this file  */
        if (device == x11)
                sprintf(line, "set size 0.8,0.53; set terminal pbm small color\n");
        if (device == eps)
                {
                sprintf(line, "set output \"%s\"\n",filename);
                write(tmpfd0, line, strlen(line));
                sprintf(line, "set terminal postscript eps enhanced colour \n");
                }
        if (device == xpm)
                {
                sprintf(line, "set output \"%s\"\n",filename);
                write(tmpfd0, line, strlen(line));
                sprintf(line, "set terminal pbm small color\n");
                }
        if (device == ppm)
                {
                sprintf(line, "set output \"%s\"\n",filename);
                write(tmpfd0, line, strlen(line));
                sprintf(line, "set terminal pbm small color\n");
                }
        if (device == png)
                {
                sprintf(line, "set output \"%s\"\n",filename);
                write(tmpfd0, line, strlen(line));
                sprintf(line, "set terminal png small\n");
                }
	write(tmpfd0, line, strlen(line));

        sprintf(line, "set mxtics\n");
	write(tmpfd0, line, strlen(line));
        sprintf(line, "set mytics\n");
	write(tmpfd0, line, strlen(line));

	/* Calculate and set plotting limits:                                       */
	calculate_plot_limits (synthetic_data, experimental_data, &xmin, &ymin, &xmax, &ymax, plot_synthetic, plot_experimental, x_offset, y_offset, zoom);
        if (!isnan(xmin) && !isnan(xmax) && !isinf(xmax) && !isinf(xmin))
                {
                sprintf (line,"set xrange[%f:%f]\n",xmin,xmax);
        	write(tmpfd0, line, strlen(line));
                }
        if (!isnan(ymin) && !isnan(ymax) && !isinf(ymax) && !isinf(ymin))
                {
                sprintf (line,"set yrange[%f:%f]\n",ymin,ymax);
	        write(tmpfd0, line, strlen(line));
                }


	if (box  == 1) /* just xy-axes */
                {
                sprintf (line,"set border 3\n");
		write(tmpfd0, line, strlen(line));
                sprintf (line,"set xtics border nomirror\n");
		write(tmpfd0, line, strlen(line));
                sprintf (line,"set ytics border nomirror\n");
		write(tmpfd0, line, strlen(line));
                }
	if (box  == 0) /* box */
                {
                sprintf (line,"set border 31\n");
		write(tmpfd0, line, strlen(line));
                sprintf (line,"set xtics border mirror\n");
		write(tmpfd0, line, strlen(line));
                sprintf (line,"set ytics border mirror\n");
		write(tmpfd0, line, strlen(line));
                }

	if (grid == 1) /* grid */
                {
                sprintf (line,"set grid nomxtics nomytics lt 0\n");
		write(tmpfd0, line, strlen(line));
                }
	if (grid == 2) /* fine grid */
                {
                sprintf (line,"set grid xtics ytics mxtics mytics lt 0\n");
		write(tmpfd0, line, strlen(line));
                }

	if (indep == 1)
		{
                sprintf (line,"set xlabel \"HJD\"\n");
		write(tmpfd0, line, strlen(line));
		}
	if (indep == 2)
		{
                sprintf (line,"set xlabel \"Phase\"\n");
		write(tmpfd0, line, strlen(line));
		}
	if (  dep == 3)
		{
                sprintf (line,"set ylabel \"Normalized Primary Star RV\"\n");
		write(tmpfd0, line, strlen(line));
		}
	if (  dep == 4)
		{
                sprintf (line,"set ylabel \"Normalized Secondary Star RV\"\n");
		write(tmpfd0, line, strlen(line));
		}
	if (  dep == 5)
		{
                sprintf (line,"set ylabel \"Primary Star Eclipse Corrections\"\n");
		write(tmpfd0, line, strlen(line));
		}
	if (  dep == 6)
		{
                sprintf (line,"set ylabel \"Secondary Star Eclipse Corrections\"\n");
		write(tmpfd0, line, strlen(line));
		}
	if (  dep == 7)
		{
                sprintf (line,"set ylabel \"Primary Star RV\"\n");
		write(tmpfd0, line, strlen(line));
		}
	if (  dep == 8)
		{
                sprintf (line,"set ylabel \"Secondary Star RV\"\n");
		write(tmpfd0, line, strlen(line));
		}
	if (  dep == 9)
		{
                sprintf (line,"set ylabel \"Both RVs\"\n");
		write(tmpfd0, line, strlen(line));
		}

	if (plot_synthetic == 1 && plot_experimental ==1)
		{
	        sprintf(line,"plot \"%s\"  t\"\" with points lt 3 lw 1 pt 6, \"%s\" t \"\" with lines 1\n",name2,name1);
		write(tmpfd1, line, strlen(line));
		}
	else
		{
		if (plot_synthetic == 1)
			{
               	        sprintf(line,"plot \"%s\" t \"\" with lines 1\n",name1);
        		write(tmpfd1, line, strlen(line));
			}
		if (plot_experimental == 1)
			{
		        sprintf(line,"plot \"%s\" t \"\" with points lt 3 lw 1 pt 6\n",name1);
			write(tmpfd1, line, strlen(line));
			}
		}

        sprintf(line, "set output\n");
	write(tmpfd1, line, strlen(line));
        sprintf(line, "quit\n");
	write(tmpfd1, line, strlen(line));

        sprintf (outfile, "%s/phoebe_rv_%03d.xpm", PHOEBE_TEMP_DIR,
                scan_temporary_directory_for_lci_file_index ("phoebe_rv"));

        if (device == x11)
                {
                sprintf(line,"gnuplot \"%s\" | ppmtoxpm > %s",name0,outfile);
                }
        else
                {
                sprintf(line,"gnuplot \"%s\"",name0);
                }

	system(line);
	remove(name0);
        if (plot_synthetic ==1 && plot_experimental == 1)
                {
		remove(name1);
		remove(name2);
                }
        else        
                {
        	remove(name1);
                }
	#endif
        }

void create_chi2_plot_using_gnuplot (PHOEBE_plot_device device, char *filename, PHOEBE_3D_data chi2)
	{
	#ifdef PHOEBE_GNUPLOT_SUPPORT
	int i, j, k;
	double min_x, max_x, min_y, max_y;

	float chi2_min, chi2_max;

	int dimx = chi2.ptsx;
	int dimy = chi2.ptsy;

	FILE *chi2_file;

    	char    name0[255];
    	char    name1[255];
        char    outfile[255];
	char    line[255];
	int	tmpfd0, tmpfd1;

	/* If the output is ascii table, write it out now and exit:                 */
	if (device == ascii)
		{
		chi2_file = fopen (filename, "w");
		fprintf (chi2_file, "# This table contains chi2 values for your parameter table.\n");
		fprintf (chi2_file, "#\n");
		for (i = 0; i < dimx; i++)
			{
			for (j = 0; j < dimy; j++)
				fprintf (chi2_file, "%lf\t", chi2.z[dimx*i+j]);
			fprintf (chi2_file, "\n");
			}
		fclose (chi2_file);
		return;
		}

	/* Let's find the limits of surface:                                        */
	min_x = max_x = chi2.x[0];
	for (i = 1; i < chi2.ptsx; i++)
		{
		if (chi2.x[i] < min_x) min_x = chi2.x[i];
		if (chi2.x[i] > max_x) max_x = chi2.x[i];
		}
	min_y = max_y = chi2.y[0];
	for (i = 1; i < chi2.ptsy; i++)
		{
		if (chi2.y[i] < min_y) min_y = chi2.y[i];
		if (chi2.y[i] > max_y) max_y = chi2.y[i];
		}

	/* Let's find the minimum and the maximum value of chi2 in a table:         */
	chi2_min = chi2_max = chi2.z[0];
	for (i = 0; i < dimx; i++)
                {
		for (j = 0; j < dimy; j++)
			{
                        k=i*dimy+j;
			if (chi2_min > chi2.z[k]) chi2_min = chi2.z[k];
			if (chi2_max < chi2.z[k]) chi2_max = chi2.z[k];
			}
                }

    	/* Open temporary data file(s) for output   */
	sprintf(name1, "%s/gnuplot-i-XXXXXX", PHOEBE_TEMP_DIR);
    	if ((tmpfd1=mkstemp(name1))==-1)
		{
       		phoebe_warning ("cannot create temporary file: exiting plot") ;
       		return ;
                }

  	/* Write data to this file  */
       	for (i = 0; i < dimx; i++)
                {       
       		for (j = 0; j < dimy; j++)
                        {
        		sprintf(line, "%lf\t%lf\t%lf\n", chi2.x[i], chi2.y[j], chi2.z[i*dimy+j]) ;
                	write(tmpfd1, line, strlen(line));
	        	}
      		sprintf(line, "\n") ;
              	write(tmpfd1, line, strlen(line));
                }
    	close(tmpfd1) ;
        
    	/* Open temporary file for gnuplot commands   */
	sprintf(name0, "%s/gnuplot-i-gnu-XXXXXX", PHOEBE_TEMP_DIR);
    	if ((tmpfd0=mkstemp(name0))==-1)
		{
        	phoebe_warning ("cannot create temporary file: exiting plot") ;
        	return ;
	    	}

    	/* Write commands to this file  */
        if (device == x11)
                sprintf(line, "set size 0.4,0.4; set terminal pbm small color\n");
        if (device == eps)
                {
                sprintf(line, "set output \"%s\"\n",filename);
                write(tmpfd0, line, strlen(line));
                sprintf(line, "set terminal postscript eps enhanced colour \n");
                }
        if (device == xpm)
                {
                sprintf(line, "set output \"%s\"\n",filename);
                write(tmpfd0, line, strlen(line));
                sprintf(line, "set terminal pbm small color\n");
                }
        if (device == ppm)
                {
                sprintf(line, "set output \"%s\"\n",filename);
                write(tmpfd0, line, strlen(line));
                sprintf(line, "set terminal pbm small color\n");
                }
        if (device == png)
                {
                sprintf(line, "set output \"%s\"\n",filename);
                write(tmpfd0, line, strlen(line));
                sprintf(line, "set terminal png small\n");
                }
        write(tmpfd0, line, strlen(line));
        
        sprintf(line,"set border 21\n");
        write(tmpfd0, line, strlen(line));
        sprintf(line,"set ticslevel 0\n");
        write(tmpfd0, line, strlen(line));
        sprintf(line,"set mxtics\n");
        write(tmpfd0, line, strlen(line));
        sprintf(line,"set mytics\n");
        write(tmpfd0, line, strlen(line));
        sprintf(line,"set mztics\n");
        write(tmpfd0, line, strlen(line));
        sprintf(line,"set xtics nomirror\n");
        write(tmpfd0, line, strlen(line));
        sprintf(line,"set ytics nomirror\n");
        write(tmpfd0, line, strlen(line));
        sprintf(line,"set ztics nomirror\n");
        write(tmpfd0, line, strlen(line));

        sprintf(line,"set xrange[%f:%f]\n",min_x,max_x);
        write(tmpfd0, line, strlen(line));
        sprintf(line,"set yrange[%f:%f]\n",min_y,max_y);
        write(tmpfd0, line, strlen(line));
        if (!isnan(chi2_min) && !isnan(chi2_max) && !isinf(chi2_min) && !isinf(chi2_max))
                {
                sprintf(line,"set zrange[%f:%f]\n",chi2_min,chi2_max);
                write(tmpfd0, line, strlen(line));
                }
        sprintf(line,"set view 60,45,1,1\n");
        write(tmpfd0, line, strlen(line));
        
        sprintf(line,"splot \"%s\" t \"\" with lines 3\n",name1);
        write(tmpfd0, line, strlen(line));

        sprintf(line, "set output\n");
	write(tmpfd1, line, strlen(line));
        sprintf(line, "quit\n");
	write(tmpfd1, line, strlen(line));

        sprintf (outfile, "%s/phoebe_c2.xpm", PHOEBE_TEMP_DIR);

        if (device == x11)
                {
                sprintf(line,"gnuplot \"%s\" | ppmtoxpm > %s",name0,outfile);
                }
        else
                {
                sprintf(line,"gnuplot \"%s\"",name0);
                }
	system(line);
	remove(name0);
	remove(name1);
	#endif
        }

void create_3d_image_plot_using_gnuplot (PHOEBE_plot_device device, char *filename, PHOEBE_data data)
	{
	#ifdef PHOEBE_GNUPLOT_SUPPORT
	FILE *plot_file;

	int i;

	double xmin, xmax;

	char working_string[255];
	char *working_str = working_string;

	char name0[255];
	char name1[255];
	char outfile[255];
	char line[255];
	int	tmpfd0, tmpfd1;

	/* If the output is ascii table, write it out now and exit:                 */
	if (device == ascii)
		{
		plot_file = fopen (filename, "w");
		fprintf (plot_file, "# y\t# z\n");
		for (i = 0; i < data.ptsno; i++)
			fprintf (plot_file, "%lf\t%lf\n", data.indep[i], data.dep[i]);
		fclose (plot_file);
		}

	/* Open temporary data file(s) for output   */
	sprintf(name1, "%s/gnuplot-i-XXXXXX", PHOEBE_TEMP_DIR);
	if ((tmpfd1=mkstemp(name1))==-1)
		{
		phoebe_warning ("cannot create temporary file: exiting plot") ;
		return ;
		}

	for (i = 0; i < data.ptsno; i++)
		{
		if (data.indep[i] < xmin) xmin = data.indep[i];
		if (data.indep[i] > xmax) xmax = data.indep[i];
		}

	/* Write data to this file */
	for (i=0 ; i<data.ptsno; i++)
		{
		sprintf(line, "%lf\t%lf\n", data.indep[i], data.dep[i]) ;
		write(tmpfd1, line, strlen(line));
		}
	close(tmpfd1) ;

	/* Open temporary file for gnuplot commands   */
	sprintf(name0, "%s/gnuplot-i-gnu-XXXXXX", PHOEBE_TEMP_DIR);
	if ((tmpfd0=mkstemp(name0))==-1)
		{
		phoebe_warning ("cannot create temporary file: exiting plot") ;
		return ;
		}

	/* Write commands to this file  */
	if (device == x11)
		sprintf(line, "set size ratio -1 0.5,0.4; set terminal pbm small color\n");
	if (device == eps)
		{
		sprintf(line, "set output \"%s\"\n",filename);
		write(tmpfd0, line, strlen(line));
		sprintf(line, "set size ratio -1; set terminal postscript eps enhanced colour \n");
		}
	if (device == xpm)
		{
		sprintf(line, "set output \"%s\"\n",filename);
		write(tmpfd0, line, strlen(line));
		sprintf(line, "set size ratio -1; set terminal pbm small color\n");
		}
	if (device == ppm)
		{
		sprintf(line, "set output \"%s\"\n",filename);
		write(tmpfd0, line, strlen(line));
		sprintf(line, "set size ratio -1; set terminal pbm small color\n");
		}
	if (device == png)
		{
		sprintf(line, "set output \"%s\"\n",filename);
		write(tmpfd0, line, strlen(line));
		sprintf(line, "set size ratio -1; set terminal png small\n");
		}
	write(tmpfd0, line, strlen(line));

	sprintf(line, "set mxtics\n");
	write(tmpfd0, line, strlen(line));
	sprintf(line, "set nomytics\n");
	write(tmpfd0, line, strlen(line));

	sprintf (line,"set xrange[-1.3:1.3]\n");
	write(tmpfd0, line, strlen(line));
	sprintf (line,"set yrange[-0.65:0.65]\n");
	write(tmpfd0, line, strlen(line));

	sprintf (line,"set border 1\n");
	write(tmpfd0, line, strlen(line));
	sprintf (line,"set xtics border nomirror\n");
	write(tmpfd0, line, strlen(line));
	sprintf (line,"set noytics\n");
	write(tmpfd0, line, strlen(line));

	sprintf(line,"plot \"%s\" t \"\" with points lt 0 lw 1 pt 0\n",name1);
	write(tmpfd1, line, strlen(line));

	sprintf(line, "set output\n");
	write(tmpfd1, line, strlen(line));
	sprintf(line, "quit\n");
	write(tmpfd1, line, strlen(line));

	sprintf (outfile, "%s/phoebe_3d_%03d.xpm", PHOEBE_TEMP_DIR,
	scan_temporary_directory_for_lci_file_index ("phoebe_3d"));
	if (device == x11)
		{
		sprintf(line,"gnuplot \"%s\" | ppmtoxpm > %s",name0,outfile);
		}
	else
		{
		sprintf(line,"gnuplot \"%s\"",name0);
		}

	system(line);
	remove(name0);
	remove(name1);
	#endif
	}
