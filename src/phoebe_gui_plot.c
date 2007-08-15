#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "phoebe_allocations.h"
#include "phoebe_binning.h"
#include "phoebe_calculations.h"
#include "phoebe_chi2.h"
#include "phoebe_error_handling.h"
#include "phoebe_global.h"
#include "phoebe_gui_accessories.h"
#include "phoebe_gui_callbacks.h"
#include "phoebe_gui_support.h"
#include "phoebe_gui_plot.h"
#include "phoebe_plot.h"
#include "phoebe_transformations.h"

void plot_lc_plot (PHOEBE_plot_device device, char *filename)
	{
	int i;

	PHOEBE_data synthetic_data;
	PHOEBE_data experimental_data;

	PHOEBE_main_parameters   main      = read_in_main_parameters ();
	PHOEBE_switches          switches  = read_in_switches ();
	PHOEBE_limb_darkening    ld        = read_in_ld_coefficients ();
	PHOEBE_curve_parameters  curve     = read_in_curve_parameters ();
	PHOEBE_spots             spots;

	PHOEBE_wl_dependent_parameters mono;
	PHOEBE_calculated_parameters params;

	GtkWidget *readout_widget;
	GtkWidget *warning_window;

	char *readout_str;

	char working_string[255];
	char *working_str = working_string;

	int VERTEXES;

	int chosen_filter;

	int INDEP;   /* This switch determines the independent variable:          */
                 /*   INDEP = 1 .. heliocentric julian date                   */
                 /*   INDEP = 2 .. phase                                      */

	int DEP;     /* This switch determines the dependent variable:            */
                 /*   DEP = 3 .. normalized primary star flux                 */
                 /*   DEP = 4 .. normalized secondary star flux               */
                 /*   DEP = 5 .. normalized total flux (from both stars)      */
                 /*   DEP = 6 .. FACTORed total flux (from both stars)        */
                 /*   DEP = 8 .. MZEROed total magnitude (from both stars)    */
                 /*   DEP = 9 .. light curve residuals                        */

	int BOX;     /* This switch determines how does SuperMongo limit plots:   */
                 /*   BOX = 0 .. draw ticked axes (x and y)                   */
                 /*   BOX = 1 .. draw ticked box                              */

	int GRID;    /* This switch determines what kind of gridding is used:     */
                 /*   GRID = 0 .. no gridding                                 */
                 /*   GRID = 1 .. coarse grid                                 */
                 /*   GRID = 2 .. fine grid                                   */

	int DATA;    /* This switch determines whether the user wants to plot ex- */
	             /* perimental data:                                          */
                 /*   DATA = 0 .. do not plot experimental data               */
                 /*   DATA = 1 .. plot experimental data                      */

	int MODEL;   /* This switch determines whether the user wants to plot     */
	             /* synthetic data:                                           */
                 /*   MODEL = 0 .. do not plot synthetic data                 */
                 /*   MODEL = 1 .. plot synthetic data                        */

	int ALIASING;/* This switch determines if the phases are to be aliased to */
                 /* a wider/narrower range or not.                            */
				 /*   ALIASING = 0 .. don't use aliasing, always [-0.5, 0.5]  */
                 /*   ALIASING = 1 .. use aliasing to [PHSTRT, PHSTOP].       */

	int RESIDUALS; /* This switch determines whether the plot should contain  */
                   /* overlapped synthetic and experimental data or should it */
				   /* calculate residuals and plot them against INDEP:        */
				   /*   RESIDUALS = 0 .. don't calculate/plot residuals       */
				   /*   RESIDUALS = 1 .. calculate/plot residuals             */

	int REDDENING; /* This switch determines if the reddening/extinction effect */
                   /* should be compensated for input magnitudes:               */
				   /*   REDDENING = 0 .. don't remove reddening from input data */
				   /*   REDDENING = 1 .. remove reddening from input data       */

	double chi2 = 0.0;

	phoebe_debug ("entering 'plot_lc_plot ()' function.\n");

	/* Let's read in the spots:                                                 */
	allocate_memory_for_spots (&spots);
	read_in_spots (&spots);

	/* We want to plot LCs, so we set MPAGE to 1: */
	switches.MPAGE = 1;

	/* The filter name combo box contains either the name of the chosen filter  */
	/* or the "None Specified" entry. If the filter name is defined, we have to */
	/* initialize the wavelength-dependent parameters based on that filter for  */
	/* synthetic LC generation. If not, we assume the default values.           */
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_data_combo_box_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));

	chosen_filter = -1;
	for (i = 0; i < switches.NLC; i++)
		if (strcmp (readout_str, PHOEBE_lc_data[i].filter) == 0)
			chosen_filter = i;
	phoebe_debug ("chosen filter number:       %d\n", chosen_filter);

	/* If the filter is not specified (chosen_filter == -1), we read in the de- */
	/* faults, else we read in filter-dependent parameters:                     */
	if (chosen_filter == -1)
		{
		phoebe_warning ("No filter selected: assuming default Johnson V (550nm) filter.\n");
		mono.WLA   = 550.0;
		mono.IBAND = 7;
		mono.HLA   = 10.0;
		mono.CLA   = 10.0;
		mono.X1A   = 0.5;
		mono.X2A   = 0.5;
		mono.Y1A   = 0.5;
		mono.Y2A   = 0.5;
		mono.EL3   = 0.0;
		mono.OPSF  = 0.0;
		mono.SIGMA = 0.0;
		}
	else mono = read_in_wl_dependent_parameters (readout_str);

	/* Read out phase settings from LC Plot Window: */
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_vertexes_value");
	VERTEXES = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_phstrt_value");
	curve.PHSTRT = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_phend_value");
	curve.PHSTOP = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	curve.PHIN = (curve.PHSTOP - curve.PHSTRT) / VERTEXES;
	curve.PHSTOP += 1e-6; /* To have the last vertex included */
	curve.HJDST = main.HJD0 + main.PERIOD * curve.PHSTRT;
	curve.HJDSP = main.HJD0 + main.PERIOD * curve.PHSTOP;
	curve.HJDIN = main.PERIOD * curve.PHIN;

	phoebe_debug ("number of vertices:         %d\n", VERTEXES);
	phoebe_debug ("starting phase of the plot: %3.3lf\n", curve.PHSTRT);
	phoebe_debug ("ending phase of the plot:   %3.3lf\n", curve.PHSTOP);
	phoebe_debug ("phase increment:            %3.3lf\n", curve.PHIN);

	/* What variable user chooses to be independent (time or phase): */
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_independent_combo_box_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	if (strcmp (readout_str, "Time") == 0)  { INDEP = 1; switches.JDPHS = 1; }
	if (strcmp (readout_str, "Phase") == 0) { INDEP = 2; switches.JDPHS = 2; }

	phoebe_debug ("independent variable:       %d\n", INDEP);

	/* What variable user chooses to be dependent (flux or magnitude): */
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_dependent_combo_box_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	if (strcmp (readout_str, "Primary Star Flux") == 0)    DEP = 3;
	if (strcmp (readout_str, "Secondary Star Flux") == 0)  DEP = 4;
	if (strcmp (readout_str, "Total Flux") == 0)           DEP = 5;
	if (strcmp (readout_str, "Normalized Flux") == 0)      DEP = 6;
	if (strcmp (readout_str, "Magnitude") == 0)            DEP = 8;

	phoebe_debug ("dependent variable:         %d\n", DEP);

	/* Do we want to have a gridded plot? If so, set GRID to 1 or 2:            */
	GRID = 0;
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_fine_gridlines");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) GRID = 2;
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_coarse_gridlines");
	if ( (GTK_TOGGLE_BUTTON (readout_widget)->active) && GRID != 2) GRID = 1;

	phoebe_debug ("grid switch state:          %d\n", GRID);

	/* What kind of plot border would we like? Boxed or axes?                   */
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_draw_box");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) BOX = 0;
	else BOX = 1;

	phoebe_debug ("box or axes switch:         %d\n", BOX);

	/* Do we want to plot experimental data?                                    */
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_experimental_data");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) DATA = 1;
	else DATA = 0;

	phoebe_debug ("plot observed data:     %d\n", DATA);

	/* Is the data switch turned on, but we have no input files?              */
	if ( (chosen_filter == -1) && (DATA == 1) ) {
		warning_window = create_notice_window (
			"PHOEBE Notice",
			"Observational data passband problem",
			"You must assign a passband to observational data in the main",
			"window's Data tab. Until then data plotting will be disabled.",
			gtk_widget_destroy);
		DATA = 0;
		phoebe_debug ("*** passbands are not assigned to observations, turning off data plots.\n");
	}

	/* Do we want data aliasing:                                                */
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_aliasing_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) ALIASING = 1;
	else ALIASING = 0;

	phoebe_debug ("aliasing on:                %d\n", ALIASING);

	/* Do we want to plot residuals:                                            */
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_plot_residuals_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) RESIDUALS = 1;
	else RESIDUALS = 0;

	phoebe_debug ("residuals on:               %d\n", RESIDUALS);

	/* Do we want to remove reddening:                                          */
	readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_reddening_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) REDDENING = 1;
	else REDDENING = 0;

	phoebe_debug ("de-reddening on:            %d\n", REDDENING);

	/* We don't want experimental data to be plotted against individual fluxes: */
	if ( (DEP == 3) || (DEP == 4) ) {
		warning_window = create_notice_window (
			"PHOEBE Notice",
			"Invalid plot request",
			"You have requested to plot observational data of individual",
			"star fluxes, which cannot be done. Omitting data plotting.",
			gtk_widget_destroy);
		DATA = 0;
		phoebe_debug ("*** cannot plot observational data for individual fluxes, turning off data plot.\n");
	}

	/* Do we want to plot synthetic data?                                       */
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_synthetic_lightcurve");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) MODEL = 1;
	else MODEL = 0;

	phoebe_debug ("synthetic data plot:        %d\n", MODEL);

	if (MODEL == 1)
		{
		/* Now we have prepared everything and it is time to write the LCI file:  */
		create_lci_input_file ("phoebe_lc", main, switches, ld, spots, curve, mono);
		phoebe_debug ("LC input file created.\n");

		/* Let's call WD's lc program on the created input file:                */
		i = scan_temporary_directory_for_lci_file_index ("phoebe_lc");
		sprintf (working_str, "%s/lc < %s/phoebe_lc_%03d.lci > %s/phoebe_lc_%03d.lco", PHOEBE_LC_DIR, PHOEBE_TEMP_DIR, i, PHOEBE_TEMP_DIR, i);
		phoebe_debug ("executing WD binary with the following command:\n\t%s\n", working_str);
		system (working_str);

		/* Assign a filename to the current LCO process and read in the calcula-  */
		/* ted synthetic data and binary parameters:                              */
		i = scan_temporary_directory_for_lci_file_index ("phoebe_lc");
		sprintf (working_str, "%s/phoebe_lc_%03d.lco", PHOEBE_TEMP_DIR, i);

		/* Here we deviate from the standard WD scheme; we do not use MPAGE swit- */
		/* ch but rather calculate magnitudes from respective flux values:        */
		if (DEP == 8)
			{
			phoebe_debug ("reading in synthetic data from lco file.\n");
			read_in_synthetic_lc_data (working_str, &synthetic_data, &params, INDEP, 5);
			phoebe_debug ("read-in finished.\n");
			phoebe_debug ("transforming fluxes to magnitudes.\n");
			transform_flux_to_magnitude (&synthetic_data, main.MNORM);
			phoebe_debug ("transformation finished.\n");
			}
		else
			{
			phoebe_debug ("reading in synthetic data from lco file.\n");
			read_in_synthetic_lc_data (working_str, &synthetic_data, &params, INDEP, DEP);
			phoebe_debug ("read-in finished.\n");
			phoebe_debug ("displaying read-in data:\n");
			#ifdef PHOEBE_DEBUG_SUPPORT
				for (i = 0; i < synthetic_data.ptsno; i++)
					phoebe_debug ("%3d:   indep: %10lf dep: %10lf weight: %10lf\n", i+1, synthetic_data.indep[i], synthetic_data.dep[i], synthetic_data.weight[i]);
			#endif
			phoebe_debug ("displaying finished.\n");
			}

		/* If the error occured, synthetic_data will have 0 points:               */
		if (synthetic_data.ptsno == 0) MODEL = 0;

		/* Write out the calculated parameters (radii, surface, ...) to the plot- */
		/* ting window:                                                           */
		phoebe_debug ("updating plot information frame.\n");
		if (MODEL != 0) plot_update_info (1, params);
		}

	if (DATA == 1) {
		/* If we want to plot experimental data, we will first read in the values */
		/* from a file according to indep and dep switches:                       */
		read_in_experimental_lc_data (chosen_filter, &experimental_data, INDEP, DEP);

		/* If an error occured, ptsno value is 0 and we need to abort; notice */
		/* window will be created by the read_in_experimental_lc_data ()      */
		/* function, so no need to do it here.                                */
		if (experimental_data.ptsno == 0) DATA = 0;

		/* Write out the number of points to plotting status window: */
		readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_lc), "plot_lc_chi2_ptsno_value");
		sprintf (working_str, "%d", experimental_data.ptsno);
		gtk_label_set_text (GTK_LABEL (readout_widget), working_str);
	}

	/* Align the data with the desired phase span:                            */
	if (DATA == 1)
		shift_interval (&experimental_data, curve.PHSTRT, curve.PHSTOP);

	/* If we plot both experimental and synthetic data, we can calculate chi2;  */
	/* if we plot residuals, we must prepare them here:                         */
	if ( (DATA == 1) && (MODEL == 1) )
		{
		chi2 = calculate_chi2 (synthetic_data, experimental_data, 1.0, 1);
		sprintf (working_str, "%lf", chi2);
		readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_chi2_weighted_sigma_value");
		gtk_label_set_text (GTK_LABEL (readout_widget), working_str);

		chi2 = calculate_chi2 (synthetic_data, experimental_data, 1.0, 0);
		sprintf (working_str, "%lf", chi2);
		readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_chi2_unweighted_sigma_value");
		gtk_label_set_text (GTK_LABEL (readout_widget), working_str);
		}

	/* Finally, we must call aliasing function in the end, so that chi2 calcu-  */
	/* lation is performed only on non-aliased points:                          */
	if (DATA == 1)
		{
		/* If the phase range of the plot is narrower than [-0.5,0.5], we must    */
		/* crop the experimental data output. If the range is wider, we must ali- */
		/* as some points to the outside regions:                                 */
		if ( (ALIASING == 1) && (switches.JDPHS == 2 /* Phases */) )
			alias_phase_to_interval (&experimental_data, curve.PHSTRT, curve.PHSTOP);

		/* Now for the residuals; after this function, synthetic_data will hold   */
		/* only zeroes (for reference) and experimental_data will hold residuals: */
		if (RESIDUALS == 1 && MODEL == 1)
			calculate_residuals (&synthetic_data, &experimental_data);
		}

	/* Create a plot: */
	if (strcmp (PHOEBE_PLOTTING_PACKAGE, "sm") == 0)
		create_lc_plot_using_sm (device, filename, synthetic_data, experimental_data, INDEP, DEP, GRID, BOX, LC_X_OFFSET, LC_Y_OFFSET, LC_ZOOM_FACTOR, MODEL, DATA);
	if (strcmp (PHOEBE_PLOTTING_PACKAGE, "gnuplot") == 0)
		create_lc_plot_using_gnuplot (device, filename, synthetic_data, experimental_data, INDEP, DEP, GRID, BOX, LC_X_OFFSET, LC_Y_OFFSET, LC_ZOOM_FACTOR, MODEL, DATA);

	/* Put a plot to the screen if device is x11: */
	if (device == x11) {
		readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_image_frame");
		sprintf (working_str, "phoebe_lc_%03d.xpm", scan_temporary_directory_for_lci_file_index ("phoebe_lc"));
		draw_image_to_screen (readout_widget, working_str);
	}

	/* Free all memory that we don't need anymore, but only the ones that were  */
	/* phoebe_malloc()ed:                                                       */
	free_memory_allocated_for_spots (&spots);

	if (MODEL == 1) {
		free (synthetic_data.indep);
		free (synthetic_data.dep);
		free (synthetic_data.weight);
	}
	if (DATA == 1) {
		free (experimental_data.indep);
		free (experimental_data.dep);
		free (experimental_data.weight);
	}

	phoebe_debug ("leaving 'plot_lc_plot ()' function.\n");
	}

