#include <stdio.h>
#include <string.h>

#include <gtk/gtk.h>

#include "phoebe_binning.h"
#include "phoebe_calculations.h"
#include "phoebe_error_handling.h"
#include "phoebe_global.h"
#include "phoebe_gui_accessories.h"
#include "phoebe_gui_support.h"
#include "phoebe_transformations.h"

int allocate_memory_for_data_record (PHOEBE_data_record **data, int records_no)
{
	/*
	 * This function allocates memory to PHOEBE_data_record structure passed to
	 * this routine as a pointer &var_name. It allocates memory for records_no
	 * entries and checks for errors. The return integer (error handler) is al-
	 * ways 0 because phoebe_realloc stops the execution in case of failure.
	 */

	if (records_no == 0) {
		free (*data);
		*data = NULL;
	}
	else *data = phoebe_realloc (*data, records_no * sizeof (**data));

	return 0;
}

int allocate_memory_for_data (PHOEBE_data *data)
{
	/*
	 * This function allocates memory to all three entries of the PHOEBE_data
	 * structure: indep, dep and weight. It reads the number of points from the
	 * structure itself, data->ptsno, so be sure you initialize it prior to
	 * calling this function.
	 */

	if (data->ptsno == 0) {
		data->indep  = NULL;
		data->dep    = NULL;
		data->weight = NULL;
	}
	else {
		data->indep  = phoebe_realloc (data->indep,  data->ptsno * sizeof (*data->indep));
		data->dep    = phoebe_realloc (data->dep,    data->ptsno * sizeof (*data->dep));
		data->weight = phoebe_realloc (data->weight, data->ptsno * sizeof (*data->weight));
	}

	return 0;
}

int allocate_memory_for_spots (PHOEBE_spots *spots)
{
	int sp_no, ss_no;

	GtkWidget *readout_widget;
	
	readout_widget = lookup_widget (PHOEBE, "spots_sprim_value");
	sp_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "spots_ssec_value");
	ss_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));

	if (sp_no != 0) {
		spots->XLAT1  = phoebe_malloc (sp_no * sizeof (double));
		spots->XLONG1 = phoebe_malloc (sp_no * sizeof (double));
		spots->RADSP1 = phoebe_malloc (sp_no * sizeof (double));
		spots->TEMSP1 = phoebe_malloc (sp_no * sizeof (double));
	}

	if (ss_no != 0) {
		spots->XLAT2  = phoebe_malloc (ss_no * sizeof (double));
		spots->XLONG2 = phoebe_malloc (ss_no * sizeof (double));
		spots->RADSP2 = phoebe_malloc (ss_no * sizeof (double));
		spots->TEMSP2 = phoebe_malloc (ss_no * sizeof (double));
	}

	return 0;
}

int free_memory_allocated_for_spots (PHOEBE_spots *spots)
{
	int sp_no, ss_no;

	GtkWidget *readout_widget;
	
	readout_widget = lookup_widget (PHOEBE, "spots_sprim_value");
	sp_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "spots_ssec_value");
	ss_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));

	if (sp_no != 0) {
		free (spots->XLAT1);
		free (spots->XLONG1);
		free (spots->RADSP1);
		free (spots->TEMSP1);
	}

	if (ss_no != 0) {
		free (spots->XLAT2);
		free (spots->XLONG2);
		free (spots->RADSP2);
		free (spots->TEMSP2);
	}
}

PHOEBE_main_parameters read_in_main_parameters ()
	{
	GtkWidget *readout_widget;
	char *readout_str;
	PHOEBE_main_parameters parameters;

	readout_widget    = phoebe_widget (HJD0);
	readout_str       = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	parameters.HJD0   = atof (readout_str);

	readout_widget    = phoebe_widget (PERIOD);
	readout_str       = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	parameters.PERIOD = atof (readout_str);

	readout_widget    = phoebe_widget (DPDT);
	readout_str       = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	parameters.DPDT   = atof (readout_str);

	readout_widget    = phoebe_widget (PSHIFT);
	parameters.PSHIFT = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (SMA);
	parameters.SMA    = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (RM);
	parameters.RM     = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (INCL);
	parameters.XINCL  = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (VGA);
	parameters.VGA    = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (TAVH);
	parameters.TAVH   = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (TAVC);
	parameters.TAVC   = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (PHSV);
	parameters.PHSV   = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (PCSV);
	parameters.PCSV   = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (GR1);
	parameters.GR1    = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (GR2);
	parameters.GR2    = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (ALB1);
	parameters.ALB1   = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (ALB2);
	parameters.ALB2   = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (F1);
	parameters.F1     = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (F2);
	parameters.F2     = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (E);
	parameters.E      = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (PERR0);
	parameters.PERR0  = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (DPERDT);
	readout_str       = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	parameters.DPERDT = atof (readout_str);

	readout_widget    = phoebe_widget (MNORM);
	parameters.MNORM  = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (LOGG1);
	parameters.LOGG1  = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (LOGG2);
	parameters.LOGG2  = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (MET1);
	parameters.M1     = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget    = phoebe_widget (MET2);
	parameters.M2     = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	parameters.ABUNIN = parameters.M1;

	return parameters;
	}

PHOEBE_switches read_in_switches ()
	{
	GtkWidget *readout_widget;

	char *readout_str;
	int readout_int;

	PHOEBE_switches switches;

/* FIX ME! Add MPAGE */

	switches.NLC = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));

	readout_int  = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));
	if (readout_int == 0) {switches.IFVC1 = 0; switches.IFVC2 = 0;}
	if (readout_int == 1) {switches.IFVC1 = 1; switches.IFVC2 = 0;}
	if (readout_int == 2) {switches.IFVC1 = 1; switches.IFVC2 = 1;}

	if (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "data_binning_switch"))->active == TRUE) switches.BINNING = 1;
	else switches.BINNING = 0;

	if (switches.BINNING == 0) switches.BINNO = 0;
	else
		{
		readout_widget = lookup_widget (PHOEBE, "data_binning_value");
		switches.BINNO = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));
		}

	/* This is something the user shouldn't be bothered with: */
	switches.NPPL = 1;

	readout_widget = lookup_widget (PHOEBE, "luminosities_nref_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) switches.MREF = 2;
	else                                            switches.MREF = 1;
	
	if (switches.MREF == 2)
		{
		readout_widget = lookup_widget (PHOEBE, "luminosities_nref_value");
		switches.NREF = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));
		}
	else switches.NREF = 1;
	
	readout_widget = lookup_widget (PHOEBE, "luminosities_icor1_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) switches.ICOR1 = 1; else switches.ICOR1 = 0;

	readout_widget = lookup_widget (PHOEBE, "luminosities_icor2_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) switches.ICOR2 = 1; else switches.ICOR2 = 0;

	readout_widget = lookup_widget (PHOEBE, "data_model_list_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	if (strcmp (readout_str, "X-ray binary"                                         ) == 0) switches.MODE = -1;
	if (strcmp (readout_str, "General binary system (no constraints)"               ) == 0) switches.MODE =  0;
	if (strcmp (readout_str, "Overcontact binary of the W UMa type"                 ) == 0) switches.MODE =  1;
	if (strcmp (readout_str, "Detached binary"                                      ) == 0) switches.MODE =  2;
	if (strcmp (readout_str, "Overcontact binary not in thermal contact"            ) == 0) switches.MODE =  3;
	if (strcmp (readout_str, "Semi-detached binary, primary star fills Roche lobe"  ) == 0) switches.MODE =  4;
	if (strcmp (readout_str, "Semi-detached binary, secondary star fills Roche lobe") == 0) switches.MODE =  5;
	if (strcmp (readout_str, "Double contact binary"                                ) == 0) switches.MODE =  6;

	readout_widget = lookup_widget (PHOEBE, "luminosities_ipb_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) switches.IPB = 1; else switches.IPB = 0;

	readout_widget = lookup_widget (PHOEBE, "luminosities_ifat1_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) switches.IFAT1 = 1; else switches.IFAT1 = 0;

	readout_widget = lookup_widget (PHOEBE, "luminosities_ifat2_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) switches.IFAT2 = 1; else switches.IFAT2 = 0;

	readout_widget = lookup_widget (PHOEBE, "luminosities_logg_from_model_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) switches.MODELLGG = 1; else switches.MODELLGG = 0;

	readout_widget = lookup_widget (PHOEBE, "fitting_n1_value");
	switches.N1 = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "fitting_n2_value");
	switches.N2 = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "fitting_n1l_value");
	switches.N1L = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "fitting_n2l_value");
	switches.N2L = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "fitting_isym_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) switches.ISYM = 1; else switches.ISYM = 0;

	readout_widget = lookup_widget (PHOEBE, "data_the_value");
	switches.THE = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "fitting_xlamda_value");
	switches.XLAMDA = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

/* FIX ME! */
	switches.KDISK = 0;
	switches.K0    = 2;
/* ******* */

	readout_widget = lookup_widget (PHOEBE, "luminosities_noise_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active)
		{
		readout_widget = lookup_widget (PHOEBE, "luminosities_noise_list_entry");
		readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
		if (strcmp (readout_str, "No level-dependent weighting") == 0) switches.NOISE = 0;
		if (strcmp (readout_str, "Scatter scales with square root") == 0) switches.NOISE = 1;
		if (strcmp (readout_str, "Scatter scales with light level") == 0) switches.NOISE = 2;
		readout_widget = lookup_widget (PHOEBE, "luminosities_noise_value");
		switches.SIGMA = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
		readout_widget = lookup_widget (PHOEBE, "luminosities_seed_value");
		switches.SEED = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
		}
	else
		{
		switches.NOISE = 0;
		switches.SIGMA = 0.0;
		switches.SEED  = 0;
		}

	readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_reddening_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) switches.REDDENING = 1; else switches.REDDENING = 0;

	readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_r_value");
	switches.REDDENING_R = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_color_excess_value");
	switches.REDDENING_E = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	return switches;
	}

PHOEBE_curve_parameters read_in_curve_parameters ()
	{
	GtkWidget *readout_widget;
	PHOEBE_curve_parameters curve;

	double hjd0, period;
	
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_phnorm_value");
	curve.PHNORM = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_factor_value");
	curve.FACTOR = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "system_hjd0_value");
	hjd0 = atof (gtk_entry_get_text (GTK_ENTRY (readout_widget)));

	readout_widget = lookup_widget (PHOEBE, "system_period_value");
	period = atof (gtk_entry_get_text (GTK_ENTRY (readout_widget)));

	curve.HJDST = hjd0 - 0.5 * period;
	curve.HJDSP = hjd0 + 0.5 * period;
	curve.HJDIN = period / 100.0;
	
	curve.PHSTRT = -0.5;
	curve.PHSTOP = 0.5;
	curve.PHIN = 0.01;

	return curve;
	}

PHOEBE_limb_darkening read_in_ld_coefficients ()
	{
	GtkWidget *readout_widget;
	char *readout_str;

	PHOEBE_limb_darkening ld;

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE), "ld_ld_law_combo_box_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	if (strcmp (readout_str, "Linear Cosine Law") == 0) ld.LD = 1;
	if (strcmp (readout_str, "Logarithmic Law")   == 0) ld.LD = 2;
	if (strcmp (readout_str, "Square Root Law")   == 0) ld.LD = 3;

	readout_widget = lookup_widget (PHOEBE, "ld_xbol1_value");
	ld.XBOL1 = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "ld_xbol2_value");
	ld.XBOL2 = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "ld_ybol1_value");
	ld.YBOL1 = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	readout_widget = lookup_widget (PHOEBE, "ld_ybol2_value");
	ld.YBOL2 = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	return ld;
	}