void plot_rv_plot (PHOEBE_plot_device device, char *filename)
	{
	int i;

	PHOEBE_data synthetic_rv1_data;
	PHOEBE_data synthetic_rv2_data;
	PHOEBE_data experimental_rv1_data;
	PHOEBE_data experimental_rv2_data;

	/* This variable holds both RVs if DEP reflects it, otherwise NULL:         */
	PHOEBE_data joint_synthetic_data;
	PHOEBE_data joint_experimental_data;

	PHOEBE_main_parameters  main     = read_in_main_parameters ();
	PHOEBE_switches         switches = read_in_switches ();
	PHOEBE_limb_darkening   ld       = read_in_ld_coefficients ();
	PHOEBE_spots            spots;
	PHOEBE_curve_parameters curve    = read_in_curve_parameters ();

	PHOEBE_wl_dependent_parameters mono;
	PHOEBE_calculated_parameters params;

	GtkWidget *readout_widget;
	GtkWidget *warning_window;

	char *readout_str;

	char working_string[255];
	char *working_str = working_string;

	int VERTEXES;

	int chosen_filter;

	int INDEP;   /* This switch determines the independent variable:          */
                 /*   INDEP = 1 .. heliocentric julian date                   */
                 /*   INDEP = 2 .. phase                                      */

	int DEP;     /* This switch determines the dependent variable:            */
                 /*   DEP = 3 .. normalized primary RV curve                  */
                 /*   DEP = 4 .. normalized secondary RV curve                */
                 /*   DEP = 5 .. primary star eclipse proximity corrections   */
                 /*   DEP = 6 .. secondary star eclipse proximity corrections */
                 /*   DEP = 7 .. primary RV curve in km/s                     */
                 /*   DEP = 8 .. secondary RV curve in km/s                   */
                 /*   DEP = 9 .. both RV curves in km/s                       */

	int BOX;     /* This switch determines how does SuperMongo limit plots:   */
                 /*   BOX = 0 .. draw ticked axes (x and y)                   */
                 /*   BOX = 1 .. draw ticked box                              */

	int GRID;    /* This switch determines what kind of gridding is used:     */
                 /*   GRID = 0 .. no gridding                                 */
                 /*   GRID = 1 .. coarse grid                                 */
                 /*   GRID = 2 .. fine grid                                   */

	int DATA;    /* This switch determines whether the user wants to plot ex- */
	             /* perimental data:                                          */
                 /*   DATA = 0 .. do not plot experimental data               */
                 /*   DATA = 1 .. plot experimental data                      */

	int MODEL;   /* This switch determines whether the user wants to plot     */
	             /* synthetic data:                                           */
                 /*   MODEL = 0 .. do not plot synthetic data                 */
                 /*   MODEL = 1 .. plot synthetic data                        */

	int ALIASING;
	             /* This switch determines if the phases are to be aliased to */
                 /* a wider/narrower range or not.                            */
				 /*   ALIASING = 0 .. don't use aliasing, always [-0.5, 0.5]  */
                 /*   ALIASING = 1 .. use aliasing to [PHSTRT, PHSTOP].       */

	int RESIDUALS;
	             /* This switch determines whether the plot should contain    */
                 /* overlapped synthetic and experimental data or should it   */
				 /* calculate residuals and plot them against INDEP:          */
				 /*   RESIDUALS = 0 .. don't calculate/plot residuals         */
				 /*   RESIDUALS = 1 .. calculate/plot residuals               */

	int rvno = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));

	double chi2_rv1 = 0.0;
	double chi2_rv2 = 0.0;
	double chi2_tot = 0.0;

	/* Let's read in the spots:                                                 */
	allocate_memory_for_spots (&spots);
	read_in_spots (&spots);

	/* We want to plot RVs, so we set MPAGE to 2: */
	switches.MPAGE = 2;

	/* The filter name combo box contains either the name of the chosen filter  */
	/* or the "None Specified" entry. If the filter name is defined, we have to */
	/* initialize the wavelength-dependent parameters based on that filter for  */
	/* synthetic RV generation. If not, we assume the default values.           */
	i = 0;
	readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_data_combo_box_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));

	chosen_filter = -1;
	for (i = 0; i < switches.IFVC1 + switches.IFVC2; i++)
		if (strcmp (readout_str, PHOEBE_rv_data[i].filter) == 0)
			chosen_filter = i;
	phoebe_debug ("chosen filter number:       %d\n", chosen_filter);

	/* If the filter is not specified (chosen_filter == -1), we read in the de- */
	/* faults, else we read in filter-dependent parameters:                     */
	if (chosen_filter == -1) {
		phoebe_warning ("No filter selected: assuming default Johnson V (550nm) filter.\n");
		mono.WLA   = 550.0;
		mono.IBAND = 7;
		mono.HLA   = 10.0;
		mono.CLA   = 10.0;
		mono.X1A   = 0.5;
		mono.X2A   = 0.5;
		mono.Y1A   = 0.5;
		mono.Y2A   = 0.5;
		mono.EL3   = 0.0;
		mono.OPSF  = 0.0;
		mono.SIGMA = 0.0;
	}
	else mono = read_in_wl_dependent_parameters (readout_str);

	/* Read out the phase settings from RV Plot Window:                         */
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_vertexes_value");
	VERTEXES = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_phstrt_value");
	curve.PHSTRT = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_phend_value");
	curve.PHSTOP = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	curve.PHIN = (curve.PHSTOP - curve.PHSTRT) / VERTEXES;
	curve.PHSTOP += 1e-6; /* To have the last vertex included */
	curve.HJDST = main.HJD0 + main.PERIOD * curve.PHSTRT;
	curve.HJDSP = main.HJD0 + main.PERIOD * curve.PHSTOP;
	curve.HJDIN = main.PERIOD * curve.PHIN;

	/* Since there is no synthetic RV support for noise, set these to 0:        */
	switches.NOISE = 0;
	switches.SIGMA = 0.0;
	switches.SEED  = 0.0;

	/* What variable the user chooses to be independent (time or phase): */
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_independent_combo_box_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	if (strcmp (readout_str, "Time") == 0)  { INDEP = 1; switches.JDPHS = 1; }
	if (strcmp (readout_str, "Phase") == 0) { INDEP = 2; switches.JDPHS = 2; }

	/* What variable user chooses to be dependent (flux or magnitude): */
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_dependent_combo_box_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	if (strcmp (readout_str, "Primary normalized RV") == 0)   DEP = 3;
	if (strcmp (readout_str, "Secondary normalized RV") == 0) DEP = 4;
	if (strcmp (readout_str, "Primary eclipse-proximity corrections") == 0) DEP = 5;
	if (strcmp (readout_str, "Secondary eclipse-proximity corrections") == 0) DEP = 6;
	if (strcmp (readout_str, "Primary RV in km/s") == 0)   DEP = 7;
	if (strcmp (readout_str, "Secondary RV in km/s") == 0)   DEP = 8;
	if (strcmp (readout_str, "Both RVs in km/s") == 0) DEP = 9;

	if (DEP == 9 && rvno == 0) {
		warning_window = create_notice_window ("PHOEBE Notice", "Observed data plot failure", "You have not defined any RV data curves in the Data tab.", "Please supply the data and try again.", gtk_widget_destroy);
		return;
	}
	if (DEP == 9 && rvno == 1) {
		warning_window = create_notice_window ("PHOEBE Notice", "Observed data plot failure", "You have defined only one RV data curve in the Data tab,", "but you are attempting to plot two curves; aborting.", gtk_widget_destroy);
		return;
	}

	/* Do we want to have a gridded plot? If so, set GRID to 1 or 2:          */
	GRID = 0;
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_fine_gridlines");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) GRID = 2;
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_coarse_gridlines");
	if ( (GTK_TOGGLE_BUTTON (readout_widget)->active) && GRID != 2) GRID = 1;

	/* What kind of plot border would we like? Boxed or axes?                 */
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_draw_box");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) BOX = 0;
	else BOX = 1;

	/* Do we want to plot experimental data?                                    */
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_experimental_data");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) DATA = 1;
	else DATA = 0;

	/* Is the data switch turned on, but we have no input files?                */
	if ( (chosen_filter == -1) && (DATA == 1) )
		{
		warning_window = create_notice_window ("PHOEBE Notice", "Observed data plot failure", "You should supply observed data to PHOEBE in the", "main window's Data tab. Until then observed data cannot be plotted.", gtk_widget_destroy);
		DATA = 0;
		}

	/* Do we want data aliasing:                                                */
	readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_aliasing_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) ALIASING = 1;
	else ALIASING = 0;

	/* Do we want to plot residuals:                                            */
	readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_plot_residuals_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) RESIDUALS = 1;
	else RESIDUALS = 0;

	/* We don't want experimental data plotted with proximity corrections: */
	if ( (DEP == 5) || (DEP == 6) ) DATA = 0;

	/* Do we want to plot synthetic data?                                       */
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_synthetic_lightcurve");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) MODEL = 1;
	else MODEL = 0;

	if (MODEL == 1)
		{
		/* Now we have prepared everything and it is time to write the LCI file:  */
		create_lci_input_file ("phoebe_rv", main, switches, ld, spots, curve, mono);

		/* Let's call WD's lc program on the created input file:                  */
		i = scan_temporary_directory_for_lci_file_index ("phoebe_rv");
		sprintf (working_str, "%s/lc < %s/phoebe_rv_%03d.lci > %s/phoebe_rv_%03d.lco", PHOEBE_LC_DIR, PHOEBE_TEMP_DIR, i, PHOEBE_TEMP_DIR, i);
		system (working_str);

		/* Assign a filename to the current LCO process and read in the calcula-  */
		/* ted synthetic data and binary parameters:                              */
		i = scan_temporary_directory_for_lci_file_index ("phoebe_rv");
		sprintf (working_str, "%s/phoebe_rv_%03d.lco", PHOEBE_TEMP_DIR, i);
		if ( ( DEP == 3 ) || ( DEP == 5 ) || ( DEP == 7 ) )
			{
			read_in_synthetic_rv_data (working_str, &synthetic_rv1_data, &params, INDEP, DEP);
			if (synthetic_rv1_data.ptsno == 0) MODEL = 0;
			}

		if ( ( DEP == 4 ) || ( DEP == 6 ) || ( DEP == 8 ) )
			{
			read_in_synthetic_rv_data (working_str, &synthetic_rv2_data, &params, INDEP, DEP);
			if (synthetic_rv1_data.ptsno == 0) MODEL = 0;
			}
		if   ( DEP == 9 )
			{
			/* This means we want both RV curves plotted on the same plot. We must  */
			/* read the values in separately to be able to properly calculate chi2  */
			/* and residuals. plot_update_info () will return proper values in both */
			/* cases, so it is not to worry.                                        */
			read_in_synthetic_rv_data (working_str, &synthetic_rv1_data, &params, INDEP, 7);
			read_in_synthetic_rv_data (working_str, &synthetic_rv2_data, &params, INDEP, 8);
			if ( (synthetic_rv1_data.ptsno == 0) || (synthetic_rv2_data.ptsno == 0) ) MODEL = 0;
			}

		/* Write out the calculated parameters (radii, surface, ...) to window:   */
		if (MODEL != 0) plot_update_info (2, params);
		}

	if (DATA == 1) {
		if ( ( DEP == 3 ) || ( DEP == 7 ) ) {
			read_in_experimental_rv_data (chosen_filter, &experimental_rv1_data, INDEP, DEP, 1.0);

			/* If an error occured, ptsno value is 0. In that case we don't want    */
			/* any experimental data present in our work, otherwise we expect the   */
			/* program to segfault.                                                 */
			if (experimental_rv1_data.ptsno == 0)
				DATA = 0;
			else
				shift_interval (&experimental_rv1_data, curve.PHSTRT, curve.PHSTOP);
		}

		if ( ( DEP == 4 ) || ( DEP == 8 ) ) {
			read_in_experimental_rv_data (chosen_filter, &experimental_rv2_data, INDEP, DEP, 1.0);

			/* If an error occured, ptsno value is 0. In that case we don't want    */
			/* any experimental data present in our work, otherwise we expect the   */
			/* program to segfault.                                                 */
			if (experimental_rv2_data.ptsno == 0)
				DATA = 0;
			else
				shift_interval (&experimental_rv2_data, curve.PHSTRT, curve.PHSTOP);

			sprintf (working_str, "%d", experimental_rv2_data.ptsno);
		}

		if ( DEP == 9 ) {
			read_in_experimental_rv_data (0, &experimental_rv1_data, INDEP, DEP, 1.0);
			read_in_experimental_rv_data (1, &experimental_rv2_data, INDEP, DEP, 1.0);

			if ( (experimental_rv1_data.ptsno == 0) || (experimental_rv2_data.ptsno == 0) )
				DATA = 0;
			else {
				shift_interval (&experimental_rv1_data, curve.PHSTRT, curve.PHSTOP);
				shift_interval (&experimental_rv2_data, curve.PHSTRT, curve.PHSTOP);
			}

			sprintf (working_str, "%d", experimental_rv1_data.ptsno + experimental_rv2_data.ptsno);
		}

		readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_chi2_ptsno_value");
		gtk_label_set_text (GTK_LABEL (readout_widget), working_str);
	}

	/* If we plot both experimental and synthetic data, we can calculate chi2:  */
	if ( (DATA == 1) && (MODEL == 1) && (DEP != 5) && (DEP != 6 ) )
		{
		/* First let's compute the weighted sigma value: */
		if ( (DEP == 3) || (DEP == 7) || (DEP == 9) )
			chi2_rv1 = calculate_chi2 (synthetic_rv1_data, experimental_rv1_data, 1.0, 1);
		if ( (DEP == 4) || (DEP == 8) || (DEP == 9) )
			chi2_rv2 = calculate_chi2 (synthetic_rv2_data, experimental_rv2_data, 1.0, 1);
		sprintf (working_str, "%lf", chi2_rv1 + chi2_rv2);

		/* If we plot in DEP = 9, we must calculate the combined sigma: */
		if (DEP == 9) {
			chi2_tot = chi2_rv1 * chi2_rv2 / sqrt (chi2_rv1*chi2_rv1 + chi2_rv2*chi2_rv2);
			sprintf (working_str, "%lf", chi2_tot);
		}

		readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_chi2_weighted_sigma_value");
		gtk_label_set_text (GTK_LABEL (readout_widget), working_str);

		/* Next let's compute the unweighted sigma value: */
		chi2_rv1 = chi2_rv2 = 0.0;
		if ( (DEP == 3) || (DEP == 7) || (DEP == 9) )
			chi2_rv1 = calculate_chi2 (synthetic_rv1_data, experimental_rv1_data, 1.0, 0);
		if ( (DEP == 4) || (DEP == 8) || (DEP == 9) )
			chi2_rv2 = calculate_chi2 (synthetic_rv2_data, experimental_rv2_data, 1.0, 0);
		sprintf (working_str, "%lf", chi2_rv1 + chi2_rv2);

		/* If we plot in DEP = 9, we must calculate the combined sigma: */
		if (DEP == 9) {
			chi2_tot = chi2_rv1 * chi2_rv2 / sqrt (chi2_rv1*chi2_rv1 + chi2_rv2*chi2_rv2);
			sprintf (working_str, "%lf", chi2_tot);
		}

		readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_chi2_unweighted_sigma_value");
		gtk_label_set_text (GTK_LABEL (readout_widget), working_str);

		/* If the phase range of the plot is narrower than [-0.5,0.5], we must      */
		/* crop the experimental data output. If the range is wider, we must ali-   */
		/* as some points to the outside regions:                                   */
		if (DATA == 1) {
			if ( ( DEP == 3 ) || ( DEP == 7 ) ) {
				if ( (ALIASING == 1) && (switches.JDPHS == 2 /* Phases */) )
					alias_phase_to_interval (&experimental_rv1_data, curve.PHSTRT, curve.PHSTOP);
			}
			if ( ( DEP == 4 ) || ( DEP == 8 ) ) {
				if ( (ALIASING == 1) && (switches.JDPHS == 2 /* Phases */) )
					alias_phase_to_interval (&experimental_rv2_data, curve.PHSTRT, curve.PHSTOP);
			}
			if ( DEP == 9 ) {
				if ( (ALIASING == 1) && (switches.JDPHS == 2) ) {
					alias_phase_to_interval (&experimental_rv1_data, curve.PHSTRT, curve.PHSTOP);
					alias_phase_to_interval (&experimental_rv2_data, curve.PHSTRT, curve.PHSTOP);
				}
			}
		}

		/* Now for the residuals; after this function, synthetic_data will hold   */
		/* only zeroes (for reference) and experimental_data will hold residuals: */
		if ( (RESIDUALS == 1) && ( (DEP == 3) || (DEP == 7) || (DEP == 9) ) )
			calculate_residuals (&synthetic_rv1_data, &experimental_rv1_data);
		if ( (RESIDUALS == 1) && ( (DEP == 4) || (DEP == 8) || (DEP == 9) ) )
			calculate_residuals (&synthetic_rv2_data, &experimental_rv2_data);
	}

	/* Now we have everything calculated for DEP = 9 plot, so we may join the   */
	/* data to a single array:                                                  */
	if ( ( MODEL == 1 ) && ( DEP == 9 ) )
		{
		joint_synthetic_data.ptsno = synthetic_rv1_data.ptsno + synthetic_rv2_data.ptsno;
		joint_synthetic_data.indep = NULL; joint_synthetic_data.dep = NULL; joint_synthetic_data.weight = NULL;

		allocate_memory_for_data (&joint_synthetic_data);

		for (i = 0; i < synthetic_rv1_data.ptsno; i++)
			{
			joint_synthetic_data.indep[i]  = synthetic_rv1_data.indep[i];
			joint_synthetic_data.dep[i]    = synthetic_rv1_data.dep[i];
			joint_synthetic_data.weight[i] = synthetic_rv1_data.weight[i];
			}
		for (i = synthetic_rv1_data.ptsno; i < synthetic_rv1_data.ptsno + synthetic_rv2_data.ptsno; i++)
			{
			joint_synthetic_data.indep[i]  = synthetic_rv2_data.indep[i-synthetic_rv1_data.ptsno];
			joint_synthetic_data.dep[i]    = synthetic_rv2_data.dep[i-synthetic_rv1_data.ptsno];
			joint_synthetic_data.weight[i] = synthetic_rv2_data.weight[i-synthetic_rv1_data.ptsno];
			}
		}

	if ( ( DATA == 1 ) && ( DEP == 9 ) )
			{
			joint_experimental_data.ptsno = experimental_rv1_data.ptsno + experimental_rv2_data.ptsno;
			joint_experimental_data.indep = NULL; joint_experimental_data.dep = NULL; joint_experimental_data.weight = NULL;

			allocate_memory_for_data (&joint_experimental_data);
			
			for (i = 0; i < experimental_rv1_data.ptsno; i++)
				{
				joint_experimental_data.indep[i]  = experimental_rv1_data.indep[i];
				joint_experimental_data.dep[i]    = experimental_rv1_data.dep[i];
				joint_experimental_data.weight[i] = experimental_rv1_data.weight[i];
				}
			for (i = experimental_rv1_data.ptsno; i < experimental_rv1_data.ptsno + experimental_rv2_data.ptsno; i++)
				{
				joint_experimental_data.indep[i]  = experimental_rv2_data.indep[i-experimental_rv1_data.ptsno];
				joint_experimental_data.dep[i]    = experimental_rv2_data.dep[i-experimental_rv1_data.ptsno];
				joint_experimental_data.weight[i] = experimental_rv2_data.weight[i-experimental_rv1_data.ptsno];
				}
			}

	/* Create a plot: */
	if ( ( DEP == 3 ) || ( DEP == 5 ) || ( DEP == 7 ) )
		if (strcmp (PHOEBE_PLOTTING_PACKAGE, "sm") == 0)
			create_rv_plot_using_sm (device, filename, synthetic_rv1_data, experimental_rv1_data, INDEP, DEP, GRID, BOX, RV_X_OFFSET, RV_Y_OFFSET, RV_ZOOM_FACTOR, MODEL, DATA);
		else if (strcmp (PHOEBE_PLOTTING_PACKAGE, "gnuplot") == 0)
			create_rv_plot_using_gnuplot (device, filename, synthetic_rv1_data, experimental_rv1_data, INDEP, DEP, GRID, BOX, RV_X_OFFSET, RV_Y_OFFSET, RV_ZOOM_FACTOR, MODEL, DATA);
	if ( ( DEP == 4 ) || ( DEP == 6 ) || ( DEP == 8 ) )
		if (strcmp (PHOEBE_PLOTTING_PACKAGE, "sm") == 0)
			create_rv_plot_using_sm (device, filename, synthetic_rv2_data, experimental_rv2_data, INDEP, DEP, GRID, BOX, RV_X_OFFSET, RV_Y_OFFSET, RV_ZOOM_FACTOR, MODEL, DATA);
		else if (strcmp (PHOEBE_PLOTTING_PACKAGE, "gnuplot") == 0)
			create_rv_plot_using_gnuplot (device, filename, synthetic_rv2_data, experimental_rv2_data, INDEP, DEP, GRID, BOX, RV_X_OFFSET, RV_Y_OFFSET, RV_ZOOM_FACTOR, MODEL, DATA);
	if ( DEP == 9 )
		if (strcmp (PHOEBE_PLOTTING_PACKAGE, "sm") == 0)
			create_rv_plot_using_sm (device, filename, joint_synthetic_data, joint_experimental_data, INDEP, DEP, GRID, BOX, RV_X_OFFSET, RV_Y_OFFSET, RV_ZOOM_FACTOR, MODEL, DATA);
		else if (strcmp (PHOEBE_PLOTTING_PACKAGE, "gnuplot") == 0)
			create_rv_plot_using_gnuplot (device, filename, joint_synthetic_data, joint_experimental_data, INDEP, DEP, GRID, BOX, RV_X_OFFSET, RV_Y_OFFSET, RV_ZOOM_FACTOR, MODEL, DATA);

	/* Put a plot to the screen, but only if device is x11: */
	if (device == x11)
		{
		readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_image_frame");
		sprintf (working_str, "phoebe_rv_%03d.xpm", scan_temporary_directory_for_lci_file_index ("phoebe_rv"));
		draw_image_to_screen (readout_widget, working_str);
		}

	/* Free all memory that we don't need anymore, but only the ones that were  */
	/* phoebe_malloc()ed:                                                       */
	free_memory_allocated_for_spots (&spots);

	if ( (DEP == 3) || (DEP == 5) || (DEP == 7) )
		{
		if ( MODEL == 1 )
			{
			free (synthetic_rv1_data.indep);
			free (synthetic_rv1_data.dep);
			free (synthetic_rv1_data.weight);
			}
		if ( DATA == 1 )
			{
			free (experimental_rv1_data.indep);
			free (experimental_rv1_data.dep);
			free (experimental_rv1_data.weight);
			}
		}
	if ( (DEP == 4) || (DEP == 6) || (DEP == 8) )
		{
		if ( MODEL == 1 )
			{
			free (synthetic_rv2_data.indep);
			free (synthetic_rv2_data.dep);
			free (synthetic_rv2_data.weight);
			if (DEP == 9)
				{
				free (joint_synthetic_data.indep);
				free (joint_synthetic_data.dep);
				free (joint_synthetic_data.weight);
				}
			}
		if ( DATA == 1 )
			{
			free (experimental_rv2_data.indep);
			free (experimental_rv2_data.dep);
			free (experimental_rv2_data.weight);
			if (DEP == 9)
				{
				free (joint_experimental_data.indep);
				free (joint_experimental_data.dep);
				free (joint_experimental_data.weight);
				}
			}
		}
	}