int read_in_spots (PHOEBE_spots *spots)
	{
	GtkWidget *readout_widget;

	int i;

	char *readout_str;

	/* First we read in the number of spots on both stars:                    */
	readout_widget = lookup_widget (PHOEBE, "spots_sprim_value");
	spots->SPRIM = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE, "spots_ssec_value");
	spots->SSEC = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));

	/* Next we read in the spot movement switches due to eccentricity or asin-  */
	/* chronous rotation:                                                       */
	readout_widget = lookup_widget (PHOEBE, "spots_ifsmv1_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) spots->IFSMV1 = 1; else spots->IFSMV1 = 0;
	readout_widget = lookup_widget (PHOEBE, "spots_ifsmv2_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) spots->IFSMV2 = 1; else spots->IFSMV2 = 0;

	/* Check whether the first spot is to be adjusted:                          */
	if ( (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE,  "spots_xlat1_adjust"))->active) ||
		 (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_xlong1_adjust"))->active) ||
		 (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_radsp1_adjust"))->active) ||
		 (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_temsp1_adjust"))->active) ) {

		readout_widget = lookup_widget (PHOEBE, "spots_spot_1_source_list");
		gtk_label_get (GTK_LABEL(GTK_BIN(readout_widget)->child), &readout_str);
		if (strcmp (readout_str, "on primary") == 0) spots->KSPA = 1; else spots->KSPA = 2;

		readout_widget = lookup_widget (PHOEBE, "spots_spot_1_spot_list");
		gtk_label_get (GTK_LABEL(GTK_BIN(readout_widget)->child), &readout_str);
		sscanf (readout_str, "Spot %d", &i);
		spots->NSPA = i;
	}
	else {
		spots->KSPA = 0;
		spots->NSPA = 0;
	}

	if ( (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE,  "spots_xlat2_adjust"))->active) ||
		 (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_xlong2_adjust"))->active) ||
		 (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_radsp2_adjust"))->active) ||
		 (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_temsp2_adjust"))->active) ) {

		readout_widget = lookup_widget (PHOEBE, "spots_spot_2_source_list");
		gtk_label_get (GTK_LABEL(GTK_BIN(readout_widget)->child), &readout_str);
		if (strcmp (readout_str, "on primary") == 0) spots->KSPB = 1; else spots->KSPB = 2;

		readout_widget = lookup_widget (PHOEBE, "spots_spot_2_spot_list");
		gtk_label_get (GTK_LABEL(GTK_BIN(readout_widget)->child), &readout_str);
		sscanf (readout_str, "Spot %d", &i);
		spots->NSPB = i;
	}
	else {
		spots->KSPB = 0;
		spots->NSPB = 0;
	}

	if (spots->SPRIM != 0)
		for (i = 0; i < spots->SPRIM; i++) {
			readout_widget = lookup_widget (PHOEBE, "spots_primary_info_list");
			gtk_clist_get_text (GTK_CLIST (readout_widget), i, 1, &readout_str);
			spots->XLAT1[i]  = atof (readout_str);
			gtk_clist_get_text (GTK_CLIST (readout_widget), i, 2, &readout_str);
			spots->XLONG1[i] = atof (readout_str);
			gtk_clist_get_text (GTK_CLIST (readout_widget), i, 3, &readout_str);
			spots->RADSP1[i] = atof (readout_str);
			gtk_clist_get_text (GTK_CLIST (readout_widget), i, 4, &readout_str);
			spots->TEMSP1[i] = atof (readout_str);
		}

	if (spots->SSEC != 0)
		for (i = 0; i < spots->SSEC; i++) {
			readout_widget = lookup_widget (PHOEBE, "spots_secondary_info_list");
			gtk_clist_get_text (GTK_CLIST (readout_widget), i, 1, &readout_str);
			spots->XLAT2[i] = atof (readout_str);
			gtk_clist_get_text (GTK_CLIST (readout_widget), i, 2, &readout_str);
			spots->XLONG2[i] = atof (readout_str);
			gtk_clist_get_text (GTK_CLIST (readout_widget), i, 3, &readout_str);
			spots->RADSP2[i] = atof (readout_str);
			gtk_clist_get_text (GTK_CLIST (readout_widget), i, 4, &readout_str);
			spots->TEMSP2[i] = atof (readout_str);
		}

	return 0;
}

PHOEBE_mms read_in_mms ()
	{
	int i;
	GtkWidget *readout_widget;

	const char *mms1[] =
		{
		"fitting_mms_switch_1_1",  "fitting_mms_switch_1_2",  "fitting_mms_switch_1_3",
		"fitting_mms_switch_1_4",  "fitting_mms_switch_1_5",  "fitting_mms_switch_1_6",
		"fitting_mms_switch_1_7",  "fitting_mms_switch_1_8",  "fitting_mms_switch_1_9",
		"fitting_mms_switch_1_10", "fitting_mms_switch_1_11", "fitting_mms_switch_1_12",
		"fitting_mms_switch_1_13", "fitting_mms_switch_1_14", "fitting_mms_switch_1_15",
		"fitting_mms_switch_1_16", "fitting_mms_switch_1_17", "fitting_mms_switch_1_18",
		"fitting_mms_switch_1_19", "fitting_mms_switch_1_20", "fitting_mms_switch_1_21",
		"fitting_mms_switch_1_22", "fitting_mms_switch_1_23", "fitting_mms_switch_1_24",
		"fitting_mms_switch_1_25", "fitting_mms_switch_1_26", "fitting_mms_switch_1_27",
		"fitting_mms_switch_1_28", "fitting_mms_switch_1_29", "fitting_mms_switch_1_30",
		"fitting_mms_switch_1_31", "fitting_mms_switch_1_32", "fitting_mms_switch_1_33",
		"fitting_mms_switch_1_34", "fitting_mms_switch_1_35"
		};

	const char *mms2[] =
		{
		"fitting_mms_switch_2_1",  "fitting_mms_switch_2_2",  "fitting_mms_switch_2_3",
		"fitting_mms_switch_2_4",  "fitting_mms_switch_2_5",  "fitting_mms_switch_2_6",
		"fitting_mms_switch_2_7",  "fitting_mms_switch_2_8",  "fitting_mms_switch_2_9",
		"fitting_mms_switch_2_10", "fitting_mms_switch_2_11", "fitting_mms_switch_2_12",
		"fitting_mms_switch_2_13", "fitting_mms_switch_2_14", "fitting_mms_switch_2_15",
		"fitting_mms_switch_2_16", "fitting_mms_switch_2_17", "fitting_mms_switch_2_18",
		"fitting_mms_switch_2_19", "fitting_mms_switch_2_20", "fitting_mms_switch_2_21",
		"fitting_mms_switch_2_22", "fitting_mms_switch_2_23", "fitting_mms_switch_2_24",
		"fitting_mms_switch_2_25", "fitting_mms_switch_2_26", "fitting_mms_switch_2_27",
		"fitting_mms_switch_2_28", "fitting_mms_switch_2_29", "fitting_mms_switch_2_30",
		"fitting_mms_switch_2_31", "fitting_mms_switch_2_32", "fitting_mms_switch_2_33",
		"fitting_mms_switch_2_34", "fitting_mms_switch_2_35"
		};

	const char *mms3[] =
		{
		"fitting_mms_switch_3_1",  "fitting_mms_switch_3_2",  "fitting_mms_switch_3_3",
		"fitting_mms_switch_3_4",  "fitting_mms_switch_3_5",  "fitting_mms_switch_3_6",
		"fitting_mms_switch_3_7",  "fitting_mms_switch_3_8",  "fitting_mms_switch_3_9",
		"fitting_mms_switch_3_10", "fitting_mms_switch_3_11", "fitting_mms_switch_3_12",
		"fitting_mms_switch_3_13", "fitting_mms_switch_3_14", "fitting_mms_switch_3_15",
		"fitting_mms_switch_3_16", "fitting_mms_switch_3_17", "fitting_mms_switch_3_18",
		"fitting_mms_switch_3_19", "fitting_mms_switch_3_20", "fitting_mms_switch_3_21",
		"fitting_mms_switch_3_22", "fitting_mms_switch_3_23", "fitting_mms_switch_3_24",
		"fitting_mms_switch_3_25", "fitting_mms_switch_3_26", "fitting_mms_switch_3_27",
		"fitting_mms_switch_3_28", "fitting_mms_switch_3_29", "fitting_mms_switch_3_30",
		"fitting_mms_switch_3_31", "fitting_mms_switch_3_32", "fitting_mms_switch_3_33",
		"fitting_mms_switch_3_34", "fitting_mms_switch_3_35"
		};

	const char *mms4[] =
		{
		"fitting_mms_switch_4_1",  "fitting_mms_switch_4_2",  "fitting_mms_switch_4_3",
		"fitting_mms_switch_4_4",  "fitting_mms_switch_4_5",  "fitting_mms_switch_4_6",
		"fitting_mms_switch_4_7",  "fitting_mms_switch_4_8",  "fitting_mms_switch_4_9",
		"fitting_mms_switch_4_10", "fitting_mms_switch_4_11", "fitting_mms_switch_4_12",
		"fitting_mms_switch_4_13", "fitting_mms_switch_4_14", "fitting_mms_switch_4_15",
		"fitting_mms_switch_4_16", "fitting_mms_switch_4_17", "fitting_mms_switch_4_18",
		"fitting_mms_switch_4_19", "fitting_mms_switch_4_20", "fitting_mms_switch_4_21",
		"fitting_mms_switch_4_22", "fitting_mms_switch_4_23", "fitting_mms_switch_4_24",
		"fitting_mms_switch_4_25", "fitting_mms_switch_4_26", "fitting_mms_switch_4_27",
		"fitting_mms_switch_4_28", "fitting_mms_switch_4_29", "fitting_mms_switch_4_30",
		"fitting_mms_switch_4_31", "fitting_mms_switch_4_32", "fitting_mms_switch_4_33",
		"fitting_mms_switch_4_34", "fitting_mms_switch_4_35"
		};

	const char *mms5[] =
		{
		"fitting_mms_switch_5_1",  "fitting_mms_switch_5_2",  "fitting_mms_switch_5_3",
		"fitting_mms_switch_5_4",  "fitting_mms_switch_5_5",  "fitting_mms_switch_5_6",
		"fitting_mms_switch_5_7",  "fitting_mms_switch_5_8",  "fitting_mms_switch_5_9",
		"fitting_mms_switch_5_10", "fitting_mms_switch_5_11", "fitting_mms_switch_5_12",
		"fitting_mms_switch_5_13", "fitting_mms_switch_5_14", "fitting_mms_switch_5_15",
		"fitting_mms_switch_5_16", "fitting_mms_switch_5_17", "fitting_mms_switch_5_18",
		"fitting_mms_switch_5_19", "fitting_mms_switch_5_20", "fitting_mms_switch_5_21",
		"fitting_mms_switch_5_22", "fitting_mms_switch_5_23", "fitting_mms_switch_5_24",
		"fitting_mms_switch_5_25", "fitting_mms_switch_5_26", "fitting_mms_switch_5_27",
		"fitting_mms_switch_5_28", "fitting_mms_switch_5_29", "fitting_mms_switch_5_30",
		"fitting_mms_switch_5_31", "fitting_mms_switch_5_32", "fitting_mms_switch_5_33",
		"fitting_mms_switch_5_34", "fitting_mms_switch_5_35"
		};

	PHOEBE_mms mms;

	readout_widget = lookup_widget (PHOEBE, "fitting_mms_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) mms.on = 1; else mms.on = 0;

	readout_widget = lookup_widget (PHOEBE, "fitting_mms_value");
	mms.no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));

	for (i = 0; i < 35; i++)
		{
		readout_widget = lookup_widget (PHOEBE, mms1[i]);
		if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) mms.s1[i] = 1; else mms.s1[i] = 0;
		readout_widget = lookup_widget (PHOEBE, mms2[i]);
		if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) mms.s2[i] = 1; else mms.s2[i] = 0;
		readout_widget = lookup_widget (PHOEBE, mms3[i]);
		if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) mms.s3[i] = 1; else mms.s3[i] = 0;
		readout_widget = lookup_widget (PHOEBE, mms4[i]);
		if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) mms.s4[i] = 1; else mms.s4[i] = 0;
		readout_widget = lookup_widget (PHOEBE, mms5[i]);
		if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) mms.s5[i] = 1; else mms.s5[i] = 0;
		}

	return mms;
	}
	