void plot_chi2_plot (PHOEBE_plot_device device, char *filename)
	{
	/* This function reads in all necessary widget states that influence Chi2   */
	/* plots. Then it calls the actual plotting routine to put the plot to the  */
	/* output device.                                                           */

	PHOEBE_main_parameters  main        = read_in_main_parameters ();
	PHOEBE_switches         switches    = read_in_switches ();
	PHOEBE_limb_darkening   ld          = read_in_ld_coefficients ();
	PHOEBE_spots            spots;
	PHOEBE_curve_parameters curve       = read_in_curve_parameters ();
	PHOEBE_wl_dependent_parameters mono;
	PHOEBE_calculated_parameters dummy;

	PHOEBE_data synthetic_data;
	PHOEBE_data experimental_data;

	PHOEBE_3D_data chi2_data;

	GtkWidget *progress_bar = lookup_widget (PHOEBE, "fitting_chi2_progress_bar");
	GtkWidget *new_image;
	GtkWidget *readout_widget;

	double x_param_min, x_param_max;
	double y_param_min, y_param_max;

	int plot_type;

	double EPSILON = 1e-3;

	double x, y;
	double *par1, *par2;

	char *readout_str;
	char working_string[255];
	char *working_str = working_string;

	double percentage = 0.0;
	double chi2;

	int countx, county;

	int i;
	int curve_no;

	allocate_memory_for_spots (&spots);
	read_in_spots (&spots);

	/* Pepare MPAGE and JDPHS for correlation use:                              */
	switches.MPAGE = 1;
	switches.JDPHS = 2;
	
	readout_widget = lookup_widget (PHOEBE, "fitting_chi2_indep");
	readout_str = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (readout_widget)->entry));

	if (strcmp (readout_str, "Orbital Semi-Major Axis") == 0)                par1 = &main.SMA;
	if (strcmp (readout_str, "Orbital Eccentricity") == 0)                   par1 = &main.E;
	if (strcmp (readout_str, "Argument of Periastron") == 0)                 par1 = &main.PERR0;
	if (strcmp (readout_str, "Primary Star Synchronicity Parameter") == 0)   par1 = &main.F1;
	if (strcmp (readout_str, "Secondary Star Synchronicity Parameter") == 0) par1 = &main.F2;
	if (strcmp (readout_str, "Phase Shift") == 0)                            par1 = &main.PSHIFT;
	if (strcmp (readout_str, "Systemic Radial Velocity") == 0)               par1 = &main.VGA;
	if (strcmp (readout_str, "Orbital Inclination") == 0)                    par1 = &main.XINCL;
	if (strcmp (readout_str, "Primary Star Gravity Brightening") == 0)       par1 = &main.GR1;
	if (strcmp (readout_str, "Secondary Star Gravity Brightening") == 0)     par1 = &main.GR2;
	if (strcmp (readout_str, "Primary Star Temperature") == 0)               par1 = &main.TAVH;
	if (strcmp (readout_str, "Secondary Star Temperature") == 0)             par1 = &main.TAVC;
	if (strcmp (readout_str, "Primary Star Bolometric Albedo") == 0)         par1 = &main.ALB1;
	if (strcmp (readout_str, "Secondary Star Bolometric Albedo") == 0)       par1 = &main.ALB2;
	if (strcmp (readout_str, "Primary Star Surface Potential") == 0)         par1 = &main.PHSV;
	if (strcmp (readout_str, "Secondary Star Surface Potential") == 0)       par1 = &main.PCSV;
	if (strcmp (readout_str, "Mass Ratio") == 0)                             par1 = &main.RM;
	if (strcmp (readout_str, "HJD0 Reference Frame") == 0)                   par1 = &main.HJD0;
	if (strcmp (readout_str, "Orbital Period") == 0)                         par1 = &main.PERIOD;
	if (strcmp (readout_str, "Period Time Derivative") == 0)                 par1 = &main.DPDT;
	if (strcmp (readout_str, "HJD0 Time Derivative") == 0)                   par1 = &main.DPERDT;

	readout_widget = lookup_widget (PHOEBE, "fitting_chi2_dep");
	readout_str = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (readout_widget)->entry));

	if (strcmp (readout_str, "Orbital Semi-Major Axis") == 0)                par2 = &main.SMA;
	if (strcmp (readout_str, "Orbital Eccentricity") == 0)                   par2 = &main.E;
	if (strcmp (readout_str, "Argument of Periastron") == 0)                 par2 = &main.PERR0;
	if (strcmp (readout_str, "Primary Star Synchronicity Parameter") == 0)   par2 = &main.F1;
	if (strcmp (readout_str, "Secondary Star Synchronicity Parameter") == 0) par2 = &main.F2;
	if (strcmp (readout_str, "Phase Shift") == 0)                            par2 = &main.PSHIFT;
	if (strcmp (readout_str, "Systemic Radial Velocity") == 0)               par2 = &main.VGA;
	if (strcmp (readout_str, "Orbital Inclination") == 0)                    par2 = &main.XINCL;
	if (strcmp (readout_str, "Primary Star Gravity Brightening") == 0)       par2 = &main.GR1;
	if (strcmp (readout_str, "Secondary Star Gravity Brightening") == 0)     par2 = &main.GR2;
	if (strcmp (readout_str, "Primary Star Temperature") == 0)               par2 = &main.TAVH;
	if (strcmp (readout_str, "Secondary Star Temperature") == 0)             par2 = &main.TAVC;
	if (strcmp (readout_str, "Primary Star Bolometric Albedo") == 0)         par2 = &main.ALB1;
	if (strcmp (readout_str, "Secondary Star Bolometric Albedo") == 0)       par2 = &main.ALB2;
	if (strcmp (readout_str, "Primary Star Surface Potential") == 0)         par2 = &main.PHSV;
	if (strcmp (readout_str, "Secondary Star Surface Potential") == 0)       par2 = &main.PCSV;
	if (strcmp (readout_str, "Mass Ratio") == 0)                             par2 = &main.RM;
	if (strcmp (readout_str, "HJD0 Reference Frame") == 0)                   par2 = &main.HJD0;
	if (strcmp (readout_str, "Orbital Period") == 0)                         par2 = &main.PERIOD;
	if (strcmp (readout_str, "Period Time Derivative") == 0)                 par2 = &main.DPDT;
	if (strcmp (readout_str, "HJD0 Time Derivative") == 0)                   par2 = &main.DPERDT;

	readout_widget = lookup_widget (PHOEBE, "fitting_chi2_indep_min_value");
	x_param_min = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "fitting_chi2_indep_max_value");
	x_param_max = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "fitting_chi2_dep_min_value");
	y_param_min = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "fitting_chi2_dep_max_value");
	y_param_max = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "fitting_chi2_x_steps_value");
	chi2_data.ptsx = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE, "fitting_chi2_y_steps_value");
	chi2_data.ptsy = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));
	chi2_data.ptsz = chi2_data.ptsx * chi2_data.ptsy;

	chi2_data.x = phoebe_malloc (chi2_data.ptsx * sizeof (double));
	chi2_data.y = phoebe_malloc (chi2_data.ptsy * sizeof (double));
	chi2_data.z = phoebe_malloc (chi2_data.ptsz * sizeof (double));

	readout_widget = lookup_widget (PHOEBE, "fitting_chi2_2d_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) plot_type = 1;
	else plot_type = 2;

	readout_widget = lookup_widget (PHOEBE, "fitting_chi2_filter_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	if (strcmp (readout_str, "Filter: None Specified") == 0)
		{
		readout_widget = create_notice_window ("PHOEBE Notice", "PHOEBE Notice: Filter name invalid", "You have not assigned a proper filter to the calculation routine.", "Please make sure you defined filters in Data tab.", gtk_widget_destroy);
		return;
		}
	mono = read_in_wl_dependent_parameters (readout_str);
	curve_no = 0; while (strcmp (readout_str, PHOEBE_lc_data[curve_no].filter) != 0) curve_no++;
	read_in_experimental_lc_data (curve_no, &experimental_data, 2, 5);

	gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE, "fitting_chi2_calculate_button")), FALSE);

	countx = 0;
	for (x = x_param_min; x <= x_param_max + EPSILON; x += (x_param_max - x_param_min) / (chi2_data.ptsx - 1))
		{
		chi2_data.x[countx] = x;
		countx++;
		}
	county = 0;
	for (y = y_param_min; y <= y_param_max + EPSILON; y += (y_param_max - y_param_min) / (chi2_data.ptsy - 1))
		{
		chi2_data.y[county] = y;
		county++;
		}

	/* We have prepared everything, now we go into the calculation loop:        */
	countx = county = 0;
	for (x = x_param_min; x <= x_param_max + EPSILON; x += (x_param_max - x_param_min) / (chi2_data.ptsx - 1))
		{
		for (y = y_param_min; y <= y_param_max + EPSILON; y += (y_param_max - y_param_min) / (chi2_data.ptsy - 1))
			{
			/* Change the values of the two parameters that par1 and par2 point to: */
			*par1 = x;
			*par2 = y;

			/* Create a LCI input file and call lc program on it:                   */
			create_lci_input_file ("phoebe_lc", main, switches, ld, spots, curve, mono);

			/* Prepare a system call string and call it:                            */
			i = scan_temporary_directory_for_lci_file_index ("phoebe_lc");
			sprintf (working_str, "%s/lc < %s/phoebe_lc_%03d.lci > %s/phoebe_lc_%03d.lco", PHOEBE_LC_DIR, PHOEBE_TEMP_DIR, i, PHOEBE_TEMP_DIR, i);
			system (working_str);

			/* Get synthetic points from LCO file:                                  */
			sprintf (working_str, "%s/phoebe_lc_%03d.lco", PHOEBE_TEMP_DIR, i);
			read_in_synthetic_lc_data (working_str, &synthetic_data, &dummy, 2, 5);

			/* Calculate chi2 and write it to temporary SuperMongo file:            */
			chi2 = calculate_chi2 (synthetic_data, experimental_data, mono.SIGMA, 1.0);
			chi2_data.z[countx*chi2_data.ptsy+county] = chi2;
/*
			printf ("cx = %d, cy = %d, idx = %d, chi2 = %lf\n", countx, county, countx*chi2_data.ptsy+county, chi2);
*/
			/* Free memory for the next iteration:                                  */
			free (synthetic_data.indep);
			free (synthetic_data.dep);
			free (synthetic_data.weight);

			/* Be sure that this calculation doesn't stop PHOEBE from responding:   */
			while (gtk_events_pending()) gtk_main_iteration ();

			/* Increase the progress meter: */
			percentage += 1.0 / chi2_data.ptsx / chi2_data.ptsy;
			gtk_progress_bar_update (GTK_PROGRESS_BAR (progress_bar), percentage);
			
			county++;
			}
		countx++; county = 0;
		}

	/* We're out of the loop, so let's turn the Calculate button back on:       */
	gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE, "fitting_chi2_calculate_button")), TRUE);

	/* The chi2 table is ready, so we may free exp_data memory:                 */
	free (experimental_data.indep);
	free (experimental_data.dep);
	free (experimental_data.weight);

	/* Create SM script for chi2 plot and call SuperMongo:                      */
	if (strcmp (PHOEBE_PLOTTING_PACKAGE, "sm") == 0)
		create_chi2_plot_using_sm (device, filename, chi2_data);
	if (strcmp (PHOEBE_PLOTTING_PACKAGE, "gnuplot") == 0)
		create_chi2_plot_using_gnuplot (device, filename, chi2_data);

	/* Free the 3D container:                                                   */
	free (chi2_data.x); free (chi2_data.y); free (chi2_data.z);

	if (device == x11)
		{
		/* Erase the old image:                                                   */
		readout_widget = lookup_widget (PHOEBE, "fitting_chi2_image_frame");
		gtk_widget_destroy (GTK_BIN (readout_widget)->child);

		/* Create a new image on the screen:                                      */
		readout_widget = lookup_widget (PHOEBE, "fitting_chi2_image_frame");
		new_image = create_pixmap (PHOEBE, "phoebe_c2.xpm");
		gtk_container_add (GTK_CONTAINER (readout_widget), new_image);
		gtk_widget_show (new_image);
		}

	free_memory_allocated_for_spots (&spots);

	/* That's it, folks; we go back to main...                                  */
	return;
	}

void plot_3d_image_plot (PHOEBE_plot_device device, char *filename)
	{
	PHOEBE_main_parameters   main      = read_in_main_parameters ();
	PHOEBE_switches          switches  = read_in_switches ();
	PHOEBE_limb_darkening    ld        = read_in_ld_coefficients ();
	PHOEBE_spots             spots;
	PHOEBE_curve_parameters  curve     = read_in_curve_parameters ();

	PHOEBE_wl_dependent_parameters mono;

	GtkWidget *readout_widget;

	PHOEBE_data image_data;

	int i;

	char working_string[255];
	char *working_str = working_string;

	allocate_memory_for_spots (&spots);
	read_in_spots (&spots);

	/* We want to plot 3D images, so we set MPAGE to 5: */
	switches.MPAGE = 5;
	switches.JDPHS = 2;

	/* Wavelength-dependent parameters play no role, but have to be supplied:   */
	mono.WLA   = 500.0; mono.HLA   = 10.0;  mono.CLA   = 10.0;
	mono.X1A   = 0.5;   mono.X2A   = 0.5;   mono.Y1A   = 0.5;
	mono.Y2A   = 0.5;   mono.EL3   = 0.0;   mono.OPSF  = 0.0;
	mono.SIGMA = 0.0;   mono.IBAND = 7;

	/* Next, set the phase range only to one value: the desired plot phase:     */
	readout_widget = lookup_widget (PHOEBE, "luminosities_star_image_phase_value");
	curve.PHSTRT = curve.PHSTOP = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	curve.PHIN = 1.0; curve.HJDST = curve.HJDSP = curve.HJDIN = 0.0;

	/* Create an input file and call WD to calculate star shape:                */
	create_lci_input_file ("phoebe_3d", main, switches, ld, spots, curve, mono);
	i = scan_temporary_directory_for_lci_file_index ("phoebe_3d");
	sprintf (working_str, "%s/lc < %s/phoebe_3d_%03d.lci > %s/phoebe_3d_%03d.lco", PHOEBE_LC_DIR, PHOEBE_TEMP_DIR, i, PHOEBE_TEMP_DIR, i);
	system (working_str);

	/* Get the output of WD into image_data (allocated within the function):    */
	sprintf (working_str, "%s/phoebe_3d_%03d.lco", PHOEBE_TEMP_DIR, i);
	read_in_3d_image_data (working_str, &image_data);

	/* Finally, create a plot and put it to screen:                             */
	if (strcmp (PHOEBE_PLOTTING_PACKAGE, "sm") == 0)
		create_3d_image_plot_using_sm (device, filename, image_data);
	if (strcmp (PHOEBE_PLOTTING_PACKAGE, "gnuplot") == 0)
		create_3d_image_plot_using_gnuplot (device, filename, image_data);
	
	if (device == x11)
		{
		readout_widget = lookup_widget (PHOEBE, "luminosities_star_image_image_frame");
		sprintf (working_str, "phoebe_3d_%03d.xpm", scan_temporary_directory_for_lci_file_index ("phoebe_3d"));
		draw_image_to_screen (readout_widget, working_str);
		}

	free_memory_allocated_for_spots (&spots);

	free (image_data.indep);
	free (image_data.dep);
	free (image_data.weight);
	}