PHOEBE_wl_dependent_parameters read_in_wl_dependent_parameters (char *filter)
	{
	/* This function reads in all wavelength-dependent parameters:              */
	/*                                                                          */
	/*   WLA         wavelength                                                 */
	/*   HLA         primary star luminosity                                    */
	/*   CLA         secondary star luminosity                                  */
	/*   X1A         primary star linear limb darkening coeficient              */
	/*   Y1A         primary star non-linear limb darkening coeficient          */
	/*   X2A         secondary star linear limb darkening coeficient            */
	/*   Y2A         secondary star non-linear limb darkening coeficient        */
	/*   EL3         third light                                                */
	/*   OPSF        opacity function                                           */
	/*   NOISE       level-dependent weighting model                            */
	/*   SIGMA       standard deviation of the data set                         */
	/*                                                                          */

	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));

	int i;
	int match_lc = 0;
	int match_rv = 0;

	GtkWidget *readout_widget;
	char      *readout_str;

	PHOEBE_wl_dependent_parameters mono;

	/* If this function was called without any data files, we just set every-   */
	/* thing to 0 and return:                                                   */
	if ( (lc_no == 0) && (rv_no == 0) ) {
		mono.WLA = mono.HLA = mono.CLA = mono.X1A = mono.X2A = mono.Y1A = mono.Y2A = mono.EL3 = mono.OPSF = mono.SIGMA = 0.0;
		return mono;
	}

	/* Within the following loop we examine all filter names and stop at one    */
	/* that successfully compares to the argument name.                         */
	for (i = 0; i < lc_no; i++)
		if (strcmp (filter, PHOEBE_lc_data[i].filter) == 0) { match_lc = 1; break; }
	if (match_lc == 0)
		for (i = 0; i < rv_no; i++)
			if (strcmp (filter, PHOEBE_rv_data[i].filter) == 0) { match_rv = 1; break; }
	if ( (match_lc == 0) && (match_rv == 0) )
		{
		/* This happens when:                                                     */
		/* 1) user left the filter setting to "Undefined",                        */
		/* 2) user entered an invalid name of the filter in his keyword file.     */
		/* Either way, set up the defaults, wrap it up and exit.                  */

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
		return mono;
		}

	/* match_* now tells us what type of data file is analysed and i tells us   */
	/* which filter we want. With that we read in wavelength-dependent parame-  */
	/* ters:                                                                    */

	/* 1. Wavelength: */
	sscanf (filter, "%lfnm", &mono.WLA);

	mono.IBAND = 0;

	if (strncmp (filter, "350nm (u)", 9) == 0) mono.IBAND = 1;
	if (strncmp (filter, "411nm (v)", 9) == 0) mono.IBAND = 2;
	if (strncmp (filter, "467nm (b)", 9) == 0) mono.IBAND = 3;
	if (strncmp (filter, "547nm (y)", 9) == 0) mono.IBAND = 4;

	if (strncmp (filter, "360nm (U)", 9) == 0) mono.IBAND = 5;
	if (strncmp (filter, "440nm (B)", 9) == 0) mono.IBAND = 6;
	if (strncmp (filter, "550nm (V)", 9) == 0) mono.IBAND = 7;
	if (strncmp (filter, "700nm (R)", 9) == 0) mono.IBAND = 8;
	if (strncmp (filter, "900nm (I)", 9) == 0) mono.IBAND = 9;
	if (strncmp (filter, "1250nm (J)", 10) == 0) mono.IBAND = 10;
	if (strncmp (filter, "2200nm (K)", 10) == 0) mono.IBAND = 11;
	if (strncmp (filter, "3400nm (L)", 10) == 0) mono.IBAND = 12;
	if (strncmp (filter, "5000nm (M)", 10) == 0) mono.IBAND = 13;
	if (strncmp (filter, "10200nm (N)", 11) == 0) mono.IBAND = 14;

	if (strncmp (filter, "647nm (Rc)", 10) == 0) mono.IBAND = 15;
	if (strncmp (filter, "786nm (Ic)", 10) == 0) mono.IBAND = 16;

	if (strncmp (filter, "419nm (Bt)", 10) == 0) mono.IBAND = 23;
	if (strncmp (filter, "523nm (Vt)", 10) == 0) mono.IBAND = 24;
	if (strncmp (filter, "505nm (Hp)", 10) == 0) mono.IBAND = 25;

	if (strncmp (filter, "861nm (RVIJ)", 12) == 0) {
		phoebe_warning ("861nm filter not supported by WD2003, Johnson I adopted.\n");
		mono.IBAND = 9;
	}

	if (mono.IBAND == 0) {
		phoebe_warning ("IBAND assignment failed. Johnson V filter (550nm) assumed.\n");
		mono.IBAND = 7;
	}

	/* 2. Luminosities: */
	if (match_lc == 1)
		{
		readout_widget = lookup_widget (PHOEBE, "luminosities_lc_info_list");
		gtk_clist_get_text (GTK_CLIST (readout_widget), i, 1, &readout_str);
		mono.HLA = atof (readout_str);
		gtk_clist_get_text (GTK_CLIST (readout_widget), i, 2, &readout_str);
		mono.CLA = atof (readout_str);
		}
	else
		{
		/* I have no idea why there is support for RV luminosities; when I under- */
		/* stand it, I'll make proper readouts.                                   */
		mono.HLA = 10.0;
		mono.CLA = 10.0;
		}

	/* 3. Limb darkening coefficients: */
	if (match_lc == 1) readout_widget = lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list");
	if (match_rv == 1) readout_widget = lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list");
	gtk_clist_get_text (GTK_CLIST (readout_widget), i, 1, &readout_str);
	mono.X1A = atof (readout_str);
	gtk_clist_get_text (GTK_CLIST (readout_widget), i, 2, &readout_str);
	mono.Y1A = atof (readout_str);
	gtk_clist_get_text (GTK_CLIST (readout_widget), i, 3, &readout_str);
	mono.X2A = atof (readout_str);
	gtk_clist_get_text (GTK_CLIST (readout_widget), i, 4, &readout_str);
	mono.Y2A = atof (readout_str);

	/* 4. Third light: */
	
	/* Third light is defined only for LCs, so we have to disable the readout   */
	/* for RVs:                                                                 */

	if (match_lc == 1)
		{
		gtk_clist_get_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_el3_info_list")), i, 1, &readout_str);
		mono.EL3 = atof (readout_str);
		}
	else
		mono.EL3 = 0.0;

	/* 5. Opacity function:                                                     */
	if (match_lc == 1)
		{
		gtk_clist_get_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_el3_info_list")), i, 2, &readout_str);
		mono.OPSF = atof (readout_str);
		}
	else
		mono.OPSF = 0.0;

	/* 6. Level-dependent weighting:                                            */
	if (match_lc == 1)
		{
		readout_widget = lookup_widget (PHOEBE, "luminosities_weighting_info_list");
		gtk_clist_get_text (GTK_CLIST (readout_widget), i, 1, &readout_str);
		if (strcmp (readout_str, "No Level-Dependent Weighting")    == 0) mono.NOISE = 0;
		if (strcmp (readout_str, "Scatter Scales With Square Root") == 0) mono.NOISE = 1;
		if (strcmp (readout_str, "Scatter Scales With Light Level") == 0) mono.NOISE = 2;
		}
	else
		mono.NOISE = 0;

	/* 7. Standard deviation:                                                   */
	if (match_lc == 1)
		mono.SIGMA = atof (PHOEBE_lc_data[i].sigma);

	if (match_rv == 1)
		{
		/* We have to divide sigma with 100 if input units are km/s:              */
		if (strcmp (PHOEBE_rv_data[i].column2, "RV in km/s") == 0) mono.SIGMA = atof (PHOEBE_rv_data[i].sigma) / 100.0;
		else mono.SIGMA = atof (PHOEBE_rv_data[i].sigma);
		}

	/* 8. Systemic radial velocity:                                             */
	readout_widget = lookup_widget (PHOEBE, "system_vga_value");
	mono.VGA = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	return mono;
	}