void plot_lc_zoom_in ()
	{
	GtkWidget *zoom_step = lookup_widget (PHOEBE_plot_lc, "plot_lc_zoom_step_entry");
	GtkWidget *dummy = gtk_button_new ();

	char *readout_str;

	int LC_ZOOM_INC;

	readout_str = gtk_entry_get_text (GTK_ENTRY (zoom_step));
	sscanf (readout_str, "%d", &LC_ZOOM_INC);

	LC_ZOOM_FACTOR -= (double) LC_ZOOM_INC / 100.0;

	on_plot_lc_plot_button_clicked (GTK_BUTTON (dummy), NULL);
	}

void plot_lc_zoom_out ()
	{
	GtkWidget *zoom_step = lookup_widget (GTK_WIDGET (PHOEBE_plot_lc), "plot_lc_zoom_step_entry");
	GtkWidget *dummy = gtk_button_new ();

	char *readout_str;

	int LC_ZOOM_INC;

	readout_str = gtk_entry_get_text (GTK_ENTRY (zoom_step));
	sscanf (readout_str, "%d", &LC_ZOOM_INC);

	LC_ZOOM_FACTOR += (double) LC_ZOOM_INC / 100.0;

	on_plot_lc_plot_button_clicked (GTK_BUTTON (dummy), NULL);
	}

void plot_lc_shift_left ()
	{
	GtkWidget *offset_step = lookup_widget (GTK_WIDGET (PHOEBE_plot_lc), "plot_lc_offset_step_entry");
	GtkWidget *dummy = gtk_button_new ();

	char *readout_str;

	int LC_X_INC;

	readout_str = gtk_entry_get_text (GTK_ENTRY (offset_step));
	sscanf (readout_str, "%d", &LC_X_INC);

	LC_X_OFFSET -= (double) LC_X_INC / 100.0;

	on_plot_lc_plot_button_clicked (GTK_BUTTON (dummy), NULL);
	}

void plot_lc_shift_right ()
	{
	GtkWidget *offset_step = lookup_widget (GTK_WIDGET (PHOEBE_plot_lc), "plot_lc_offset_step_entry");
	GtkWidget *dummy = gtk_button_new ();

	char *readout_str;

	int LC_X_INC;

	readout_str = gtk_entry_get_text (GTK_ENTRY (offset_step));
	sscanf (readout_str, "%d", &LC_X_INC);

	LC_X_OFFSET += (double) LC_X_INC / 100.0;

	on_plot_lc_plot_button_clicked (GTK_BUTTON (dummy), NULL);
	}

void plot_lc_shift_up ()
	{
	GtkWidget *offset_step = lookup_widget (GTK_WIDGET (PHOEBE_plot_lc), "plot_lc_offset_step_entry");
	GtkWidget *dummy = gtk_button_new ();

	char *readout_str;

	int LC_Y_INC;

	readout_str = gtk_entry_get_text (GTK_ENTRY (offset_step));
	sscanf (readout_str, "%d", &LC_Y_INC);

	LC_Y_OFFSET -= (double) LC_Y_INC / 100.0;

	on_plot_lc_plot_button_clicked (GTK_BUTTON (dummy), NULL);
	}