int read_in_dco_values (char *filename, PHOEBE_dco_record *dco_record, double *correlation_matrix)
	{
	/* This function opens the given DCO file from temp directory and reads in  */
	/* all available information to the variable passed as the argument.        */

	int i, j, k;

	PHOEBE_switches switches = read_in_switches ();

	double readout_dbl;

	char working_string[255];
	char *working_str = working_string;

	FILE *dcout;

	dcout = fopen (filename, "r");

	while (feof (dcout) == FALSE)
		{
		fgets (working_str, 255, dcout);

		if (strcmp (working_str, " Sums of squares of residuals for separate curves, including only individual weights\n") == 0)
			{
			fgets (working_str, 255, dcout);      /* Skip an empty line in DCO file */
			fgets (working_str, 255, dcout);      /* Skip a header line in DCO file */
			for (i = 0; i < switches.NLC + switches.IFVC1 + switches.IFVC2; i++)
				fscanf (dcout, "%*d %d %lf", &dco_record->points_no[i], &dco_record->chi2[i]);
			}

		if (strcmp (working_str, "       CORRELATION COEFFICIENTS\n") == 0)
			{
			fgets (working_str, 255, dcout);      /* Skip an empty line in DCO file */

			/* How many rows does the DC list have -> this tells us what is the di- */
			/* mension of the correlation matrix:                                   */
			i = GTK_CLIST (lookup_widget (PHOEBE_dc, "dc_parameters_info_list"))->rows;

			/* Our correlation matrix is i x i in size. Let's read it in:           */
			for (j = 0; j < i; j++)
				for (k = 0; k < i; k++)
					fscanf (dcout, "%lf", &correlation_matrix[j*i+k]);
			}

		if (strcmp (working_str, "                      Input-Output in D Format\n") == 0)
			{
			fgets (working_str, 255, dcout);      /* Skip an empty line in DCO file */
			fgets (working_str, 255, dcout);      /* Skip a header line in DCO file */
			i = 0;
			while (fscanf (dcout, "%d %d %lf %lf %lf %lf", &dco_record->param_no[i], &dco_record->curve_no[i], &dco_record->original_value[i], &dco_record->correction[i], &dco_record->modified_value[i], &dco_record->sigma[i]) == 6)
				{
				/* If we adjusted temperatures, we have to modify the units:          */
				if ( (dco_record->param_no[i] == 19) || (dco_record->param_no[i] == 20) )
					{
					dco_record->original_value[i] *= 10000.0;
					dco_record->correction[i] *= 10000.0;
					dco_record->modified_value[i] *= 10000.0;
					dco_record->sigma[i] *= 10000.0;
					}
				/* The same goes for center-of-mass radial velocity:                  */
				if ( dco_record->param_no[i] == 15 )
					{
					dco_record->original_value[i] *= 100.0;
					dco_record->correction[i] *= 100.0;
					dco_record->modified_value[i] *= 100.0;
					dco_record->sigma[i] *= 100.0;
					}
				i++;
				}
			}
		}

	fclose (dcout);

	return 0;
	}

int read_in_data_file_info (GtkWidget *parent, PHOEBE_data_record *input)
	{
	/* This function reads in the experimental data values from parent widget,  */
	/* which can be either PHOEBE_assign_data_file for LCs or PHOEBE_assign_rv_ */
	/* _data_file for RVs. Variable input holds only one element of LC and RV   */
	/* array records - the one selected in main PHOEBE window.                  */
	/*                                                                          */
	/* Data that is read here:                                                  */
	/*                                                                          */
	/* Column 1 contents:  independent variable (HJD, phase)                    */
	/* Column 2 contents:  dependent variable (magnitude, flux)                 */
	/* Column 3 contents:  weighting (real weights, integer weights, undefined) */
	/* Filename:           experimental data filename                           */
	/* Standard deviation: sigma of experimental data set                       */
	/* Filter:             filter of experimental data set                      */

	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));

	int selected_row;

	int i;
	int modified = 0;

	char working_string[255];
	char *working_str = working_string;

	GtkWidget *readout_widget;
	char      *readout_str;
	double     readout_dbl;

	/* Read out what's in column 1 of the data file:                            */
	readout_widget = lookup_widget (parent, "data_file_column_1_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (input->column1, "%s", readout_str);

	/* Read out what's in column 2 of the data file:                            */
	readout_widget = lookup_widget (parent, "data_file_column_2_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (input->column2, "%s", readout_str);

	/* Read out what's in column 3 of the data file:                            */
	readout_widget = lookup_widget (parent, "data_file_column_3_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (input->column3, "%s", readout_str);

	/* Read out the filename:                                                   */
	readout_widget = lookup_widget (parent, "data_file_filename_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (input->filename, "%s", readout_str);

	/* Read out standard deviation:                                             */
	readout_widget = lookup_widget (parent, "data_file_sigma_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (input->sigma, "%lf", readout_dbl);

	/* Read out the filter name:                                                */
	readout_widget = lookup_widget (parent, "data_file_filter_button");
	gtk_label_get (GTK_LABEL(GTK_BIN(readout_widget)->child), &readout_str);

	/* This is where things get a little trickier: if there are two or more LCs */
	/* or RVs in the same filter, we want to tell them apart somehow; that is   */
	/* why we append a #number to their names. We have to do it for all possi-  */
	/* ble combinations -- even if one LC and one RV are in the same filter,    */
	/* they must be separated the same way.                                     */

	/* First, let's see what record are we editing, because we don't want to    */
	/* compare filter's name against itself:                                    */
	if (parent == PHOEBE_assign_data_file)
		selected_row = (int) ((GList *) (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list"))->selection))->data;
	if (parent == PHOEBE_assign_rv_data_file)
		selected_row = (int) ((GList *) (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list"))->selection))->data;

	i = 0;
	while (i < lc_no)
		{
		if (
		   (strncmp (PHOEBE_lc_data[i].filter, readout_str, strlen (readout_str)) == 0) &&
		   (strchr (readout_str, '#') == NULL) &&
			 (strcmp (readout_str, PHOEBE_lc_data[selected_row].filter) != 0)
			 )
			{
			sprintf (PHOEBE_lc_data[i].filter, "%s #%d", readout_str, modified+1);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list")), i, 3, PHOEBE_lc_data[i].filter);
			modified += 1;
			}
		i++;
		}

	i = 0;
	while (i < rv_no)
		{
		if (
		   (strncmp (PHOEBE_rv_data[i].filter, readout_str, strlen (readout_str)) == 0) &&
			 (strchr (readout_str, '#') == NULL) &&
			 (strcmp (readout_str, PHOEBE_rv_data[selected_row].filter) != 0)
			 )
			{
			sprintf (PHOEBE_rv_data[i].filter, "%s #%d", readout_str, modified+1);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list")), i, 3, PHOEBE_rv_data[i].filter);
			modified += 1;
			}
		i++;
		}

	if (modified > 0)
		{
		sprintf (working_str, "%s #%d", readout_str, modified+1);
		readout_str = working_string;
		}

	sprintf (input->filter, "%s", readout_str);

	return 0;
	}

int read_in_synthetic_lc_data (char *filename, PHOEBE_data *data, PHOEBE_calculated_parameters *params, int indep, int dep)
	{
	/* This function opens the given LCO file from temp directory and reads in  */
	/* calculated values of a synthetic lightcurve. It allocates memory for da- */
	/* ta through the allocate_memory_for_data call and writes in the values    */
	/* according to parameters indep and dep. It sets all weights to 1.0.       */

	struct lc_record_tag
		{
		double hjd;
		double phase;
		double flux1;
		double flux2;
		double total;
		double norm;
		double dist;
		double mag;
		};
	struct lc_record_tag *record = NULL;
	struct lc_record_tag  rec;

	int i;
	double L1, L2;

	char working_string[255];
	char *working_str = working_string;

	/* All warnings reported in .lco file will be rerouted to screen through a  */
	/* notice window:                                                           */
	GtkWidget *notice_window;
	
	FILE *data_file;

	/* Initialize everything to 0, so we don't get any accidental appending:    */
	data->ptsno = 0; data->indep = NULL; data->dep = NULL; data->weight = NULL;

	data_file = fopen (filename, "r");

	/* We shall read in all the values through a checkup "while" loop, because  */
	/* the output format of .lco file is only *more or less* standard, which    */
	/* means that WD sometimes appends some comments to that file (such as      */
	/* the warning that the secondary component exceeds critical lobe).         */
	while (! feof (data_file))
		{
		fgets (working_str, 250, data_file);
		if (feof (data_file) != 0) break;

		/* WD warnings:                                                           */
		if (strcmp (working_str, " Primary star exceeds outer contact surface\n") == 0)
			notice_window = create_notice_window ("PHOEBE Notice", "Physical Content Feasibility Problem", "Your current set of parameters suggests that", "the primary star exceeds the outer contact surface (L2)!", gtk_widget_destroy);
		if (strcmp (working_str, " Secondary star exceeds outer contact surface\n") == 0)
			notice_window = create_notice_window ("PHOEBE Notice", "Physical Content Feasibility Problem", "Your current set of parameters suggests that", "the secondary star exceeds the outer contact surface (L2)!", gtk_widget_destroy);

		/* WD notices:                                                            */
		if (strstr (working_str, "Note: The light curve output contains simulated observational scatter") != NULL)
			if (PHOEBE_WARN_ON_SYNTHETIC_SCATTER == 1)
				notice_window = create_notice_window ("PHOEBE Notice", "PHOEBE Synthetic Scatter Notice", "This synthetic light curve contains synthetic", "Gaussian scatter. To turn it off, use Luminosities tab.", gtk_widget_destroy);

		/* WD internal problems:                                                  */
		if (strstr (working_str, "TEMPERATURE RANGE EXCEEDED IN SUBROUTINE ATM") != NULL)
			{
			notice_window = create_notice_window ("PHOEBE Notice", "Internal WD algorithm problem", "Your current configuration exceeds the allowed temperature range", "in WD subroutine ATM. Further LC output will be suppressed.", gtk_widget_destroy);
			break;
			}

		/* Read in the value of L2:                                               */
		if (strstr (working_str, " band       L1         L2 ") != NULL)
			{
			if (fscanf (data_file, "%*d %lf %lf %*lf %*lf %*lf %*lf %*lf %*e %*lf %*lf %*lf\n", &L1, &L2) != 2)
				{
				phoebe_warning ("Error in read_in_synthetic_lc_data line 0!\n");
				params->lum_p = -1.0;
				params->lum_s = -1.0;
				}
			else
				{
				params->lum_p = L1;
				params->lum_s = L2;
				}
			}

		/* Read in the first set of calculated parameters:                        */
		if (strstr (working_str, " Star         M/Msun   (Mean Radius)/Rsun     M Bol    Log g (cgs)") != NULL)
			{
			if (fscanf (data_file, "%d %lf %lf %lf %lf\n", &i, &params->mass_p, &params->radius_p, &params->mbol_p, &params->logg_p) != 5) phoebe_warning ("Error in read_in_synthetic_lc_data line 1!\n");
			if (fscanf (data_file, "%d %lf %lf %lf %lf\n", &i, &params->mass_s, &params->radius_s, &params->mbol_s, &params->logg_s) != 5) phoebe_warning ("Error in read_in_synthetic_lc_data line 2!\n");
			}

		/* Read in the second set of calculated parameters:                       */
		if (strstr (working_str, "grid1/4    grid2/4  polar sbr 1   polar sbr 2   surf. area 1  surf. area 2       phase        phase        phase") != NULL)
			if (fscanf (data_file, "%d %d %lf %lf %lf %lf %*lf %*lf\n", &i, &i, &params->psb_p, &params->psb_s, &params->surface_p, &params->surface_s) != 6) phoebe_warning ("Error in read_in_synthetic_lc_data line 3!\n");

		/* Read in synthetic data:                                                */
		if (strstr (working_str, "      JD                 Phase     light 1     light 2     (1+2+3)    norm lite   dist      mag+K") != NULL)
			{
			i = 0;
			fgets (working_str, 250, data_file);
			while (sscanf (working_str, "%lf %lf %lf %lf %lf %lf %lf %lf", &rec.hjd, &rec.phase, &rec.flux1, &rec.flux2, &rec.total, &rec.norm, &rec.dist, &rec.mag) == 8)
				{
				record = realloc (record, (i+1) * sizeof (*record));
				sscanf (working_str, "%lf %lf %lf %lf %lf %lf %lf %lf", &record[i].hjd, &record[i].phase, &record[i].flux1, &record[i].flux2, &record[i].total, &record[i].norm, &record[i].dist, &record[i].mag);
				sprintf(working_str,"%i",i);
				i++;
				fgets (working_str, 250, data_file);
				}
			data->ptsno = i;
			}

		/* Read in the third set of calculated parameters:                        */
		if (strstr (working_str, "star    r pole     deriv     r point     deriv      r side      deriv     r back      deriv") != NULL)
			{
			int pos;
			char *ptr;

			fgets (working_str, 250, data_file);                      /* Empty line */

			/* If there are any asterisks '*' in the string, formatting problems    */
			/* occured and we must handle them.                                     */

			fgets (working_str, 250, data_file);
			if ( (pos = sscanf (working_str, "%d %lf %*lf %lf %*lf %lf %*lf %lf %*lf\n", &i, &params->rpole_p, &params->rpoint_p, &params->rside_p, &params->rback_p)) != 5)
				{
				phoebe_warning ("Formatting problems in lco file, radii, parameter %d.\n", pos);

				ptr = &(working_str[4]);
				if ( (pos = sscanf (ptr, "%lf", &params->rpole_p)) != 1) params->rpole_p = -1.0;
				ptr = &(working_str[26]);
				if ( (pos = sscanf (ptr, "%lf", &params->rpoint_p)) != 1) params->rpoint_p = -1.0;
				ptr = &(working_str[48]);
				if ( (pos = sscanf (ptr, "%lf", &params->rside_p)) != 1) params->rside_p = -1.0;
				ptr = &(working_str[70]);
				if ( (pos = sscanf (ptr, "%lf", &params->rback_p)) != 1) params->rback_p = -1.0;
				}

			fgets (working_str, 250, data_file);
			if ( (pos = sscanf (working_str, "%d %lf %*lf %lf %*lf %lf %*lf %lf %*lf\n", &i, &params->rpole_s, &params->rpoint_s, &params->rside_s, &params->rback_s)) != 5)
				{
				phoebe_warning ("Formatting problems in lco file, radii, parameter %d.\n", pos);

				ptr = &(working_str[4]);
				if ( (pos = sscanf (ptr, "%lf", &params->rpole_s)) != 1) params->rpole_s = -1.0;
				ptr = &(working_str[26]);
				if ( (pos = sscanf (ptr, "%lf", &params->rpoint_s)) != 1) params->rpoint_s = -1.0;
				ptr = &(working_str[48]);
				if ( (pos = sscanf (ptr, "%lf", &params->rside_s)) != 1) params->rside_s = -1.0;
				ptr = &(working_str[70]);
				if ( (pos = sscanf (ptr, "%lf", &params->rback_s)) != 1) params->rback_s = -1.0;
				}
			}
		}

	fclose (data_file);

	allocate_memory_for_data (data);

	for (i = 0; i < data->ptsno; i++)
		{
		if (indep == 1) data->indep[i]  = record[i].hjd;
		if (indep == 2) data->indep[i]  = record[i].phase;
		if (  dep == 3) data->dep[i]    = record[i].flux1;
		if (  dep == 4) data->dep[i]    = record[i].flux2;
		if (  dep == 5) data->dep[i]    = record[i].total;
		if (  dep == 6) data->dep[i]    = record[i].norm;
                    data->weight[i] = 1.0;
		}

	free (record);

	return 0;
	}

int read_in_synthetic_rv_data (char *filename, PHOEBE_data *data, PHOEBE_calculated_parameters *params, int indep, int dep)
	{
	/* This function opens the given LCO file from temp directory and reads in  */
	/* calculated values of a synthetic RV curve. It allocates memory for data  */
	/* through the allocate_memory_for_data call and writes in the values       */
	/* according to parameters indep and dep. It sets all weights to 1.0. If    */
	/* DEP is set to 7 or 8 (user VUNIT), the output will *always* be in km/s.  */

	int i;

	char working_string[255];
	char *working_str = working_string;

	char dummy_str[255];
	
	/* All warnings reported in .lco file will be rerouted to screen through a  */
	/* notice window:                                                           */
	GtkWidget *notice_window;

	FILE *data_file;

	/* This is a temporary variable that is freed at the end of the function:   */
	PHOEBE_synthetic_rv_record *rv_output = phoebe_malloc (sizeof (*rv_output));

	/* Initialize everything to 0, so we don't get any accidental appending:    */
	data->ptsno = 0; data->indep = NULL; data->dep = NULL; data->weight = NULL;

	data_file = fopen (filename, "r");

	/* We shall read in all the values through a checkup "while" loop, because  */
	/* the output format of .lco file is only *more or less* standard, which    */
	/* means that WD sometimes appends some comments to that file (such as      */
	/* the warning that the secondary component exceeds critical lobe).         */
	while (! feof (data_file))
		{
		fgets (working_str, 255, data_file);

		/* If there are any warnings appended to a .lco file, put them on screen: */
		if (strcmp (working_str, " Primary star exceeds outer contact surface\n") == 0)
			notice_window = create_notice_window ("PHOEBE Notice", "Physical Content Feasibility Problem", "Your current set of parameters suggests that", "the primary star exceeds the outer contact surface (L2)!", gtk_widget_destroy);
		if (strcmp (working_str, " Secondary star exceeds outer contact surface\n") == 0)
			notice_window = create_notice_window ("PHOEBE Notice", "Physical Content Feasibility Problem", "Your current set of parameters suggests that", "the secondary star exceeds the outer contact surface (L2)!", gtk_widget_destroy);

		/* Internal WD problems:                                                  */
		if (strstr (working_str, "TEMPERATURE RANGE EXCEEDED IN SUBROUTINE ATM") != NULL)
			{
			notice_window = create_notice_window ("PHOEBE Notice", "Internal WD algorithm problem", "Your current configuration exceeds the allowed temperature range", "in WD subroutine ATM. Further output will be suppressed.", gtk_widget_destroy);
			break;
			}

		/* Read in the first set of calculated parameters:                        */
		if (strstr (working_str, " Star         M/Msun   (Mean Radius)/Rsun     M Bol    Log g (cgs)") != NULL)
			{
			if (fscanf (data_file, "%d %lf %lf %lf %lf\n", &i, &params->mass_p, &params->radius_p, &params->mbol_p, &params->logg_p) != 5) phoebe_warning ("Error in read_in_synthetic_lc_data line 1!\n");
			if (fscanf (data_file, "%d %lf %lf %lf %lf\n", &i, &params->mass_s, &params->radius_s, &params->mbol_s, &params->logg_s) != 5) phoebe_warning ("Error in read_in_synthetic_lc_data line 2!\n");
			}

		/* Read in the second set of calculated parameters:                       */
		if (strstr (working_str, "grid1/4    grid2/4  polar sbr 1   polar sbr 2   surf. area 1  surf. area 2       phase        phase        phase") != NULL)
			if (fscanf (data_file, "%d %d %lf %lf %lf %lf %*lf %*lf\n", &i, &i, &params->psb_p, &params->psb_s, &params->surface_p, &params->surface_s) != 6) phoebe_warning ("Error in read_in_synthetic_lc_data line 3!\n");

		/* Read in synthetic data:                                                */
		if (strstr (working_str, "      JD              Phase     V Rad 1     V Rad 2      del V1      del V2   V1 km/s      V2 km/s") != NULL)
			{
			i = 0;
			while (fscanf (data_file, "%lf %lf %lf %lf %lf %lf %lf %lf\n", &rv_output[i].hjd, &rv_output[i].phase, &rv_output[i].primary_norm_rv, &rv_output[i].secondary_norm_rv, &rv_output[i].primary_eclipse_corr, &rv_output[i].secondary_eclipse_corr, &rv_output[i].primary_rv, &rv_output[i].secondary_rv) == 8)
				{
				sprintf(dummy_str,"%i",i);
				i++;
				rv_output = phoebe_realloc (rv_output, (i+1) * sizeof (*rv_output));
				}
			if (dep != 9) data->ptsno = i; else data->ptsno = 2*i;
			}

		/* Read in the third set of calculated parameters:                        */
		if (strstr (working_str, "star    r pole     deriv     r point     deriv      r side      deriv     r back      deriv") != NULL)
			{
			int pos;
			char *ptr;

			fgets (working_str, 250, data_file);                      /* Empty line */

			/* If there are any asterisks '*' in the string, formatting problems    */
			/* occured and we must handle them.                                     */

			fgets (working_str, 250, data_file);
			if ( (pos = sscanf (working_str, "%d %lf %*lf %lf %*lf %lf %*lf %lf %*lf\n", &i, &params->rpole_p, &params->rpoint_p, &params->rside_p, &params->rback_p)) != 5)
				{
				phoebe_warning ("Formatting problems in lco file, radii, parameter %d.\n", pos);

				ptr = &(working_str[4]);
				if ( (pos = sscanf (ptr, "%lf", &params->rpole_p)) != 1) params->rpole_p = -1.0;
				ptr = &(working_str[26]);
				if ( (pos = sscanf (ptr, "%lf", &params->rpoint_p)) != 1) params->rpoint_p = -1.0;
				ptr = &(working_str[48]);
				if ( (pos = sscanf (ptr, "%lf", &params->rside_p)) != 1) params->rside_p = -1.0;
				ptr = &(working_str[70]);
				if ( (pos = sscanf (ptr, "%lf", &params->rback_p)) != 1) params->rback_p = -1.0;
				}

			fgets (working_str, 250, data_file);
			if ( (pos = sscanf (working_str, "%d %lf %*lf %lf %*lf %lf %*lf %lf %*lf\n", &i, &params->rpole_s, &params->rpoint_s, &params->rside_s, &params->rback_s)) != 5)
				{
				phoebe_warning ("Formatting problems in lco file, radii, parameter %d.\n", pos);

				ptr = &(working_str[4]);
				if ( (pos = sscanf (ptr, "%lf", &params->rpole_s)) != 1) params->rpole_s = -1.0;
				ptr = &(working_str[26]);
				if ( (pos = sscanf (ptr, "%lf", &params->rpoint_s)) != 1) params->rpoint_s = -1.0;
				ptr = &(working_str[48]);
				if ( (pos = sscanf (ptr, "%lf", &params->rside_s)) != 1) params->rside_s = -1.0;
				ptr = &(working_str[70]);
				if ( (pos = sscanf (ptr, "%lf", &params->rback_s)) != 1) params->rback_s = -1.0;
				}
			}
		}

	fclose (data_file);

	allocate_memory_for_data (data);

	for (i = 0; i < data->ptsno; i++)
		{
		/* We will multiply primary_rv and secondary_rv with 100.0 to get km/s:   */

		if (indep == 1) data->indep[i]  = rv_output[i].hjd;
		if (indep == 2) data->indep[i]  = rv_output[i].phase;
		if (  dep == 3) data->dep[i]    = rv_output[i].primary_norm_rv;
		if (  dep == 4) data->dep[i]    = rv_output[i].secondary_norm_rv;
		if (  dep == 5) data->dep[i]    = rv_output[i].primary_eclipse_corr;
		if (  dep == 6) data->dep[i]    = rv_output[i].secondary_eclipse_corr;
		if (  dep == 7) data->dep[i]    = 100.0 * rv_output[i].primary_rv;
		if (  dep == 8) data->dep[i]    = 100.0 * rv_output[i].secondary_rv;
                    data->weight[i] = 1.0;
		}
	free (rv_output);

	return 0;
	}

int read_in_experimental_lc_data (int curve, PHOEBE_data *data, int indep, int dep)
{
	int i;
	int col_type;
	int readout_int;

	int phase, magnitude;

	int status;

	char *readout_str;

	GtkWidget *notice_window;

	/*
	 * If data units mismatch the given indep/dep switches, we need to know pe-
	 * riod and HJD0, that's why we declare this variable, but read the values
	 * in only in case of a mismatch.                                         
	 */

	PHOEBE_main_parameters main_pars;

	/*
	 * Although this isn't really very elegant, somehow we have to know if the
	 * user wants the data to be binned; that's why we read in all switches:    
	 */

	PHOEBE_switches switches = read_in_switches ();

	FILE *data_file;

	/* Initialize everything to 0, so we don't get any accidental appending:  */
	data->ptsno = 0; data->indep = NULL; data->dep = NULL; data->weight = NULL;

	/*
	 * Set the columns variable to hold the number and type of columns in a fi-
	 * le; we do it here and not in the loop so that strcmp gets evaluated only
	 * now and not for each point in the loop.                                 
	 */

	if (strcmp (PHOEBE_lc_data[curve].column3, "Unavailable") == 0)    col_type = 1;
	if (strcmp (PHOEBE_lc_data[curve].column3, "Weight (int)") == 0)   col_type = 2;
	if (strcmp (PHOEBE_lc_data[curve].column3, "Weight (real)") == 0)  col_type = 3;
	if (strcmp (PHOEBE_lc_data[curve].column3, "Absolute error") == 0) col_type = 4;

	/* Do the same for phase and magnitude, just to have everything here:     */
	if (strcmp (PHOEBE_lc_data[curve].column1, "Phase")     == 0) phase = 1;     else phase = 0;
	if (strcmp (PHOEBE_lc_data[curve].column2, "Magnitude") == 0) magnitude = 1; else magnitude = 0;

	if (!file_exists (PHOEBE_lc_data[curve].filename)) {
		notice_window = create_notice_window ("PHOEBE Notice", "Observed data filename not found", "PHOEBE cannot find the file containing observed data.", "Please check your settings in the Data tab.", gtk_widget_destroy);
		data->ptsno = 0;
		return;
	}
		
	data_file = fopen (PHOEBE_lc_data[curve].filename, "r");

	i = 0;
	while (!feof (data_file)) {
		/*
		 * We now read in the whole line (255 characters or less) and parse it:
		 */
		readout_str = phoebe_malloc (255 * sizeof (*readout_str));
		fgets (readout_str, 255, data_file);
		if (feof (data_file)) {
			free (readout_str);
			break;
		}

		/* Strip all comments and spaces; if the line is empty, discard it:   */
		if (parse_input_data (&readout_str) != 0) {
			if (readout_str) printf ("MEMORY CORRUPTION!!!\n");
			continue;
		}

		/*
		 * By this point only real data should have survived the filtering,
		 * so we allocate space for it and read it in:
		 */

		i++; data->ptsno = i;
		allocate_memory_for_data (data);

		if ( col_type == 1 ) {
			status = sscanf (readout_str, "%lf %lf", &data->indep[i-1], &data->dep[i-1]);
			if (status != 2) {
				char notice[255];
				sprintf (notice, "%d. LC data file does not conform to the format specified in the Data tab", curve+1);
				notice_window = create_notice_window ("PHOEBE Notice", "Invalid observed data file format", notice, "and the output will be suppressed. Please verify your file format specifications!", gtk_widget_destroy);
				data->ptsno = 0; free (data->indep); free (data->dep); free (data->weight);
				return -1;
			}
			data->weight[i-1] = 1.0;
		}

		if ( col_type == 2 ) {
			status = sscanf (readout_str, "%lf %lf %d", &(data->indep[i-1]), &(data->dep[i-1]), &readout_int);
			if (status != 3) {
				char notice[255];
				sprintf (notice, "%d. LC data file does not conform to the format specified in the Data tab", curve+1);
				notice_window = create_notice_window ("PHOEBE Notice", "Invalid observed data file format", notice, "and the output will be suppressed. Please verify your file format specifications!", gtk_widget_destroy);
				data->ptsno = 0; free (data->indep); free (data->dep); free (data->weight);
				return -1;
			}
			data->weight[i-1] = (double) readout_int;
		}
		if ( (col_type == 3) || (col_type == 4) ) {
			status = sscanf (readout_str, "%lf %lf %lf", &data->indep[i-1], &data->dep[i-1], &data->weight[i-1]);
			if (status != 3) {
				char notice[255];
				sprintf (notice, "%d. LC data file does not conform to the format specified in the Data tab", curve+1);
				notice_window = create_notice_window ("PHOEBE Notice", "Invalid observed data file format", notice, "and the output will be suppressed. Please verify your file format specifications!", gtk_widget_destroy);
				data->ptsno = 0; free (data->indep); free (data->dep); free (data->weight);
				return -1;
			}
		}
		free (readout_str);
	}

	fclose (data_file);

	if (col_type == 4) transform_absolute_error_to_weight (data);

	/* Synchronize independent variable to match indep switch:                  */
	if ( (indep == 1) && (phase == 1) )
		{
		main_pars = read_in_main_parameters ();
		transform_phase_to_hjd (data, main_pars.HJD0, main_pars.PERIOD);
		}
	if ( (indep == 2) && (phase == 0) )
		{
		main_pars = read_in_main_parameters ();
		transform_hjd_to_phase (data, main_pars.HJD0, main_pars.PERIOD, main_pars.DPDT);
		}

	/* Synchronize dependent variable to match dep switch:                      */
	if ( ( (dep == 5) || (dep == 6) ) && (magnitude == 1) )
		{
		main_pars = read_in_main_parameters ();
		transform_magnitude_to_flux (data, main_pars.MNORM);
		}
	if ( (dep == 8) && (magnitude == 0) )
		{
		main_pars = read_in_main_parameters ();
		transform_flux_to_magnitude (data, main_pars.MNORM);
		}

	/* If the data should be binned, bin it, but only if indep is phase:        */

	if ( (switches.BINNING == 1) && (indep == 2) )
		bin_data (data, switches.BINNO);

	return 0;
	}

int read_in_experimental_rv_data (int curve, PHOEBE_data *data, int indep, int dep, double requested_vunit)
	{
	/* This function reads in experimental radial velocity data from the user-  */
	/* supplied file here denoted with variable curve. Based on indep and dep   */
	/* switches this routine returns the desired values in requested RV units.  */

	int i;
	int col_type;
	int readout_int;

	int phase;

	int input_vunit;    /* The switch that tells PHOEBE what is in input files: */
						/*     0 .. 100km/s                                     */
						/*     1 .. 1km/s                                       */

	int err_no;

	char *readout_str;
	
	GtkWidget *notice_window;

	/* If data units mismatch the given indep/dep switches, we need to know pe- */
	/* riod and HJD0, that's why we declare this variable, but read the values  */
	/* in only in case of a mismatch.                                           */
	PHOEBE_main_parameters main_pars;

	FILE *data_file;

	/* Initialize everything to 0, so we don't get any accidental appending:    */
	data->ptsno = 0; data->indep = NULL; data->dep = NULL; data->weight = NULL;

	/* Set the columns variable to hold the number and type of columns in a fi- */
	/* le; we do it here and not in the loop so that strcmp gets evaluated only */
	/* now and not for each point in the loop.                                  */
	if (strcmp (PHOEBE_rv_data[curve].column3, "Unavailable") == 0)    col_type = 1;
	if (strcmp (PHOEBE_rv_data[curve].column3, "Weight (int)") == 0)   col_type = 2;
	if (strcmp (PHOEBE_rv_data[curve].column3, "Weight (real)") == 0)  col_type = 3;
	if (strcmp (PHOEBE_rv_data[curve].column3, "Absolute error") == 0) col_type = 4;

	/* Do the same for phase and magnitude, just to have everything here:       */
	if (strcmp (PHOEBE_rv_data[curve].column1, "Phase")     == 0)  phase = 1; else phase = 0;
	if (strcmp (PHOEBE_rv_data[curve].column2, "RV in km/s") == 0) input_vunit = 1; else input_vunit = 0;

	if (!file_exists (PHOEBE_rv_data[curve].filename)) {
		notice_window = create_notice_window (
			"PHOEBE Notice",
			"Observed data filename not found",
			"PHOEBE cannot find the file containing observed data.",
			"Please check your settings in the Data tab.",
			gtk_widget_destroy);
		data->ptsno = 0;
		return;
	}
	data_file = fopen (PHOEBE_rv_data[curve].filename, "r");

	i = 0;
	while (!feof (data_file)) {
		/*
		 * We now read in the whole line (255 characters or less) and parse it:
		 */
		readout_str = phoebe_malloc (255 * sizeof (*readout_str));
		fgets (readout_str, 255, data_file);
		if (feof (data_file)) {
			free (readout_str);
			break;
		}

		/* Strip all comments and spaces; if the line is empty, discard it:   */
		if (parse_input_data (&readout_str) != 0) {
			if (readout_str) printf ("MEMORY CORRUPTION!!!\n");
			continue;
		}

		/*
		 * By this point only real data should have survived the filtering,
		 * so we allocate space for it and read it in:
		 */

		i++; data->ptsno = i;
		allocate_memory_for_data (data);

		if ( col_type == 1 ) {
			err_no = sscanf (readout_str, "%lf %lf\n", &data->indep[i-1], &data->dep[i-1]);
			if (err_no != 2) {
				char notice[255];
				sprintf (notice, "%d. RV data file does not conform to the format specified in the Data tab", curve+1);
				notice_window = create_notice_window ("PHOEBE Notice", "Invalid observed data file format", "Observed data file doesn't conform to the format specified in the Data tab", "and the output will be suppressed. Please verify your file format specifications!", gtk_widget_destroy);
				data->ptsno = 0; free (data->indep); free (data->dep); free (data->weight);
				return -1;
			}
			data->weight[i-1] = 1.0;
		}

		if ( col_type == 2 ) {
			err_no = sscanf (readout_str, "%lf %lf %d\n",  &data->indep[i-1], &data->dep[i-1], &readout_int);
			if (err_no != 3) {
				char notice[255];
				sprintf (notice, "%d. LC data file does not conform to the format specified in the Data tab", curve+1);
				notice_window = create_notice_window ("PHOEBE Notice", "Invalid observed data file format", "Observed data file doesn't conform to the format specified in the Data tab", "and the output will be suppressed. Please verify your file format specifications!", gtk_widget_destroy);
				data->ptsno = 0; free (data->indep); free (data->dep); free (data->weight);
				return -1;
			}
			data->weight[i-1] = (double) readout_int;
		}

		if ( (col_type == 3) || (col_type == 4) ) {
			err_no = sscanf (readout_str, "%lf %lf %lf\n", &data->indep[i-1], &data->dep[i-1], &data->weight[i-1]);
			if (err_no != 3) {
				char notice[255];
				sprintf (notice, "%d. LC data file does not conform to the format specified in the Data tab", curve+1);
				notice_window = create_notice_window ("PHOEBE Notice", "Invalid observed data file format", "Observed data file doesn't conform to the format specified in the Data tab", "and the output will be suppressed. Please verify your file format specifications!", gtk_widget_destroy);
				data->ptsno = 0; free (data->indep); free (data->dep); free (data->weight);
				return -1;
			}
		}

		free (readout_str);
	}

	fclose (data_file);

	if (col_type == 4) transform_absolute_error_to_weight (data);

	/* Synchronize independent variable to match indep switch:                  */
	if ( (indep == 1) && (phase == 1) )
		{
		main_pars = read_in_main_parameters ();
		transform_phase_to_hjd (data, main_pars.HJD0, main_pars.PERIOD);
		}
	if ( (indep == 2) && (phase == 0) )
		{
		main_pars = read_in_main_parameters ();
		transform_hjd_to_phase (data, main_pars.HJD0, main_pars.PERIOD, main_pars.DPDT);
		}

	/* Synchronize dependent variable to match indep switch:                    */
	if ( (input_vunit == 0) && (requested_vunit == 1.0) )
		transform_100kms_to_kms (data);
	if ( (input_vunit == 1) && (requested_vunit == 100.0) )
		transform_kms_to_100kms (data);

	if ( (dep == 3) || (dep == 4) )
		{
		main_pars = read_in_main_parameters ();
		normalize_rv_to_orbit (data, main_pars.SMA, main_pars.PERIOD);
		}

	return 0;
	}

int read_in_3d_image_data (char *filename, PHOEBE_data *data)
	{
	FILE *input = fopen (filename, "r");

	char working_string[256];
	char *working_str = working_string;

	sprintf (working_str, "");
	while ( (feof (input) == 0) && (strstr (working_str, "Sky Coordinate") == NULL) )
		fgets (working_str, 255, input);

	data->ptsno = 1;
	data->indep = NULL; data->dep = NULL; data->weight = NULL;
	allocate_memory_for_data (data);

	while (fscanf (input, "%lf %lf\n", &data->indep[data->ptsno-1], &data->dep[data->ptsno-1]) == 2)
		{
		data->ptsno++;
		allocate_memory_for_data (data);
		}

	data->ptsno--;
	fclose (input);
	}

int read_in_data_file_specifics ()
	{
	/*
	 * This function opens all data files and extracts the following info:
	 *
	 * - The number of points,
	 * - The sum of all points,
	 * - The median of all points.
	 */

	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));

	int i;
	int INDEP, DEP;

	double sum, median;

	PHOEBE_data data;

	GtkWidget *data_list = lookup_widget (PHOEBE, "data_files_info_list");
	char working_string[255];
	char *working_str = working_string;

	for (i = 0; i < lc_no; i++) {

		/*
		 * First do some error checking; the default values entered in the list
		 * correspond to the undefined entry, so we just skip all declarations
		 * in here if an error occurs.
		 */

		if (!file_exists (PHOEBE_lc_data[i].filename)) continue;

		if (strcmp (PHOEBE_lc_data[i].column1, "Phase") == 0) INDEP = 2; else INDEP = 1;
		if (strcmp (PHOEBE_lc_data[i].column2, "Magnitude") == 0) DEP = 8; else DEP = 5;

		read_in_experimental_lc_data (i, &data, INDEP, DEP);
		if (data.ptsno != 0) {
			sum    = calculate_sum (data);
			median = calculate_median (data);

			gtk_clist_set_text (GTK_CLIST (data_list), i, 0, PHOEBE_lc_data[i].filter);
			sprintf (working_str, "%d", data.ptsno);
			gtk_clist_set_text (GTK_CLIST (data_list), i, 1, working_str);
			sprintf (working_str, "%5.5lf", sum);
			gtk_clist_set_text (GTK_CLIST (data_list), i, 2, working_str);
			sprintf (working_str, "%5.5lf", median);
			gtk_clist_set_text (GTK_CLIST (data_list), i, 3, working_str);

			data.ptsno = 0; free (data.indep); free (data.dep); free (data.weight);
		}
	}

	for (i = 0; i < rv_no; i++) {
		if (!file_exists (PHOEBE_rv_data[i].filename)) continue;

		if (strcmp (PHOEBE_rv_data[i].column1, "Phase") == 0) INDEP = 2; else INDEP = 1;
		if (strcmp (PHOEBE_rv_data[i].column2, "RV in km/s") == 0) DEP = 7; else DEP = 3;

		read_in_experimental_rv_data (i, &data, INDEP, DEP, 1.0);
		if (data.ptsno != 0) {
			sum    = calculate_sum (data);
			median = calculate_median (data);

			gtk_clist_set_text (GTK_CLIST (data_list), lc_no + i, 0, PHOEBE_rv_data[i].filter);
			sprintf (working_str, "%d", data.ptsno);
			gtk_clist_set_text (GTK_CLIST (data_list), lc_no + i, 1, working_str);
			sprintf (working_str, "%5.5lf", sum);
			gtk_clist_set_text (GTK_CLIST (data_list), lc_no + i, 2, working_str);
			sprintf (working_str, "%5.5lf", median);
			gtk_clist_set_text (GTK_CLIST (data_list), lc_no + i, 3, working_str);

			data.ptsno = 0; free (data.indep); free (data.dep); free (data.weight);
		}
	}

	return 0;
}