void plot_lc_shift_down ()
	{
	GtkWidget *offset_step = lookup_widget (GTK_WIDGET (PHOEBE_plot_lc), "plot_lc_offset_step_entry");
	GtkWidget *dummy = gtk_button_new ();

	char *readout_str;

	int LC_Y_INC;

	readout_str = gtk_entry_get_text (GTK_ENTRY (offset_step));
	sscanf (readout_str, "%d", &LC_Y_INC);

	LC_Y_OFFSET += (double) LC_Y_INC / 100.0;

	on_plot_lc_plot_button_clicked (GTK_BUTTON (dummy), NULL);
	}

void plot_update_info (int DESTINATION, PHOEBE_calculated_parameters params)
	{
	GtkWidget *readout_widget;
	
	char working_string[255];
	char *working_str = working_string;

	int i;
	
	const char *lc_keywords[] =
		{
		"plot_lc_info_mass_p_label",
		"plot_lc_info_mass_s_label",
		"plot_lc_info_radius_p_label",
		"plot_lc_info_radius_s_label",
		"plot_lc_info_lum_p_label",
		"plot_lc_info_lum_s_label",
		"plot_lc_info_mbol_p_label",
		"plot_lc_info_mbol_s_label",
		"plot_lc_info_logg_p_label",
		"plot_lc_info_logg_s_label",
		"plot_lc_info_psb_p_label",
		"plot_lc_info_psb_s_label",
		"plot_lc_info_surface_p_label",
		"plot_lc_info_surface_s_label",
		"plot_lc_info_rpole_p_label",
		"plot_lc_info_rpole_s_label",
		"plot_lc_info_rpoint_p_label",
		"plot_lc_info_rpoint_s_label",
		"plot_lc_info_rside_p_label",
		"plot_lc_info_rside_s_label",
		"plot_lc_info_rback_p_label",
		"plot_lc_info_rback_s_label"
		};

	const char *rv_keywords[] =
		{
		"plot_rv_info_mass_p_label",
		"plot_rv_info_mass_s_label",
		"plot_rv_info_radius_p_label",
		"plot_rv_info_radius_s_label",
		"plot_rv_info_lum_p_label",
		"plot_rv_info_lum_s_label",
		"plot_rv_info_mbol_p_label",
		"plot_rv_info_mbol_s_label",
		"plot_rv_info_logg_p_label",
		"plot_rv_info_logg_s_label",
		"plot_rv_info_psb_p_label",
		"plot_rv_info_psb_s_label",
		"plot_rv_info_surface_p_label",
		"plot_rv_info_surface_s_label",
		"plot_rv_info_rpole_p_label",
		"plot_rv_info_rpole_s_label",
		"plot_rv_info_rpoint_p_label",
		"plot_rv_info_rpoint_s_label",
		"plot_rv_info_rside_p_label",
		"plot_rv_info_rside_s_label",
		"plot_rv_info_rback_p_label",
		"plot_rv_info_rback_s_label"
		};

	double values[22] =
		{
		params.mass_p,
		params.mass_s,
		params.radius_p,
		params.radius_s,
		params.lum_p,
		params.lum_s,
		params.mbol_p,
		params.mbol_s,
		params.logg_p,
		params.logg_s,
		params.psb_p,
		params.psb_s,
		params.surface_p,
		params.surface_s,
		params.rpole_p,
		params.rpole_s,
		params.rpoint_p,
		params.rpoint_s,
		params.rside_p,
		params.rside_s,
		params.rback_p,
		params.rback_s
		};

	for (i = 0; i < 22; i++)
		{
		if (DESTINATION == 1)
			readout_widget = lookup_widget (PHOEBE_plot_lc, lc_keywords[i]);
		if (DESTINATION == 2)
			readout_widget = lookup_widget (PHOEBE_plot_rv, rv_keywords[i]);

		sprintf (working_str, "%.3lf", values[i]);
		if (i > 13 && values[i] <= 0.0)
			sprintf (working_str, "n/a");

		gtk_label_set_text (GTK_LABEL (readout_widget), working_str);
		}

	/* If the values of log g from the model should be coupled to the main win- */
	/* dow values, update them:                                                 */
	if (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "luminosities_logg_from_model_switch"))->active == TRUE)
		{
		readout_widget = lookup_widget (PHOEBE, "component_logg1_value");
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), params.logg_p);
		readout_widget = lookup_widget (PHOEBE, "component_logg2_value");
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), params.logg_s);
		}
	}

void plot_rv_shift_up ()
	{
	GtkWidget *offset_step = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_offset_step_entry");
	GtkWidget *dummy = gtk_button_new ();

	char *readout_str;

	int RV_Y_INC;

	readout_str = gtk_entry_get_text (GTK_ENTRY (offset_step));
	sscanf (readout_str, "%d", &RV_Y_INC);

	RV_Y_OFFSET -= (double) RV_Y_INC / 100.0;

	on_plot_rv_plot_button_clicked (GTK_BUTTON (dummy), NULL);
	}

void plot_rv_shift_down ()
	{
	GtkWidget *offset_step = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_offset_step_entry");
	GtkWidget *dummy = gtk_button_new ();

	char *readout_str;

	int RV_Y_INC;

	readout_str = gtk_entry_get_text (GTK_ENTRY (offset_step));
	sscanf (readout_str, "%d", &RV_Y_INC);

	RV_Y_OFFSET += (double) RV_Y_INC / 100.0;

	on_plot_rv_plot_button_clicked (GTK_BUTTON (dummy), NULL);
	}

void plot_rv_shift_left ()
	{
	GtkWidget *offset_step = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_offset_step_entry");
	GtkWidget *dummy = gtk_button_new ();

	char *readout_str;

	int RV_X_INC;

	readout_str = gtk_entry_get_text (GTK_ENTRY (offset_step));
	sscanf (readout_str, "%d", &RV_X_INC);

	RV_X_OFFSET -= (double) RV_X_INC / 100.0;

	on_plot_rv_plot_button_clicked (GTK_BUTTON (dummy), NULL);
	}

void plot_rv_shift_right ()
	{
	GtkWidget *offset_step = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_offset_step_entry");
	GtkWidget *dummy = gtk_button_new ();

	char *readout_str;

	int RV_X_INC;

	readout_str = gtk_entry_get_text (GTK_ENTRY (offset_step));
	sscanf (readout_str, "%d", &RV_X_INC);

	RV_X_OFFSET += (double) RV_X_INC / 100.0;

	on_plot_rv_plot_button_clicked (GTK_BUTTON (dummy), NULL);
	}
	
void plot_rv_zoom_in ()
	{
	GtkWidget *zoom_step = lookup_widget (PHOEBE_plot_rv, "plot_rv_zoom_step_entry");
	GtkWidget *dummy = gtk_button_new ();

	char *readout_str;

	int RV_ZOOM_INC;

	readout_str = gtk_entry_get_text (GTK_ENTRY (zoom_step));
	sscanf (readout_str, "%d", &RV_ZOOM_INC);

	RV_ZOOM_FACTOR -= (double) RV_ZOOM_INC / 100.0;

	on_plot_rv_plot_button_clicked (GTK_BUTTON (dummy), NULL);
	}

void plot_rv_zoom_out ()
	{
	GtkWidget *zoom_step = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_zoom_step_entry");
	GtkWidget *dummy = gtk_button_new ();

	char *readout_str;

	int RV_ZOOM_INC;

	readout_str = gtk_entry_get_text (GTK_ENTRY (zoom_step));
	sscanf (readout_str, "%d", &RV_ZOOM_INC);

	RV_ZOOM_FACTOR += (double) RV_ZOOM_INC / 100.0;

	on_plot_rv_plot_button_clicked (GTK_BUTTON (dummy), NULL);
	}

int draw_image_to_screen (GtkWidget *frame, char *image_name)
	{
	GtkWidget *new_image;

	gtk_widget_destroy (GTK_BIN (frame)->child);
	new_image = create_pixmap (frame, image_name);
	gtk_container_add (GTK_CONTAINER (frame), new_image);
	gtk_widget_show (new_image);
	}
