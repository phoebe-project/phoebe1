#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "phoebe_global.h"
#include "phoebe_gui_accessories.h"
#include "phoebe_gui_keyword.h"
#include "phoebe_gui_support.h"

void add_to_keyword_file (const char *keyword, GtkWidget *WIDGET, const char *widget_name, FILE *keyword_file)
	{
	/* This function is a wrapper for saving parameter values to the keyword    */
	/* file by accessing their corresponding widgets.                           */

	GtkWidget *readout_widget;
	int readout_int;
	double readout_double;
	char *readout_str;
	int i, rows;

	readout_widget = lookup_widget (WIDGET, widget_name);

	if (GTK_IS_SPIN_BUTTON (readout_widget))
		{
		/* This means we have a widget with numeric value. Now we have to figure  */
		/* out if it's an integer (0 digits) or a double (more that 0 digits):    */
		if (GTK_SPIN_BUTTON (readout_widget)->digits == 0)
			{
			readout_int = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));
			fprintf (keyword_file, "%-15s = %d\n", keyword, readout_int);
			}
		else
			{
			readout_double = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
			fprintf (keyword_file, "%-15s = %lf\n", keyword, readout_double);
			}
		}
	if ( (GTK_IS_ENTRY (readout_widget)) && (! GTK_IS_SPIN_BUTTON (readout_widget)) )
		{
		/* This means we have an entry. Since GTK_IS_ENTRY returns true for spin- */
		/* buttons as well, we have to test it the way written above.             */
		readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
		fprintf (keyword_file, "%-15s = \"%s\"\n", keyword, readout_str);
		}
	if (GTK_IS_LABEL (readout_widget))
		{
		/* This means we have a label. These widgets are usually some calculated  */
		/* parameter values that the user cannot change.                          */
		gtk_label_get (GTK_LABEL (readout_widget), &readout_str);
		fprintf (keyword_file, "%-15s = \"%s\"\n", keyword, readout_str);
		}
	if (GTK_IS_TOGGLE_BUTTON (readout_widget))
		{
		/* This means we have a toggle button. These are switches.                */
		if (GTK_TOGGLE_BUTTON (readout_widget)->active)
			fprintf (keyword_file, "%-15s = %d\n", keyword, 1);
		else
			fprintf (keyword_file, "%-15s = %d\n", keyword, 0);
		}
	if (GTK_IS_CLIST (readout_widget))
		{
		rows = (GTK_CLIST (readout_widget))->rows;
		for (i = 0; i < rows; i++)
			{
			if (strcmp (keyword, "LC") == 0)
				{
				fprintf (keyword_file, "%sCOL1%d%-8s = \"%s\"\n", keyword, i+1, "", PHOEBE_lc_data[i].column1);
				fprintf (keyword_file, "%sCOL2%d%-8s = \"%s\"\n", keyword, i+1, "", PHOEBE_lc_data[i].column2);
				fprintf (keyword_file, "%sCOL3%d%-8s = \"%s\"\n", keyword, i+1, "", PHOEBE_lc_data[i].column3);
				fprintf (keyword_file, "%sFN%d%-10s = \"%s\"\n",  keyword, i+1, "", PHOEBE_lc_data[i].filename);
				fprintf (keyword_file, "%sSIG%d%-9s = %s\n",      keyword, i+1, "", PHOEBE_lc_data[i].sigma);
				fprintf (keyword_file, "%sFLT%d%-9s = \"%s\"\n",  keyword, i+1, "", PHOEBE_lc_data[i].filter);
				}
			if (strcmp (keyword, "RV") == 0)
				{
				fprintf (keyword_file, "%sCOL1%d%-8s = \"%s\"\n", keyword, i+1, "", PHOEBE_rv_data[i].column1);
				fprintf (keyword_file, "%sCOL2%d%-8s = \"%s\"\n", keyword, i+1, "", PHOEBE_rv_data[i].column2);
				fprintf (keyword_file, "%sCOL3%d%-8s = \"%s\"\n", keyword, i+1, "", PHOEBE_rv_data[i].column3);
				fprintf (keyword_file, "%sFN%d%-10s = \"%s\"\n",  keyword, i+1, "", PHOEBE_rv_data[i].filename);
				fprintf (keyword_file, "%sSIG%d%-9s = %s\n",      keyword, i+1, "", PHOEBE_rv_data[i].sigma);
				fprintf (keyword_file, "%sFLT%d%-9s = \"%s\"\n",  keyword, i+1, "", PHOEBE_rv_data[i].filter);
				}
			if (strcmp (keyword, "LUMLC") == 0)
				{
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 1, &readout_str);
				fprintf (keyword_file, "HLALC%d%-9s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 2, &readout_str);
				fprintf (keyword_file, "CLALC%d%-9s = %s\n", i+1, "", readout_str);
				}
			if (strcmp (keyword, "EL3") == 0)
				{
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 1, &readout_str);
				fprintf (keyword_file, "EL3%d%-11s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 2, &readout_str);
				fprintf (keyword_file, "OPSF%d%-10s = %s\n", i+1, "", readout_str);
				}
			if (strcmp (keyword, "LDLC") == 0)
				{
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 1, &readout_str);
				fprintf (keyword_file, "X1ALC%d%-9s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 2, &readout_str);
				fprintf (keyword_file, "Y1ALC%d%-9s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 3, &readout_str);
				fprintf (keyword_file, "X2ALC%d%-9s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 4, &readout_str);
				fprintf (keyword_file, "Y2ALC%d%-9s = %s\n", i+1, "", readout_str);
				}
			if (strcmp (keyword, "LDRV") == 0)
				{
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 1, &readout_str);
				fprintf (keyword_file, "X1ARV%d%-9s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 2, &readout_str);
				fprintf (keyword_file, "Y1ARV%d%-9s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 3, &readout_str);
				fprintf (keyword_file, "X2ARV%d%-9s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 4, &readout_str);
				fprintf (keyword_file, "Y2ARV%d%-9s = %s\n", i+1, "", readout_str);
				}
			if (strcmp (keyword, "WEIGHTS") == 0)
				{
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 1, &readout_str);
				fprintf (keyword_file, "WEIGHT%d%-8s = \"%s\"\n", i+1, "", readout_str);
				}
			if (strcmp (keyword, "SPOTPRIM") == 0)
				{
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 1, &readout_str);
				fprintf (keyword_file, "XLAT1%d%-9s = %s\n",  i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 2, &readout_str);
				fprintf (keyword_file, "XLONG1%d%-8s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 3, &readout_str);
				fprintf (keyword_file, "RADSP1%d%-8s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 4, &readout_str);
				fprintf (keyword_file, "TEMSP1%d%-8s = %s\n", i+1, "", readout_str);
				}
			if (strcmp (keyword, "SPOTSEC") == 0)
				{
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 1, &readout_str);
				fprintf (keyword_file, "XLAT2%d%-9s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 2, &readout_str);
				fprintf (keyword_file, "XLONG2%d%-8s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 3, &readout_str);
				fprintf (keyword_file, "RADSP2%d%-8s = %s\n", i+1, "", readout_str);
				gtk_clist_get_text (GTK_CLIST (readout_widget), i, 4, &readout_str);
				fprintf (keyword_file, "TEMSP2%d%-8s = %s\n", i+1, "", readout_str);
				}
			}
		}
	}

void get_from_keyword_file (GtkWidget *parent, const char *widget_name, char *value, FILE *keyword_file)
	{
	GtkWidget *readout_widget;

	readout_widget = lookup_widget (parent, widget_name);

	if (GTK_IS_SPIN_BUTTON (readout_widget))
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (value));

	if ( (GTK_IS_ENTRY (readout_widget)) && (! GTK_IS_SPIN_BUTTON (readout_widget)) )
		{
		/* Strings have quotes around them, which we don't want:                  */
		strip_string_tail (value);
		value++;
		gtk_entry_set_text (GTK_ENTRY (readout_widget), value);
		}

	if (GTK_IS_TOGGLE_BUTTON (readout_widget))
		{
		if (atoi (value) == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
		else gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
		}

	if (GTK_IS_CLIST (readout_widget))
		{
		}
	}

void save_keyword_file (char *filename)
	{
	FILE *keyword_file = fopen (filename, "w");

	/* ****************************** DATA TAB ******************************** */

	add_to_keyword_file ("NAME",        PHOEBE, "data_star_name_entry", keyword_file);
	add_to_keyword_file ("MODEL",       PHOEBE, "data_model_list_entry", keyword_file);
	add_to_keyword_file ("LCNO",        PHOEBE, "data_lc_no_value", keyword_file);
	add_to_keyword_file ("RVNO",        PHOEBE, "data_rv_no_value", keyword_file);
	add_to_keyword_file ("SPECNO",      PHOEBE, "data_spectra_no_value", keyword_file);
	add_to_keyword_file ("MNORM",       PHOEBE, "data_zero_magnitude_value", keyword_file);
	add_to_keyword_file ("BINNING",     PHOEBE, "data_binning_switch", keyword_file);
	add_to_keyword_file ("BINVAL",      PHOEBE, "data_binning_value", keyword_file);
	add_to_keyword_file ("LC",          PHOEBE, "data_lc_info_list", keyword_file);
	add_to_keyword_file ("RV",          PHOEBE, "data_rv_info_list", keyword_file);
	add_to_keyword_file ("REDDENING",   PHOEBE_assign_data_file, "data_file_reddening_switch", keyword_file);
	add_to_keyword_file ("REDDENING_R", PHOEBE_assign_data_file, "data_file_r_value", keyword_file);
	add_to_keyword_file ("REDDENING_E", PHOEBE_assign_data_file, "data_file_color_excess_value", keyword_file);
	add_to_keyword_file ("THE_VAL",     PHOEBE, "data_the_value", keyword_file);

	/* ************************** SYSTEM-RELATED TAB ************************** */

	add_to_keyword_file ("HJD0",        PHOEBE, "system_hjd0_value", keyword_file);
	add_to_keyword_file ("HJD0_ADJ",    PHOEBE, "system_hjd0_adjust", keyword_file);
	add_to_keyword_file ("HJD0_DEL",    PHOEBE, "system_hjd0_step_value", keyword_file);
	add_to_keyword_file ("HJD0_MIN",    PHOEBE, "system_hjd0_min_value", keyword_file);
	add_to_keyword_file ("HJD0_MAX",    PHOEBE, "system_hjd0_max_value", keyword_file);
	add_to_keyword_file ("PERIOD",      PHOEBE, "system_period_value", keyword_file);
	add_to_keyword_file ("PERIOD_ADJ",  PHOEBE, "system_period_adjust", keyword_file);
	add_to_keyword_file ("PERIOD_DEL",  PHOEBE, "system_period_step_value", keyword_file);
	add_to_keyword_file ("PERIOD_MIN",  PHOEBE, "system_period_min_value", keyword_file);
	add_to_keyword_file ("PERIOD_MAX",  PHOEBE, "system_period_max_value", keyword_file);
	add_to_keyword_file ("DPDT",        PHOEBE, "system_dpdt_value", keyword_file);
	add_to_keyword_file ("DPDT_ADJ",    PHOEBE, "system_dpdt_adjust", keyword_file);
	add_to_keyword_file ("DPDT_DEL",    PHOEBE, "system_dpdt_step_value", keyword_file);
	add_to_keyword_file ("DPDT_MIN",    PHOEBE, "system_dpdt_min_value", keyword_file);
	add_to_keyword_file ("DPDT_MAX",    PHOEBE, "system_dpdt_max_value", keyword_file);
	add_to_keyword_file ("PSHIFT",      PHOEBE, "system_pshift_value", keyword_file);
	add_to_keyword_file ("PSHIFT_ADJ",  PHOEBE, "system_pshift_adjust", keyword_file);
	add_to_keyword_file ("PSHIFT_DEL",  PHOEBE, "system_pshift_step_value", keyword_file);
	add_to_keyword_file ("PSHIFT_MIN",  PHOEBE, "system_pshift_min_value", keyword_file);
	add_to_keyword_file ("PSHIFT_MAX",  PHOEBE, "system_pshift_max_value", keyword_file);
	add_to_keyword_file ("SMA",         PHOEBE, "system_sma_value", keyword_file);
	add_to_keyword_file ("SMA_ADJ",     PHOEBE, "system_sma_adjust", keyword_file);
	add_to_keyword_file ("SMA_DEL",     PHOEBE, "system_sma_step_value", keyword_file);
	add_to_keyword_file ("SMA_MIN",     PHOEBE, "system_sma_min_value", keyword_file);
	add_to_keyword_file ("SMA_MAX",     PHOEBE, "system_sma_max_value", keyword_file);
	add_to_keyword_file ("RM",          PHOEBE, "system_rm_value", keyword_file);
	add_to_keyword_file ("RM_ADJ",      PHOEBE, "system_rm_adjust", keyword_file);
	add_to_keyword_file ("RM_DEL",      PHOEBE, "system_rm_step_value", keyword_file);
	add_to_keyword_file ("RM_MIN",      PHOEBE, "system_rm_min_value", keyword_file);
	add_to_keyword_file ("RM_MAX",      PHOEBE, "system_rm_max_value", keyword_file);
	add_to_keyword_file ("INCL",        PHOEBE, "system_incl_value", keyword_file);
	add_to_keyword_file ("INCL_ADJ",    PHOEBE, "system_incl_adjust", keyword_file);
	add_to_keyword_file ("INCL_DEL",    PHOEBE, "system_incl_step_value", keyword_file);
	add_to_keyword_file ("INCL_MIN",    PHOEBE, "system_incl_min_value", keyword_file);
	add_to_keyword_file ("INCL_MAX",    PHOEBE, "system_incl_max_value", keyword_file);
	add_to_keyword_file ("VGA",         PHOEBE, "system_vga_value", keyword_file);
	add_to_keyword_file ("VGA_ADJ",     PHOEBE, "system_vga_adjust", keyword_file);
	add_to_keyword_file ("VGA_DEL",     PHOEBE, "system_vga_step_value", keyword_file);
	add_to_keyword_file ("VGA_MIN",     PHOEBE, "system_vga_min_value", keyword_file);
	add_to_keyword_file ("VGA_MAX",     PHOEBE, "system_vga_max_value", keyword_file);

	/* ************************* COMPONENT-RELATED TAB ************************ */

	add_to_keyword_file ("TAVH",        PHOEBE, "component_tavh_value", keyword_file);
	add_to_keyword_file ("TAVH_ADJ",    PHOEBE, "component_tavh_adjust", keyword_file);
	add_to_keyword_file ("TAVH_DEL",    PHOEBE, "component_tavh_del_value", keyword_file);
	add_to_keyword_file ("TAVH_MIN",    PHOEBE, "component_tavh_value_min", keyword_file);
	add_to_keyword_file ("TAVH_MAX",    PHOEBE, "component_tavh_value_max", keyword_file);
	add_to_keyword_file ("TAVC",        PHOEBE, "component_tavc_value", keyword_file);
	add_to_keyword_file ("TAVC_ADJ",    PHOEBE, "component_tavc_adjust", keyword_file);
	add_to_keyword_file ("TAVC_DEL",    PHOEBE, "component_tavc_del_value", keyword_file);
	add_to_keyword_file ("TAVC_MIN",    PHOEBE, "component_tavc_value_min", keyword_file);
	add_to_keyword_file ("TAVC_MAX",    PHOEBE, "component_tavc_value_max", keyword_file);
	add_to_keyword_file ("PHSV",        PHOEBE, "component_phsv_value", keyword_file);
	add_to_keyword_file ("PHSV_ADJ",    PHOEBE, "component_phsv_adjust", keyword_file);
	add_to_keyword_file ("PHSV_DEL",    PHOEBE, "component_phsv_del_value", keyword_file);
	add_to_keyword_file ("PHSV_MIN",    PHOEBE, "component_phsv_value_min", keyword_file);
	add_to_keyword_file ("PHSV_MAX",    PHOEBE, "component_phsv_value_max", keyword_file);
	add_to_keyword_file ("PCSV",        PHOEBE, "component_pcsv_value", keyword_file);
	add_to_keyword_file ("PCSV_ADJ",    PHOEBE, "component_pcsv_adjust", keyword_file);
	add_to_keyword_file ("PCSV_DEL",    PHOEBE, "component_pcsv_del_value", keyword_file);
	add_to_keyword_file ("PCSV_MIN",    PHOEBE, "component_pcsv_value_min", keyword_file);
	add_to_keyword_file ("PCSV_MAX",    PHOEBE, "component_pcsv_value_max", keyword_file);
	add_to_keyword_file ("LOGG1",       PHOEBE, "component_logg1_value", keyword_file);
	add_to_keyword_file ("LOGG1_ADJ",   PHOEBE, "component_logg1_adjust", keyword_file);
	add_to_keyword_file ("LOGG1_DEL",   PHOEBE, "component_logg1_step_value", keyword_file);
	add_to_keyword_file ("LOGG1_MIN",   PHOEBE, "component_logg1_value_min", keyword_file);
	add_to_keyword_file ("LOGG1_MAX",   PHOEBE, "component_logg1_value_max", keyword_file);
	add_to_keyword_file ("LOGG2",       PHOEBE, "component_logg2_value", keyword_file);
	add_to_keyword_file ("LOGG2_ADJ",   PHOEBE, "component_logg2_adjust", keyword_file);
	add_to_keyword_file ("LOGG2_DEL",   PHOEBE, "component_logg2_step_value", keyword_file);
	add_to_keyword_file ("LOGG2_MIN",   PHOEBE, "component_logg2_value_min", keyword_file);
	add_to_keyword_file ("LOGG2_MAX",   PHOEBE, "component_logg2_value_max", keyword_file);
	add_to_keyword_file ("MET1",        PHOEBE, "component_met1_value", keyword_file);
	add_to_keyword_file ("MET1_ADJ",    PHOEBE, "component_met1_adjust", keyword_file);
	add_to_keyword_file ("MET1_DEL",    PHOEBE, "component_met1_step_value", keyword_file);
	add_to_keyword_file ("MET1_MIN",    PHOEBE, "component_met1_value_min", keyword_file);
	add_to_keyword_file ("MET1_MAX",    PHOEBE, "component_met1_value_max", keyword_file);
	add_to_keyword_file ("MET2",        PHOEBE, "component_met2_value", keyword_file);
	add_to_keyword_file ("MET2_ADJ",    PHOEBE, "component_met2_adjust", keyword_file);
	add_to_keyword_file ("MET2_DEL",    PHOEBE, "component_met2_step_value", keyword_file);
	add_to_keyword_file ("MET2_MIN",    PHOEBE, "component_met2_value_min", keyword_file);
	add_to_keyword_file ("MET2_MAX",    PHOEBE, "component_met2_value_max", keyword_file);

	/* ***************************** ORBIT TAB ******************************** */

	add_to_keyword_file ("E",           PHOEBE, "orbit_e_value", keyword_file);
	add_to_keyword_file ("E_ADJ",       PHOEBE, "orbit_e_adjust", keyword_file);
	add_to_keyword_file ("E_DEL",       PHOEBE, "orbit_e_del_value", keyword_file);
	add_to_keyword_file ("E_MIN",       PHOEBE, "orbit_e_value_min", keyword_file);
	add_to_keyword_file ("E_MAX",       PHOEBE, "orbit_e_value_max", keyword_file);
	add_to_keyword_file ("PERR0",       PHOEBE, "orbit_perr0_value", keyword_file);
	add_to_keyword_file ("PERR0_ADJ",   PHOEBE, "orbit_perr0_adjust", keyword_file);
	add_to_keyword_file ("PERR0_DEL",   PHOEBE, "orbit_perr0_del_value", keyword_file);
	add_to_keyword_file ("PERR0_MIN",   PHOEBE, "orbit_perr0_value_min", keyword_file);
	add_to_keyword_file ("PERR0_MAX",   PHOEBE, "orbit_perr0_value_max", keyword_file);
	add_to_keyword_file ("DPERDT",      PHOEBE, "orbit_dperdt_value", keyword_file);
	add_to_keyword_file ("DPERDT_ADJ",  PHOEBE, "orbit_dperdt_adjust", keyword_file);
	add_to_keyword_file ("DPERDT_DEL",  PHOEBE, "orbit_dperdt_del_value", keyword_file);
	add_to_keyword_file ("DPERDT_MIN",  PHOEBE, "orbit_dperdt_value_min", keyword_file);
	add_to_keyword_file ("DPERDT_MAX",  PHOEBE, "orbit_dperdt_value_max", keyword_file);
	add_to_keyword_file ("F1",          PHOEBE, "orbit_f1_value", keyword_file);
	add_to_keyword_file ("F1_ADJ",      PHOEBE, "orbit_f1_adjust", keyword_file);
	add_to_keyword_file ("F1_DEL",      PHOEBE, "orbit_f1_del_value", keyword_file);
	add_to_keyword_file ("F1_MIN",      PHOEBE, "orbit_f1_value_min", keyword_file);
	add_to_keyword_file ("F1_MAX",      PHOEBE, "orbit_f1_value_max", keyword_file);
	add_to_keyword_file ("F2",          PHOEBE, "orbit_f2_value", keyword_file);
	add_to_keyword_file ("F2_ADJ",      PHOEBE, "orbit_f2_adjust", keyword_file);
	add_to_keyword_file ("F2_DEL",      PHOEBE, "orbit_f2_del_value", keyword_file);
	add_to_keyword_file ("F2_MIN",      PHOEBE, "orbit_f2_value_min", keyword_file);
	add_to_keyword_file ("F2_MAX",      PHOEBE, "orbit_f2_value_max", keyword_file);

	/* ************************** LUMINOSITIES TAB **************************** */

	add_to_keyword_file ("LUMLC",       PHOEBE, "luminosities_lc_info_list", keyword_file);
	add_to_keyword_file ("EL3",         PHOEBE, "luminosities_el3_info_list", keyword_file);
	add_to_keyword_file ("EL3_FLUX",    PHOEBE, "luminosities_el3_flux_switch", keyword_file);
	add_to_keyword_file ("WEIGHTS",     PHOEBE, "luminosities_weighting_info_list", keyword_file);
	add_to_keyword_file ("HLA_ADJ",     PHOEBE, "luminosities_hla_adjust", keyword_file);
	add_to_keyword_file ("HLA_DEL",     PHOEBE, "luminosities_hla_del_value", keyword_file);
	add_to_keyword_file ("CLA_ADJ",     PHOEBE, "luminosities_cla_adjust", keyword_file);
	add_to_keyword_file ("CLA_DEL",     PHOEBE, "luminosities_cla_del_value", keyword_file);
	add_to_keyword_file ("EL3_ADJ",     PHOEBE, "luminosities_el3_adjust", keyword_file);
	add_to_keyword_file ("IPB_ON",      PHOEBE, "luminosities_ipb_switch", keyword_file);
	add_to_keyword_file ("NREF_ON",     PHOEBE, "luminosities_nref_switch", keyword_file);
	add_to_keyword_file ("NREF_VAL",    PHOEBE, "luminosities_nref_value", keyword_file);
	add_to_keyword_file ("IFAT1_ON",    PHOEBE, "luminosities_ifat1_switch", keyword_file);
	add_to_keyword_file ("IFAT2_ON",    PHOEBE, "luminosities_ifat2_switch", keyword_file);
	add_to_keyword_file ("MODELLGG_ON", PHOEBE, "luminosities_logg_from_model_switch", keyword_file);
	add_to_keyword_file ("NOISE_ON",    PHOEBE, "luminosities_noise_switch", keyword_file);
	add_to_keyword_file ("NOISE_TYPE",  PHOEBE, "luminosities_noise_list_entry", keyword_file);
	add_to_keyword_file ("NOISE_VAL",   PHOEBE, "luminosities_noise_value", keyword_file);
	add_to_keyword_file ("SEED_VAL",    PHOEBE, "luminosities_seed_value", keyword_file);
	add_to_keyword_file ("ICOR1_ON",    PHOEBE, "luminosities_icor1_switch", keyword_file);
	add_to_keyword_file ("ICOR2_ON",    PHOEBE, "luminosities_icor2_switch", keyword_file);

	/* ******************************* LD TAB ********************************* */

	add_to_keyword_file ("LD",          PHOEBE, "ld_ld_law_combo_box_entry", keyword_file);
	add_to_keyword_file ("XBOL1",       PHOEBE, "ld_xbol1_value", keyword_file);
	add_to_keyword_file ("XBOL2",       PHOEBE, "ld_xbol2_value", keyword_file);
	add_to_keyword_file ("YBOL1",       PHOEBE, "ld_ybol1_value", keyword_file);
	add_to_keyword_file ("YBOL2",       PHOEBE, "ld_ybol2_value", keyword_file);
	add_to_keyword_file ("LDLC",        PHOEBE, "ld_monochromatic_lc_info_list", keyword_file);
	add_to_keyword_file ("LDRV",        PHOEBE, "ld_monochromatic_rv_info_list", keyword_file);
	add_to_keyword_file ("X1A_DEL",     PHOEBE, "ld_x1a_del_value", keyword_file);
	add_to_keyword_file ("X2A_DEL",     PHOEBE, "ld_x2a_del_value", keyword_file);
	add_to_keyword_file ("X1A_ADJ",     PHOEBE, "ld_x1a_adjust", keyword_file);
	add_to_keyword_file ("X2A_ADJ",     PHOEBE, "ld_x2a_adjust", keyword_file);

	/* ***************************** SURFACE TAB ****************************** */

	add_to_keyword_file ("ALB1",        PHOEBE, "surface_alb1_value", keyword_file);
	add_to_keyword_file ("ALB1_ADJ",    PHOEBE, "surface_alb1_adjust", keyword_file);
	add_to_keyword_file ("ALB1_DEL",    PHOEBE, "surface_alb1_del_value", keyword_file);
	add_to_keyword_file ("ALB1_MIN",    PHOEBE, "surface_alb1_value_min", keyword_file);
	add_to_keyword_file ("ALB1_MAX",    PHOEBE, "surface_alb1_value_max", keyword_file);
	add_to_keyword_file ("ALB2",        PHOEBE, "surface_alb2_value", keyword_file);
	add_to_keyword_file ("ALB2_ADJ",    PHOEBE, "surface_alb2_adjust", keyword_file);
	add_to_keyword_file ("ALB2_DEL",    PHOEBE, "surface_alb2_del_value", keyword_file);
	add_to_keyword_file ("ALB2_MIN",    PHOEBE, "surface_alb2_value_min", keyword_file);
	add_to_keyword_file ("ALB2_MAX",    PHOEBE, "surface_alb2_value_max", keyword_file);
	add_to_keyword_file ("GR1",         PHOEBE, "surface_gr1_value", keyword_file);
	add_to_keyword_file ("GR1_ADJ",     PHOEBE, "surface_gr1_adjust", keyword_file);
	add_to_keyword_file ("GR1_DEL",     PHOEBE, "surface_gr1_del_value", keyword_file);
	add_to_keyword_file ("GR1_MIN",     PHOEBE, "surface_gr1_value_min", keyword_file);
	add_to_keyword_file ("GR1_MAX",     PHOEBE, "surface_gr1_value_max", keyword_file);
	add_to_keyword_file ("GR2",         PHOEBE, "surface_gr2_value", keyword_file);
	add_to_keyword_file ("GR2_ADJ",     PHOEBE, "surface_gr2_adjust", keyword_file);
	add_to_keyword_file ("GR2_DEL",     PHOEBE, "surface_gr2_del_value", keyword_file);
	add_to_keyword_file ("GR2_MIN",     PHOEBE, "surface_gr2_value_min", keyword_file);
	add_to_keyword_file ("GR2_MAX",     PHOEBE, "surface_gr2_value_max", keyword_file);
	add_to_keyword_file ("NSPOTSPRIM",  PHOEBE, "spots_sprim_value", keyword_file);
	add_to_keyword_file ("NSPOTSSEC",   PHOEBE, "spots_ssec_value", keyword_file);
	add_to_keyword_file ("SPOTPRIM",    PHOEBE, "spots_primary_info_list", keyword_file);
	add_to_keyword_file ("SPOTSEC",     PHOEBE, "spots_secondary_info_list", keyword_file);
	add_to_keyword_file ("SPOT1_ADJ",   PHOEBE, "spots_spot_1_adjust", keyword_file);
	add_to_keyword_file ("SPOT2_ADJ",   PHOEBE, "spots_spot_2_adjust", keyword_file);
	add_to_keyword_file ("XLAT1_ADJ",   PHOEBE, "spots_xlat1_adjust", keyword_file);
	add_to_keyword_file ("XLONG1_ADJ",  PHOEBE, "spots_xlong1_adjust", keyword_file);
	add_to_keyword_file ("RADSP1_ADJ",  PHOEBE, "spots_radsp1_adjust", keyword_file);
	add_to_keyword_file ("TEMSP1_ADJ",  PHOEBE, "spots_temsp1_adjust", keyword_file);
	add_to_keyword_file ("XLAT2_ADJ",   PHOEBE, "spots_xlat2_adjust", keyword_file);
	add_to_keyword_file ("XLONG2_ADJ",  PHOEBE, "spots_xlong2_adjust", keyword_file);
	add_to_keyword_file ("RADSP2_ADJ",  PHOEBE, "spots_radsp2_adjust", keyword_file);
	add_to_keyword_file ("TEMSP2_ADJ",  PHOEBE, "spots_temsp2_adjust", keyword_file);
	add_to_keyword_file ("XLAT1_DEL",   PHOEBE_fitting_quickbar, "fitting_quickbar_latsp1_step_value", keyword_file);
	add_to_keyword_file ("XLONG1_DEL",  PHOEBE_fitting_quickbar, "fitting_quickbar_longsp1_step_value", keyword_file);
	add_to_keyword_file ("RADSP1_DEL",  PHOEBE_fitting_quickbar, "fitting_quickbar_radsp1_step_value", keyword_file);
	add_to_keyword_file ("TEMSP1_DEL",  PHOEBE_fitting_quickbar, "fitting_quickbar_temsp1_step_value", keyword_file);
	add_to_keyword_file ("XLAT2_DEL",   PHOEBE_fitting_quickbar, "fitting_quickbar_latsp2_step_value", keyword_file);
	add_to_keyword_file ("XLONG2_DEL",  PHOEBE_fitting_quickbar, "fitting_quickbar_longsp2_step_value", keyword_file);
	add_to_keyword_file ("RADSP2_DEL",  PHOEBE_fitting_quickbar, "fitting_quickbar_radsp2_step_value", keyword_file);
	add_to_keyword_file ("TEMSP2_DEL",  PHOEBE_fitting_quickbar, "fitting_quickbar_temsp2_step_value", keyword_file);

	/* **************************** FITTING TAB ******************************* */

	add_to_keyword_file ("N1_VAL",      PHOEBE, "fitting_n1_value", keyword_file);
	add_to_keyword_file ("N2_VAL",      PHOEBE, "fitting_n2_value", keyword_file);
	add_to_keyword_file ("N1L_VAL",     PHOEBE, "fitting_n1l_value", keyword_file);
	add_to_keyword_file ("N2L_VAL",     PHOEBE, "fitting_n2l_value", keyword_file);
	add_to_keyword_file ("XLAMDA_VAL",  PHOEBE, "fitting_xlamda_value", keyword_file);
	add_to_keyword_file ("ISYM_ON",     PHOEBE, "fitting_isym_switch", keyword_file);
	add_to_keyword_file ("JDPHS_TIME",  PHOEBE, "fitting_independent_variable_times_switch", keyword_file);

	/* ************************** LC PLOTTING WINDOW ************************** */

	add_to_keyword_file ("LC_PHSTRT",   PHOEBE_plot_lc, "plot_lc_phstrt_value", keyword_file);
	add_to_keyword_file ("LC_PHEND",    PHOEBE_plot_lc, "plot_lc_phend_value", keyword_file);
	add_to_keyword_file ("LC_VERTICES", PHOEBE_plot_lc, "plot_lc_vertexes_value", keyword_file);
	add_to_keyword_file ("LC_INDEP",    PHOEBE_plot_lc, "plot_lc_independent_combo_box_entry", keyword_file);
	add_to_keyword_file ("LC_DEP",      PHOEBE_plot_lc, "plot_lc_dependent_combo_box_entry", keyword_file);
	add_to_keyword_file ("PHNORM_VAL",  PHOEBE_plot_lc, "plot_lc_phnorm_value", keyword_file);
	add_to_keyword_file ("FACTOR_VAL",  PHOEBE_plot_lc, "plot_lc_factor_value", keyword_file);

	/* ************************** RV PLOTTING WINDOW ************************** */

	add_to_keyword_file ("RV_PHSTRT",   PHOEBE_plot_rv, "plot_rv_phstrt_value", keyword_file);
	add_to_keyword_file ("RV_PHEND",    PHOEBE_plot_rv, "plot_rv_phend_value", keyword_file);
	add_to_keyword_file ("RV_VERTICES", PHOEBE_plot_rv, "plot_rv_vertexes_value", keyword_file);
	add_to_keyword_file ("RV_INDEP",    PHOEBE_plot_rv, "plot_rv_independent_combo_box_entry", keyword_file);
	add_to_keyword_file ("RV_DEP",      PHOEBE_plot_rv, "plot_rv_dependent_combo_box_entry", keyword_file);

	fclose (keyword_file);
	}

void open_keyword_file (const char *filename)
	{
	GtkWidget *notice_window = NULL;

	char readout_string[255];
	char *readout_str = readout_string;

	char keyword_string[255];
	char *keyword_str = keyword_string;

	char value_string[255];
	char *value_str = value_string;

	char working_string[255];
	char *working_str = working_string;

	int readout_int;

	FILE *keyword_file;
	
	keyword_file = fopen (filename, "r");

	while (!feof (keyword_file))
		{
		fgets (readout_str, 255, keyword_file);
		if (feof (keyword_file) != 0) break;
		if (*readout_str == '\n') continue;

		/* fgets reads a newline character, which we don't want really:           */
		strip_string_tail (readout_str);
		
		/* Let us check if the keyword file is an old PHOEBE keyword file:        */
		if (strchr (readout_str, '=') == NULL)
			{
			/* Yep, this is a legacy PHOEBE file. Print out a warning and call the  */
			/* legacy function to open it.                                          */
			notice_window = create_notice_window (
				"Notice",
				"Opening legacy PHOEBE keyword file format",
			  "PHOEBE keywords have changed in version 0.2. Although your file will be",
				"opened, please save your keyword file to convert it to the current format.",
			gtk_widget_destroy);
			fclose (keyword_file);
			open_legacy_keyword_file (filename);
			return;
			}

		sscanf (readout_str, "%s = %*s", keyword_str);
		value_str = strchr (readout_str, '=');
		if (value_str == NULL)
			{
			/* If the keyword doesn't have '=', it will be skipped.                 */
			sprintf (working_str, "keyword %s in file %s invalid.", keyword_str, filename);
			phoebe_warning (working_str);
			continue;
			}
		/* value_str now points to '=', we need the next character:               */
		value_str++;

		/* Eat all empty spaces at the beginning:                                 */
		while (value_str[0] == ' ') value_str++;

		/* ***************************** DATA TAB ******************************* */

		if (strcmp (keyword_str, "NAME")        == 0) get_from_keyword_file (PHOEBE, "data_star_name_entry", value_str, keyword_file);
		if (strcmp (keyword_str, "MODEL")       == 0) get_from_keyword_file (PHOEBE, "data_model_list_entry", value_str, keyword_file);
		if (strcmp (keyword_str, "LCNO")        == 0) get_from_keyword_file (PHOEBE, "data_lc_no_value", value_str, keyword_file);
		if (strcmp (keyword_str, "RVNO")        == 0) get_from_keyword_file (PHOEBE, "data_rv_no_value", value_str, keyword_file);
		if (strcmp (keyword_str, "SPECNO")      == 0) get_from_keyword_file (PHOEBE, "data_spectra_no_value", value_str, keyword_file);
		if (strcmp (keyword_str, "MNORM")       == 0) get_from_keyword_file (PHOEBE, "data_zero_magnitude_value", value_str, keyword_file);
		if (strcmp (keyword_str, "BINNING")     == 0) get_from_keyword_file (PHOEBE, "data_binning_switch", value_str, keyword_file);
		if (strcmp (keyword_str, "BINVAL")      == 0) get_from_keyword_file (PHOEBE, "data_binning_value", value_str, keyword_file);
		if (strcmp (keyword_str, "REDDENING")   == 0) get_from_keyword_file (PHOEBE_assign_data_file, "data_file_reddening_switch", value_str, keyword_file);
		if (strcmp (keyword_str, "REDDENING_R") == 0) get_from_keyword_file (PHOEBE_assign_data_file, "data_file_r_value", value_str, keyword_file);
		if (strcmp (keyword_str, "REDDENING_E") == 0) get_from_keyword_file (PHOEBE_assign_data_file, "data_file_color_excess_value", value_str, keyword_file);
		if (strcmp (keyword_str, "THE_VAL")     == 0) get_from_keyword_file (PHOEBE, "data_the_value", value_str, keyword_file);

		if (strncmp (keyword_str, "LCCOL1", 6) == 0)
			{
			sscanf (keyword_str, "LCCOL1%d", &readout_int);
			strip_string_tail (value_str); value_str++;
			sprintf (PHOEBE_lc_data[readout_int-1].column1, "%s", value_str);
			}

		if (strncmp (keyword_str, "LCCOL2", 6) == 0)
			{
			sscanf (keyword_str, "LCCOL2%d", &readout_int);
			strip_string_tail (value_str); value_str++;
			sprintf (PHOEBE_lc_data[readout_int-1].column2, "%s", value_str);
			}

		if (strncmp (keyword_str, "LCCOL3", 6) == 0)
			{
			sscanf (keyword_str, "LCCOL3%d", &readout_int);
			strip_string_tail (value_str); value_str++;
			sprintf (PHOEBE_lc_data[readout_int-1].column3, "%s", value_str);
			}

		if (strncmp (keyword_str, "LCFN", 4) == 0)
			{
			sscanf (keyword_str, "LCFN%d", &readout_int);
			strip_string_tail (value_str); value_str++;
			sprintf (PHOEBE_lc_data[readout_int-1].filename, "%s", value_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list")), readout_int-1, 1, value_str);
			}

		if (strncmp (keyword_str, "LCSIG", 5) == 0)
			{
			sscanf (keyword_str, "LCSIG%d", &readout_int);
			sprintf (PHOEBE_lc_data[readout_int-1].sigma, "%s", value_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list")), readout_int-1, 2, value_str);
			}

		if (strncmp (keyword_str, "LCFLT", 5) == 0)
			{
			sscanf (keyword_str, "LCFLT%d", &readout_int);
			strip_string_tail (value_str); value_str++;
			sprintf (PHOEBE_lc_data[readout_int-1].filter, "%s", value_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list")), readout_int-1, 3, value_str);
			}

		if (strncmp (keyword_str, "RVCOL1", 6) == 0)
			{
			sscanf (keyword_str, "RVCOL1%d", &readout_int);
			strip_string_tail (value_str); value_str++;
			sprintf (PHOEBE_rv_data[readout_int-1].column1, "%s", value_str);
			}

		if (strncmp (keyword_str, "RVCOL2", 6) == 0)
			{
			sscanf (keyword_str, "RVCOL2%d", &readout_int);
			strip_string_tail (value_str); value_str++;
			sprintf (PHOEBE_rv_data[readout_int-1].column2, "%s", value_str);
			}

		if (strncmp (keyword_str, "RVCOL3", 6) == 0)
			{
			sscanf (keyword_str, "RVCOL3%d", &readout_int);
			strip_string_tail (value_str); value_str++;
			sprintf (PHOEBE_rv_data[readout_int-1].column3, "%s", value_str);
			}

		if (strncmp (keyword_str, "RVFN", 4) == 0)
			{
			sscanf (keyword_str, "RVFN%d", &readout_int);
			strip_string_tail (value_str); value_str++;
			sprintf (PHOEBE_rv_data[readout_int-1].filename, "%s", value_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list")), readout_int-1, 1, value_str);
			}

		if (strncmp (keyword_str, "RVSIG", 5) == 0)
			{
			sscanf (keyword_str, "RVSIG%d", &readout_int);
			sprintf (PHOEBE_rv_data[readout_int-1].sigma, "%s", value_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list")), readout_int-1, 2, value_str);
			}

		if (strncmp (keyword_str, "RVFLT", 5) == 0)
			{
			sscanf (keyword_str, "RVFLT%d", &readout_int);
			strip_string_tail (value_str); value_str++;
			sprintf (PHOEBE_rv_data[readout_int-1].filter, "%s", value_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list")), readout_int-1, 3, value_str);
			}

		/* ************************* SYSTEM-RELATED TAB ************************* */

		if (strcmp (keyword_str, "HJD0")        == 0) get_from_keyword_file (PHOEBE, "system_hjd0_value", value_str, keyword_file);
		if (strcmp (keyword_str, "HJD0_ADJ")    == 0) get_from_keyword_file (PHOEBE, "system_hjd0_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "HJD0_DEL")    == 0) get_from_keyword_file (PHOEBE, "system_hjd0_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "HJD0_MIN")    == 0) get_from_keyword_file (PHOEBE, "system_hjd0_min_value", value_str, keyword_file);
		if (strcmp (keyword_str, "HJD0_MAX")    == 0) get_from_keyword_file (PHOEBE, "system_hjd0_max_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PERIOD")      == 0) get_from_keyword_file (PHOEBE, "system_period_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PERIOD_ADJ")  == 0) get_from_keyword_file (PHOEBE, "system_period_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "PERIOD_DEL")  == 0) get_from_keyword_file (PHOEBE, "system_period_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PERIOD_MIN")  == 0) get_from_keyword_file (PHOEBE, "system_period_min_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PERIOD_MAX")  == 0) get_from_keyword_file (PHOEBE, "system_period_max_value", value_str, keyword_file);
		if (strcmp (keyword_str, "DPDT")        == 0) get_from_keyword_file (PHOEBE, "system_dpdt_value", value_str, keyword_file);
		if (strcmp (keyword_str, "DPDT_ADJ")    == 0) get_from_keyword_file (PHOEBE, "system_dpdt_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "DPDT_DEL")    == 0) get_from_keyword_file (PHOEBE, "system_dpdt_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "DPDT_MIN")    == 0) get_from_keyword_file (PHOEBE, "system_dpdt_min_value", value_str, keyword_file);
		if (strcmp (keyword_str, "DPDT_MAX")    == 0) get_from_keyword_file (PHOEBE, "system_dpdt_max_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PSHIFT")      == 0) get_from_keyword_file (PHOEBE, "system_pshift_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PSHIFT_ADJ")  == 0) get_from_keyword_file (PHOEBE, "system_pshift_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "PSHIFT_DEL")  == 0) get_from_keyword_file (PHOEBE, "system_pshift_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PSHIFT_MIN")  == 0) get_from_keyword_file (PHOEBE, "system_pshift_min_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PSHIFT_MAX")  == 0) get_from_keyword_file (PHOEBE, "system_pshift_max_value", value_str, keyword_file);
		if (strcmp (keyword_str, "SMA")         == 0) get_from_keyword_file (PHOEBE, "system_sma_value", value_str, keyword_file);
		if (strcmp (keyword_str, "SMA_ADJ")     == 0) get_from_keyword_file (PHOEBE, "system_sma_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "SMA_DEL")     == 0) get_from_keyword_file (PHOEBE, "system_sma_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "SMA_MIN")     == 0) get_from_keyword_file (PHOEBE, "system_sma_min_value", value_str, keyword_file);
		if (strcmp (keyword_str, "SMA_MAX")     == 0) get_from_keyword_file (PHOEBE, "system_sma_max_value", value_str, keyword_file);
		if (strcmp (keyword_str, "RM")          == 0) get_from_keyword_file (PHOEBE, "system_rm_value", value_str, keyword_file);
		if (strcmp (keyword_str, "RM_ADJ")      == 0) get_from_keyword_file (PHOEBE, "system_rm_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "RM_DEL")      == 0) get_from_keyword_file (PHOEBE, "system_rm_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "RM_MIN")      == 0) get_from_keyword_file (PHOEBE, "system_rm_min_value", value_str, keyword_file);
		if (strcmp (keyword_str, "RM_MAX")      == 0) get_from_keyword_file (PHOEBE, "system_rm_max_value", value_str, keyword_file);
		if (strcmp (keyword_str, "INCL")        == 0) get_from_keyword_file (PHOEBE, "system_incl_value", value_str, keyword_file);
		if (strcmp (keyword_str, "INCL_ADJ")    == 0) get_from_keyword_file (PHOEBE, "system_incl_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "INCL_DEL")    == 0) get_from_keyword_file (PHOEBE, "system_incl_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "INCL_MIN")    == 0) get_from_keyword_file (PHOEBE, "system_incl_min_value", value_str, keyword_file);
		if (strcmp (keyword_str, "INCL_MAX")    == 0) get_from_keyword_file (PHOEBE, "system_incl_max_value", value_str, keyword_file);
		if (strcmp (keyword_str, "VGA")         == 0) get_from_keyword_file (PHOEBE, "system_vga_value", value_str, keyword_file);
		if (strcmp (keyword_str, "VGA_ADJ")     == 0) get_from_keyword_file (PHOEBE, "system_vga_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "VGA_DEL")     == 0) get_from_keyword_file (PHOEBE, "system_vga_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "VGA_MIN")     == 0) get_from_keyword_file (PHOEBE, "system_vga_min_value", value_str, keyword_file);
		if (strcmp (keyword_str, "VGA_MAX")     == 0) get_from_keyword_file (PHOEBE, "system_vga_max_value", value_str, keyword_file);

		/* ************************ COMPONENT-RELATED TAB *********************** */

		if (strcmp (keyword_str, "TAVH")        == 0) get_from_keyword_file (PHOEBE, "component_tavh_value", value_str, keyword_file);
		if (strcmp (keyword_str, "TAVH_ADJ")    == 0) get_from_keyword_file (PHOEBE, "component_tavh_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "TAVH_DEL")    == 0) get_from_keyword_file (PHOEBE, "component_tavh_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "TAVH_MIN")    == 0) get_from_keyword_file (PHOEBE, "component_tavh_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "TAVH_MAX")    == 0) get_from_keyword_file (PHOEBE, "component_tavh_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "TAVC")        == 0) get_from_keyword_file (PHOEBE, "component_tavc_value", value_str, keyword_file);
		if (strcmp (keyword_str, "TAVC_ADJ")    == 0) get_from_keyword_file (PHOEBE, "component_tavc_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "TAVC_DEL")    == 0) get_from_keyword_file (PHOEBE, "component_tavc_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "TAVC_MIN")    == 0) get_from_keyword_file (PHOEBE, "component_tavc_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "TAVC_MAX")    == 0) get_from_keyword_file (PHOEBE, "component_tavc_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "PHSV")        == 0) get_from_keyword_file (PHOEBE, "component_phsv_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PHSV_ADJ")    == 0) get_from_keyword_file (PHOEBE, "component_phsv_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "PHSV_DEL")    == 0) get_from_keyword_file (PHOEBE, "component_phsv_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PHSV_MIN")    == 0) get_from_keyword_file (PHOEBE, "component_phsv_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "PHSV_MAX")    == 0) get_from_keyword_file (PHOEBE, "component_phsv_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "PCSV")        == 0) get_from_keyword_file (PHOEBE, "component_pcsv_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PCSV_ADJ")    == 0) get_from_keyword_file (PHOEBE, "component_pcsv_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "PCSV_DEL")    == 0) get_from_keyword_file (PHOEBE, "component_pcsv_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PCSV_MIN")    == 0) get_from_keyword_file (PHOEBE, "component_pcsv_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "PCSV_MAX")    == 0) get_from_keyword_file (PHOEBE, "component_pcsv_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "LOGG1")       == 0) get_from_keyword_file (PHOEBE, "component_logg1_value", value_str, keyword_file);
		if (strcmp (keyword_str, "LOGG1_ADJ")   == 0) get_from_keyword_file (PHOEBE, "component_logg1_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "LOGG1_DEL")   == 0) get_from_keyword_file (PHOEBE, "component_logg1_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "LOGG1_MIN")   == 0) get_from_keyword_file (PHOEBE, "component_logg1_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "LOGG1_MAX")   == 0) get_from_keyword_file (PHOEBE, "component_logg1_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "LOGG2")       == 0) get_from_keyword_file (PHOEBE, "component_logg2_value", value_str, keyword_file);
		if (strcmp (keyword_str, "LOGG2_ADJ")   == 0) get_from_keyword_file (PHOEBE, "component_logg2_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "LOGG2_DEL")   == 0) get_from_keyword_file (PHOEBE, "component_logg2_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "LOGG2_MIN")   == 0) get_from_keyword_file (PHOEBE, "component_logg2_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "LOGG2_MAX")   == 0) get_from_keyword_file (PHOEBE, "component_logg2_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "MET1")        == 0) get_from_keyword_file (PHOEBE, "component_met1_value", value_str, keyword_file);
		if (strcmp (keyword_str, "MET1_ADJ")    == 0) get_from_keyword_file (PHOEBE, "component_met1_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "MET1_DEL")    == 0) get_from_keyword_file (PHOEBE, "component_met1_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "MET1_MIN")    == 0) get_from_keyword_file (PHOEBE, "component_met1_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "MET1_MAX")    == 0) get_from_keyword_file (PHOEBE, "component_met1_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "MET2")        == 0) get_from_keyword_file (PHOEBE, "component_met2_value", value_str, keyword_file);
		if (strcmp (keyword_str, "MET2_ADJ")    == 0) get_from_keyword_file (PHOEBE, "component_met2_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "MET2_DEL")    == 0) get_from_keyword_file (PHOEBE, "component_met2_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "MET2_MIN")    == 0) get_from_keyword_file (PHOEBE, "component_met2_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "MET2_MAX")    == 0) get_from_keyword_file (PHOEBE, "component_met2_value_max", value_str, keyword_file);

		/* **************************** ORBIT TAB ******************************* */

		if (strcmp (keyword_str, "E")           == 0) get_from_keyword_file (PHOEBE, "orbit_e_value", value_str, keyword_file);
		if (strcmp (keyword_str, "E_ADJ")       == 0) get_from_keyword_file (PHOEBE, "orbit_e_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "E_DEL")       == 0) get_from_keyword_file (PHOEBE, "orbit_e_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "E_MIN")       == 0) get_from_keyword_file (PHOEBE, "orbit_e_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "E_MAX")       == 0) get_from_keyword_file (PHOEBE, "orbit_e_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "PERR0")       == 0) get_from_keyword_file (PHOEBE, "orbit_perr0_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PERR0_ADJ")   == 0) get_from_keyword_file (PHOEBE, "orbit_perr0_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "PERR0_DEL")   == 0) get_from_keyword_file (PHOEBE, "orbit_perr0_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "PERR0_MIN")   == 0) get_from_keyword_file (PHOEBE, "orbit_perr0_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "PERR0_MAX")   == 0) get_from_keyword_file (PHOEBE, "orbit_perr0_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "DPERDT")      == 0) get_from_keyword_file (PHOEBE, "orbit_dperdt_value", value_str, keyword_file);
		if (strcmp (keyword_str, "DPERDT_ADJ")  == 0) get_from_keyword_file (PHOEBE, "orbit_dperdt_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "DPERDT_DEL")  == 0) get_from_keyword_file (PHOEBE, "orbit_dperdt_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "DPERDT_MIN")  == 0) get_from_keyword_file (PHOEBE, "orbit_dperdt_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "DPERDT_MAX")  == 0) get_from_keyword_file (PHOEBE, "orbit_dperdt_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "F1")          == 0) get_from_keyword_file (PHOEBE, "orbit_f1_value", value_str, keyword_file);
		if (strcmp (keyword_str, "F1_ADJ")      == 0) get_from_keyword_file (PHOEBE, "orbit_f1_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "F1_DEL")      == 0) get_from_keyword_file (PHOEBE, "orbit_f1_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "F1_MIN")      == 0) get_from_keyword_file (PHOEBE, "orbit_f1_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "F1_MAX")      == 0) get_from_keyword_file (PHOEBE, "orbit_f1_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "F2")          == 0) get_from_keyword_file (PHOEBE, "orbit_f2_value", value_str, keyword_file);
		if (strcmp (keyword_str, "F2_ADJ")      == 0) get_from_keyword_file (PHOEBE, "orbit_f2_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "F2_DEL")      == 0) get_from_keyword_file (PHOEBE, "orbit_f2_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "F2_MIN")      == 0) get_from_keyword_file (PHOEBE, "orbit_f2_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "F2_MAX")      == 0) get_from_keyword_file (PHOEBE, "orbit_f2_value_max", value_str, keyword_file);

		/* ************************* LUMINOSITIES TAB *************************** */

		if (strcmp (keyword_str, "HLA_ADJ")     == 0) get_from_keyword_file (PHOEBE, "luminosities_hla_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "HLA_DEL")     == 0) get_from_keyword_file (PHOEBE, "luminosities_hla_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "CLA_ADJ")     == 0) get_from_keyword_file (PHOEBE, "luminosities_cla_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "CLA_DEL")     == 0) get_from_keyword_file (PHOEBE, "luminosities_cla_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "EL3_ADJ")     == 0) get_from_keyword_file (PHOEBE, "luminosities_el3_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "IPB_ON")      == 0) get_from_keyword_file (PHOEBE, "luminosities_ipb_switch", value_str, keyword_file);
		if (strcmp (keyword_str, "NREF_ON")     == 0) get_from_keyword_file (PHOEBE, "luminosities_nref_switch", value_str, keyword_file);
		if (strcmp (keyword_str, "NREF_VAL")    == 0) get_from_keyword_file (PHOEBE, "luminosities_nref_value", value_str, keyword_file);
		if (strcmp (keyword_str, "IFAT1_ON")    == 0) get_from_keyword_file (PHOEBE, "luminosities_ifat1_switch", value_str, keyword_file);
		if (strcmp (keyword_str, "IFAT2_ON")    == 0) get_from_keyword_file (PHOEBE, "luminosities_ifat2_switch", value_str, keyword_file);
		if (strcmp (keyword_str, "MODELLGG_ON") == 0) get_from_keyword_file (PHOEBE, "luminosities_logg_from_model_switch", value_str, keyword_file);
		if (strcmp (keyword_str, "NOISE_ON")    == 0) get_from_keyword_file (PHOEBE, "luminosities_noise_switch", value_str, keyword_file);
		if (strcmp (keyword_str, "NOISE_TYPE")  == 0) get_from_keyword_file (PHOEBE, "luminosities_noise_list_entry", value_str, keyword_file);
		if (strcmp (keyword_str, "NOISE_VAL")   == 0) get_from_keyword_file (PHOEBE, "luminosities_noise_value", value_str, keyword_file);
		if (strcmp (keyword_str, "SEED_VAL")    == 0) get_from_keyword_file (PHOEBE, "luminosities_seed_value", value_str, keyword_file);
		if (strcmp (keyword_str, "ICOR1_ON")    == 0) get_from_keyword_file (PHOEBE, "luminosities_icor1_switch", value_str, keyword_file);
		if (strcmp (keyword_str, "ICOR2_ON")    == 0) get_from_keyword_file (PHOEBE, "luminosities_icor2_switch", value_str, keyword_file);
		if (strcmp (keyword_str, "EL3_FLUX")    == 0)
			{
			if (atoi (value_str) == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "luminosities_el3_flux_switch")), TRUE);
			else gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "luminosities_el3_percent_switch")), TRUE);
			}

		if (strncmp (keyword_str, "HLALC", 5) == 0)
			{
			sscanf (keyword_str, "HLALC%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_lc_info_list")), readout_int-1, 1, value_str);
			}

		if (strncmp (keyword_str, "CLALC", 5) == 0)
			{
			sscanf (keyword_str, "CLALC%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_lc_info_list")), readout_int-1, 2, value_str);
			}

		if ( (strncmp (keyword_str, "EL3", 3) == 0) && (strcmp (keyword_str, "EL3_ADJ") != 0) && (strcmp (keyword_str, "EL3_FLUX") != 0) )
			{
			sscanf (keyword_str, "EL3%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_el3_info_list")), readout_int-1, 1, value_str);
			}

		if ( (strncmp (keyword_str, "OPSF", 4) == 0) && (strcmp (keyword_str, "OPSF_ADJ") != 0) )
			{
			sscanf (keyword_str, "OPSF%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_el3_info_list")), readout_int-1, 2, value_str);
			}

		if (strncmp (keyword_str, "WEIGHT", 5) == 0)
			{
			sscanf (keyword_str, "WEIGHT%d", &readout_int);
			strip_string_tail (value_str); value_str++;
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_weighting_info_list")), readout_int-1, 1, value_str);
			}

		/* ****************************** LD TAB ******************************** */

		if (strcmp (keyword_str, "LD")          == 0) get_from_keyword_file (PHOEBE, "ld_ld_law_combo_box_entry", value_str, keyword_file);
		if (strcmp (keyword_str, "XBOL1")       == 0) get_from_keyword_file (PHOEBE, "ld_xbol1_value", value_str, keyword_file);
		if (strcmp (keyword_str, "XBOL2")       == 0) get_from_keyword_file (PHOEBE, "ld_xbol2_value", value_str, keyword_file);
		if (strcmp (keyword_str, "YBOL1")       == 0) get_from_keyword_file (PHOEBE, "ld_ybol1_value", value_str, keyword_file);
		if (strcmp (keyword_str, "YBOL2")       == 0) get_from_keyword_file (PHOEBE, "ld_ybol2_value", value_str, keyword_file);
		if (strcmp (keyword_str, "X1A_ADJ")     == 0) get_from_keyword_file (PHOEBE, "ld_x1a_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "X1A_DEL")     == 0) get_from_keyword_file (PHOEBE, "ld_x1a_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "X2A_ADJ")     == 0) get_from_keyword_file (PHOEBE, "ld_x2a_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "X2A_DEL")     == 0) get_from_keyword_file (PHOEBE, "ld_x2a_del_value", value_str, keyword_file);

		if (strncmp (keyword_str, "X1ALC", 5) == 0)
			{
			sscanf (keyword_str, "X1ALC%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), readout_int-1, 1, value_str);
			}

		if (strncmp (keyword_str, "Y1ALC", 5) == 0)
			{
			sscanf (keyword_str, "Y1ALC%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), readout_int-1, 2, value_str);
			}

		if (strncmp (keyword_str, "X2ALC", 5) == 0)
			{
			sscanf (keyword_str, "X2ALC%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), readout_int-1, 3, value_str);
			}

		if (strncmp (keyword_str, "Y2ALC", 5) == 0)
			{
			sscanf (keyword_str, "Y2ALC%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), readout_int-1, 4, value_str);
			}

		if (strncmp (keyword_str, "X1ARV", 5) == 0)
			{
			sscanf (keyword_str, "X1ARV%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), readout_int-1, 1, value_str);
			}

		if (strncmp (keyword_str, "Y1ARV", 5) == 0)
			{
			sscanf (keyword_str, "Y1ARV%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), readout_int-1, 2, value_str);
			}

		if (strncmp (keyword_str, "X2ARV", 5) == 0)
			{
			sscanf (keyword_str, "X2ARV%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), readout_int-1, 3, value_str);
			}

		if (strncmp (keyword_str, "Y2ARV", 5) == 0)
			{
			sscanf (keyword_str, "Y2ARV%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), readout_int-1, 4, value_str);
			}

		/* **************************** SURFACE TAB ***************************** */

		if (strcmp (keyword_str, "ALB1")        == 0) get_from_keyword_file (PHOEBE, "surface_alb1_value", value_str, keyword_file);
		if (strcmp (keyword_str, "ALB1_ADJ")    == 0) get_from_keyword_file (PHOEBE, "surface_alb1_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "ALB1_DEL")    == 0) get_from_keyword_file (PHOEBE, "surface_alb1_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "ALB1_MIN")    == 0) get_from_keyword_file (PHOEBE, "surface_alb1_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "ALB1_MAX")    == 0) get_from_keyword_file (PHOEBE, "surface_alb1_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "ALB2")        == 0) get_from_keyword_file (PHOEBE, "surface_alb2_value", value_str, keyword_file);
		if (strcmp (keyword_str, "ALB2_ADJ")    == 0) get_from_keyword_file (PHOEBE, "surface_alb2_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "ALB2_DEL")    == 0) get_from_keyword_file (PHOEBE, "surface_alb2_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "ALB2_MIN")    == 0) get_from_keyword_file (PHOEBE, "surface_alb2_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "ALB2_MAX")    == 0) get_from_keyword_file (PHOEBE, "surface_alb2_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "GR1")         == 0) get_from_keyword_file (PHOEBE, "surface_gr1_value", value_str, keyword_file);
		if (strcmp (keyword_str, "GR1_ADJ")     == 0) get_from_keyword_file (PHOEBE, "surface_gr1_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "GR1_DEL")     == 0) get_from_keyword_file (PHOEBE, "surface_gr1_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "GR1_MIN")     == 0) get_from_keyword_file (PHOEBE, "surface_gr1_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "GR1_MAX")     == 0) get_from_keyword_file (PHOEBE, "surface_gr1_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "GR2")         == 0) get_from_keyword_file (PHOEBE, "surface_gr2_value", value_str, keyword_file);
		if (strcmp (keyword_str, "GR2_ADJ")     == 0) get_from_keyword_file (PHOEBE, "surface_gr2_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "GR2_DEL")     == 0) get_from_keyword_file (PHOEBE, "surface_gr2_del_value", value_str, keyword_file);
		if (strcmp (keyword_str, "GR2_MIN")     == 0) get_from_keyword_file (PHOEBE, "surface_gr2_value_min", value_str, keyword_file);
		if (strcmp (keyword_str, "GR2_MAX")     == 0) get_from_keyword_file (PHOEBE, "surface_gr2_value_max", value_str, keyword_file);
		if (strcmp (keyword_str, "NSPOTSPRIM")  == 0) get_from_keyword_file (PHOEBE, "spots_sprim_value", value_str, keyword_file);
		if (strcmp (keyword_str, "NSPOTSSEC")   == 0) get_from_keyword_file (PHOEBE, "spots_ssec_value", value_str, keyword_file);

		if (strcmp (keyword_str, "SPOT1_ADJ")   == 0) get_from_keyword_file (PHOEBE, "spots_spot_1_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "SPOT2_ADJ")   == 0) get_from_keyword_file (PHOEBE, "spots_spot_2_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "XLAT1_ADJ")   == 0) get_from_keyword_file (PHOEBE, "spots_xlat1_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "XLAT1_DEL")   == 0) get_from_keyword_file (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp1_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "XLONG1_ADJ")  == 0) get_from_keyword_file (PHOEBE, "spots_xlong1_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "XLONG1_DEL")  == 0) get_from_keyword_file (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp1_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "RADSP1_ADJ")  == 0) get_from_keyword_file (PHOEBE, "spots_radsp1_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "RADSP1_DEL")  == 0) get_from_keyword_file (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp1_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "TEMSP1_ADJ")  == 0) get_from_keyword_file (PHOEBE, "spots_temsp1_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "TEMSP1_DEL")  == 0) get_from_keyword_file (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp1_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "XLAT2_ADJ")   == 0) get_from_keyword_file (PHOEBE, "spots_xlat2_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "XLAT2_DEL")   == 0) get_from_keyword_file (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp2_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "XLONG2_ADJ")  == 0) get_from_keyword_file (PHOEBE, "spots_xlong2_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "XLONG2_DEL")  == 0) get_from_keyword_file (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp2_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "RADSP2_ADJ")  == 0) get_from_keyword_file (PHOEBE, "spots_radsp2_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "RADSP2_DEL")  == 0) get_from_keyword_file (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp2_step_value", value_str, keyword_file);
		if (strcmp (keyword_str, "TEMSP2_ADJ")  == 0) get_from_keyword_file (PHOEBE, "spots_temsp2_adjust", value_str, keyword_file);
		if (strcmp (keyword_str, "TEMSP2_DEL")  == 0) get_from_keyword_file (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp2_step_value", value_str, keyword_file);

		if (strncmp (keyword_str, "XLAT1", 5) == 0 && keyword_str[5] != '_')
			{
			sscanf (keyword_str, "XLAT1%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), readout_int-1, 1, value_str);
			}

		if (strncmp (keyword_str, "XLONG1", 6) == 0 && keyword_str[6] != '_')
			{
			sscanf (keyword_str, "XLONG1%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), readout_int-1, 2, value_str);
			}

		if (strncmp (keyword_str, "RADSP1", 6) == 0 && keyword_str[6] != '_')
			{
			sscanf (keyword_str, "RADSP1%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), readout_int-1, 3, value_str);
			}

		if (strncmp (keyword_str, "TEMSP1", 6) == 0 && keyword_str[6] != '_')
			{
			sscanf (keyword_str, "TEMSP1%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), readout_int-1, 4, value_str);
			}

		if (strncmp (keyword_str, "XLAT2", 5) == 0 && keyword_str[5] != '_')
			{
			sscanf (keyword_str, "XLAT2%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), readout_int-1, 1, value_str);
			}

		if (strncmp (keyword_str, "XLONG2", 6) == 0 && keyword_str[6] != '_')
			{
			sscanf (keyword_str, "XLONG2%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), readout_int-1, 2, value_str);
			}

		if (strncmp (keyword_str, "RADSP2", 6) == 0 && keyword_str[6] != '_')
			{
			sscanf (keyword_str, "RADSP2%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), readout_int-1, 3, value_str);
			}

		if (strncmp (keyword_str, "TEMSP2", 6) == 0 && keyword_str[6] != '_')
			{
			sscanf (keyword_str, "TEMSP2%d", &readout_int);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), readout_int-1, 4, value_str);
			}

		/* *************************** FITTING TAB ****************************** */

		if (strcmp (keyword_str, "N1_VAL")      == 0) get_from_keyword_file (PHOEBE, "fitting_n1_value", value_str, keyword_file);
		if (strcmp (keyword_str, "N2_VAL")      == 0) get_from_keyword_file (PHOEBE, "fitting_n2_value", value_str, keyword_file);
		if (strcmp (keyword_str, "N1L_VAL")     == 0) get_from_keyword_file (PHOEBE, "fitting_n1l_value", value_str, keyword_file);
		if (strcmp (keyword_str, "N2L_VAL")     == 0) get_from_keyword_file (PHOEBE, "fitting_n2l_value", value_str, keyword_file);
		if (strcmp (keyword_str, "XLAMDA_VAL")  == 0) get_from_keyword_file (PHOEBE, "fitting_xlamda_value", value_str, keyword_file);
		if (strcmp (keyword_str, "ISYM_ON")     == 0) get_from_keyword_file (PHOEBE, "fitting_isym_switch", value_str, keyword_file);
		if (strcmp (keyword_str, "JDPHS_TIME")  == 0)
			{
			if (atoi (value_str) == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "fitting_independent_variable_times_switch")), TRUE);
			else gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "fitting_independent_variable_phases_switch")), TRUE);
			}

		/* ************************* LC PLOTTING WINDOW ************************* */

		if (strcmp (keyword_str, "LC_PHSTRT")   == 0) get_from_keyword_file (PHOEBE_plot_lc, "plot_lc_phstrt_value", value_str, keyword_file);
		if (strcmp (keyword_str, "LC_PHEND")    == 0) get_from_keyword_file (PHOEBE_plot_lc, "plot_lc_phend_value", value_str, keyword_file);
		if (strcmp (keyword_str, "LC_VERTICES") == 0) get_from_keyword_file (PHOEBE_plot_lc, "plot_lc_vertexes_value", value_str, keyword_file);
		if (strcmp (keyword_str, "LC_INDEP")    == 0) get_from_keyword_file (PHOEBE_plot_lc, "plot_lc_independent_combo_box_entry", value_str, keyword_file);
		if (strcmp (keyword_str, "LC_DEP")      == 0) get_from_keyword_file (PHOEBE_plot_lc, "plot_lc_dependent_combo_box_entry", value_str, keyword_file);
		if (strcmp (keyword_str, "PHNORM_VAL")  == 0) get_from_keyword_file (PHOEBE_plot_lc, "plot_lc_phnorm_value", value_str, keyword_file);
		if (strcmp (keyword_str, "FACTOR_VAL")  == 0) get_from_keyword_file (PHOEBE_plot_lc, "plot_lc_factor_value", value_str, keyword_file);

		/* ************************* RV PLOTTING WINDOW ************************* */

		if (strcmp (keyword_str, "RV_PHSTRT")   == 0) get_from_keyword_file (PHOEBE_plot_rv, "plot_rv_phstrt_value", value_str, keyword_file);
		if (strcmp (keyword_str, "RV_PHEND")    == 0) get_from_keyword_file (PHOEBE_plot_rv, "plot_rv_phend_value", value_str, keyword_file);
		if (strcmp (keyword_str, "RV_VERTICES") == 0) get_from_keyword_file (PHOEBE_plot_rv, "plot_rv_vertexes_value", value_str, keyword_file);
		if (strcmp (keyword_str, "RV_INDEP")    == 0) get_from_keyword_file (PHOEBE_plot_rv, "plot_rv_independent_combo_box_entry", value_str, keyword_file);
		if (strcmp (keyword_str, "RV_DEP")      == 0) get_from_keyword_file (PHOEBE_plot_rv, "plot_rv_dependent_combo_box_entry", value_str, keyword_file);

		/* Finally, we have to repoint the strings to the beginning of their      */
		/* allocated space:                                                       */
		keyword_str = keyword_string; keyword_str[0] = '\0';
		value_str   =   value_string;   value_str[0] = '\0';
		}

	fclose (keyword_file);
	}
	
void open_legacy_keyword_file (const char *filename)
	{
	char keyword_string[16];
	char *keyword_str = keyword_string;

	GtkWidget *readout_widget;

	int    readout_int;
	double readout_dbl;

	char working_string[255];
	char *working_str = working_string;

	int i;

	FILE *keyword_file;

	keyword_file = fopen (filename, "r");

	do
		{
		fscanf (keyword_file, "%15s", keyword_str);

		/* ***************************** DATA TAB ******************************* */

		if (strcmp (keyword_str, "NAME:") == 0)
			{
			for (i = 1; i <= 10; i++) fgetc (keyword_file);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			readout_widget = lookup_widget (PHOEBE, "data_star_name_entry");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "MODEL:") == 0)
			{
			for (i = 1; i <= 9; i++) fgetc (keyword_file);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			readout_widget = lookup_widget (PHOEBE, "data_model_list_entry");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "LCNO:" )      == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = phoebe_widget (LCNO);
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		if (strcmp (keyword_str, "RVNO:" )      == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = phoebe_widget (RVNO);
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		if (strcmp (keyword_str, "SPECNO:" )      == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = phoebe_widget (SPECNO);
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		if (strcmp (keyword_str, "MNORM:" )      == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = phoebe_widget (MNORM);
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "REDDENING_R" )      == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_r_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "REDDENING_E" )      == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_color_excess_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "REDDENING:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_reddening_switch");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strncmp (keyword_str, "LCCOL1", 6) == 0)
			{
			sscanf (keyword_str, "LCCOL1%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			sprintf (PHOEBE_lc_data[readout_int-1].column1, "%s", working_str);
			}

		if (strncmp (keyword_str, "LCCOL2", 6) == 0)
			{
			sscanf (keyword_str, "LCCOL2%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			sprintf (PHOEBE_lc_data[readout_int-1].column2, "%s", working_str);
			}

		if (strncmp (keyword_str, "LCCOL3", 6) == 0)
			{
			/* This entry may contain spaces and that's why we have to be careful:  */
			sscanf (keyword_str, "LCCOL3%d", &readout_int);
			for (i = 1; i <= 7; i++) fgetc (keyword_file);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			sprintf (PHOEBE_lc_data[readout_int-1].column3, "%s", working_str);
			}

		if (strncmp (keyword_str, "LCFN", 4) == 0)
			{
			sscanf (keyword_str, "LCFN%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			sprintf (PHOEBE_lc_data[readout_int-1].filename, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list")), readout_int-1, 1, working_str);
			}

		if (strncmp (keyword_str, "LCSIG", 5) == 0)
			{
			sscanf (keyword_str, "LCSIG%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			sprintf (PHOEBE_lc_data[readout_int-1].sigma, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list")), readout_int-1, 2, working_str);
			}

		if (strncmp (keyword_str, "LCFLT", 5) == 0)
			{
			/* This entry may contain spaces and that's why we have to be careful:  */
			sscanf (keyword_str, "LCFLT%d", &readout_int);
			for (i = 1; i <= 8; i++) fgetc (keyword_file);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			sprintf (PHOEBE_lc_data[readout_int-1].filter, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list")), readout_int-1, 3, working_str);
			}

		if (strncmp (keyword_str, "RVCOL1", 6) == 0)
			{
			sscanf (keyword_str, "RVCOL1%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			sprintf (PHOEBE_rv_data[readout_int-1].column1, "%s", working_str);
			}

		if (strncmp (keyword_str, "RVCOL2", 6) == 0)
			{
			/* This entry may contain spaces and that's why we have to be careful:  */
			sscanf (keyword_str, "RVCOL2%d", &readout_int);
			for (i = 1; i <= 7; i++) fgetc (keyword_file);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			sprintf (PHOEBE_rv_data[readout_int-1].column2, "%s", working_str);
			}

		if (strncmp (keyword_str, "RVCOL3", 6) == 0)
			{
			sscanf (keyword_str, "RVCOL3%d", &readout_int);
			for (i = 1; i <= 7; i++) fgetc (keyword_file);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			sprintf (PHOEBE_rv_data[readout_int-1].column3, "%s", working_str);
			}

		if (strncmp (keyword_str, "RVFN", 4) == 0)
			{
			sscanf (keyword_str, "RVFN%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			sprintf (PHOEBE_rv_data[readout_int-1].filename, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list")), readout_int-1, 1, working_str);
			}

		if (strncmp (keyword_str, "RVSIG", 5) == 0)
			{
			sscanf (keyword_str, "RVSIG%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			sprintf (PHOEBE_rv_data[readout_int-1].sigma, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list")), readout_int-1, 2, working_str);
			}

		if (strncmp (keyword_str, "RVFLT", 5) == 0)
			{
			sscanf (keyword_str, "RVFLT%d", &readout_int);
			for (i = 1; i <= 8; i++) fgetc (keyword_file);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			sprintf (PHOEBE_rv_data[readout_int-1].filter, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list")), readout_int-1, 3, working_str);
			}

		if (strcmp (keyword_str, "BINNING:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "data_binning_switch");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "BINVAL:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "data_binning_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		/* *************************** GENERAL TAB ****************************** */

		if (strcmp (keyword_str, "HJD0:") == 0)
			{
			fscanf (keyword_file, "%s", working_str);
			readout_widget = lookup_widget (PHOEBE, "system_hjd0_value");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "HJD0_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "system_hjd0_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "HJD0_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_hjd0_step_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "HJD0_MIN:") == 0)
			{
			fscanf (keyword_file, "%s", working_str);
			readout_widget = lookup_widget (PHOEBE, "system_hjd0_min_value");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "HJD0_MAX:") == 0)
			{
			fscanf (keyword_file, "%s", working_str);
			readout_widget = lookup_widget (PHOEBE, "system_hjd0_max_value");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "PERIOD:") == 0)
			{
			fscanf (keyword_file, "%s", working_str);
			readout_widget = lookup_widget (PHOEBE, "system_period_value");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "PERIOD_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "system_period_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "PERIOD_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_period_step_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PERIOD_MIN:") == 0)
			{
			fscanf (keyword_file, "%s", working_str);
			readout_widget = lookup_widget (PHOEBE, "system_period_min_value");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "PERIOD_MAX:") == 0)
			{
			fscanf (keyword_file, "%s", working_str);
			readout_widget = lookup_widget (PHOEBE, "system_period_max_value");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "DPDT:") == 0)
			{
			fscanf (keyword_file, "%s", working_str);
			readout_widget = lookup_widget (PHOEBE, "system_dpdt_value");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "DPDT_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "system_dpdt_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "DPDT_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_dpdt_step_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "DPDT_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_dpdt_min_value");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "DPDT_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_dpdt_max_value");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "PSHIFT:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_pshift_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PSHIFT_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "system_pshift_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "PSHIFT_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_pshift_step_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PSHIFT_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_pshift_min_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PSHIFT_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_pshift_max_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "SMA:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_sma_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "SMA_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "system_sma_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "SMA_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_sma_step_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "SMA_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_sma_min_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "SMA_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_sma_max_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "RM:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_rm_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "RM_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "system_rm_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "RM_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_rm_step_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "RM_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_rm_min_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "RM_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_rm_max_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "XINCL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_incl_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "XINCL_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "system_incl_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "XINCL_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_incl_step_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "XINCL_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_incl_min_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "XINCL_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_incl_max_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "VGA:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_vga_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "VGA_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "system_vga_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "VGA_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_vga_step_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "VGA_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_vga_min_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "VGA_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "system_vga_max_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		/* **************************** BASIC TAB ******************************* */

		if (strcmp (keyword_str, "TAVH:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_tavh_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "TAVH_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "component_tavh_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "TAVH_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_tavh_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "TAVH_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_tavh_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "TAVH_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_tavh_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "TAVC:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_tavc_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "TAVC_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "component_tavc_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "TAVC_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_tavc_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "TAVC_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_tavc_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "TAVC_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_tavc_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "LOGG1:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_logg1_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "LOGG2:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_logg2_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "METAL1:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_met1_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "METAL2:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_met2_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		/* *************************** ADVANCED TAB ***************************** */

		if (strcmp (keyword_str, "PHSV:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_phsv_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PHSV_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "component_phsv_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "PHSV_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_phsv_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PHSV_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_phsv_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PHSV_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_phsv_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PCSV:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_pcsv_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PCSV_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "component_pcsv_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "PCSV_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_pcsv_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PCSV_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_pcsv_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PCSV_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "component_pcsv_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "GR1:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_gr1_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "GR1_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "surface_gr1_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "GR1_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_gr1_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "GR1_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_gr1_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "GR1_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_gr1_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "GR2:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_gr2_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "GR2_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "surface_gr2_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "GR2_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_gr2_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "GR2_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_gr2_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "GR2_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_gr2_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "ALB1:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_alb1_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "ALB1_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "surface_alb1_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "ALB1_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_alb1_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "ALB1_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_alb1_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "ALB1_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_alb1_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "ALB2:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_alb2_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "ALB2_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "surface_alb2_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "ALB2_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_alb2_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "ALB2_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_alb2_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "ALB2_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "surface_alb2_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "F1:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_f1_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "F1_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "orbit_f1_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "F1_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_f1_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "F1_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_f1_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "F1_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_f1_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "F2:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_f2_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "F2_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "orbit_f2_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "F2_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_f2_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "F2_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_f2_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "F2_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_f2_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		/* **************************** ORBIT TAB ******************************* */

		if (strcmp (keyword_str, "E:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_e_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "E_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "orbit_e_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "E_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_e_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "E_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_e_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "E_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_e_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PERR0:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_perr0_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PERR0_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "orbit_perr0_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "PERR0_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_perr0_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PERR0_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_perr0_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "PERR0_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_perr0_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "DPERDT:") == 0)
			{
			fscanf (keyword_file, "%s", working_str);
			readout_widget = lookup_widget (PHOEBE, "orbit_dperdt_value");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "DPERDT_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "orbit_dperdt_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "DPERDT_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_dperdt_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "DPERDT_MIN:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_dperdt_value_min");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "DPERDT_MAX:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "orbit_dperdt_value_max");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		/* ************************* LUMINOSITIES TAB *************************** */

		if (strncmp (keyword_str, "HLALC", 5) == 0)
			{
			sscanf (keyword_str, "HLALC%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_lc_info_list")), readout_int-1, 1, working_str);
			}

		if (strncmp (keyword_str, "CLALC", 5) == 0)
			{
			sscanf (keyword_str, "CLALC%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_lc_info_list")), readout_int-1, 2, working_str);
			}

		if ( (strncmp (keyword_str, "EL3", 3) == 0) && (strcmp (keyword_str, "EL3_ADJ:") != 0) )
			{
			sscanf (keyword_str, "EL3%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_el3_info_list")), readout_int-1, 1, working_str);
			}

		if ( (strncmp (keyword_str, "OPSF", 4) == 0) && (strcmp (keyword_str, "OPSF_ADJ:") != 0) )
			{
			sscanf (keyword_str, "OPSF%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_el3_info_list")), readout_int-1, 2, working_str);
			}

		if (strncmp (keyword_str, "WEIGHT", 5) == 0)
			{
			for (i = 1; i <= 7; i++) fgetc (keyword_file);
			sscanf (keyword_str, "WEIGHT%d", &readout_int);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_weighting_info_list")), readout_int-1, 1, working_str);
			}

		if (strcmp (keyword_str, "HLA_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "luminosities_hla_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "HLA_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "luminosities_hla_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "CLA_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "luminosities_cla_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "EL3_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "luminosities_el3_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "IPB_ON:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "luminosities_ipb_switch");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "IFAT1_ON:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "luminosities_ifat1_switch");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "IFAT2_ON:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "luminosities_ifat2_switch");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "NOISE_ON:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "luminosities_noise_switch");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "NOISE_TYPE:") == 0)
			{
			fscanf (keyword_file, "%s", working_str);
			readout_widget = lookup_widget (PHOEBE, "luminosities_noise_list_entry");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "NOISE_VAL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "luminosities_noise_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "SEED_VAL:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "luminosities_seed_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		/* **************************** SPOTS  TAB ****************************** */

		if (strcmp (keyword_str, "NSPOTSPRIM:" )      == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "spots_sprim_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		if (strcmp (keyword_str, "NSPOTSSEC:" )      == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "spots_ssec_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		if (strncmp (keyword_str, "XLAT1", 5) == 0)
			{
			sscanf (keyword_str, "XLAT1%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), readout_int-1, 1, working_str);
			}

		if (strncmp (keyword_str, "XLONG1", 6) == 0)
			{
			sscanf (keyword_str, "XLONG1%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), readout_int-1, 2, working_str);
			}

		if (strncmp (keyword_str, "RADSP1", 6) == 0)
			{
			sscanf (keyword_str, "RADSP1%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), readout_int-1, 3, working_str);
			}

		if (strncmp (keyword_str, "TEMSP1", 6) == 0)
			{
			sscanf (keyword_str, "TEMSP1%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), readout_int-1, 4, working_str);
			}

		if (strncmp (keyword_str, "XLAT2", 5) == 0)
			{
			sscanf (keyword_str, "XLAT2%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), readout_int-1, 1, working_str);
			}

		if (strncmp (keyword_str, "XLONG2", 6) == 0)
			{
			sscanf (keyword_str, "XLONG2%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), readout_int-1, 2, working_str);
			}

		if (strncmp (keyword_str, "RADSP2", 6) == 0)
			{
			sscanf (keyword_str, "RADSP2%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), readout_int-1, 3, working_str);
			}

		if (strncmp (keyword_str, "TEMSP2", 6) == 0)
			{
			sscanf (keyword_str, "TEMSP2%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), readout_int-1, 4, working_str);
			}

		/* ********************************************************************** */

		if (strcmp (keyword_str, "NREF_ON:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "luminosities_nref_switch");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "NREF_VAL:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "luminosities_nref_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		if (strcmp (keyword_str, "PHNORM_VAL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_phnorm_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "THE_VAL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "data_the_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "FACTOR_VAL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_factor_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "ICOR1_ON:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "luminosities_icor1_switch");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "ICOR2_ON:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "luminosities_icor2_switch");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		/* ****************************** LD TAB ******************************** */

		if (strcmp (keyword_str, "LD:") == 0)
			{
			for (i = 1; i <= 12; i++) fgetc (keyword_file);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			readout_widget = lookup_widget (PHOEBE, "ld_ld_law_combo_box_entry");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "XBOL1:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "ld_xbol1_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "YBOL1:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "ld_ybol1_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "XBOL2:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "ld_xbol2_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "YBOL2:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "ld_ybol2_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "X1A_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "ld_x1a_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "X2A_ADJ:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "ld_x2a_adjust");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strncmp (keyword_str, "X1ALC", 5) == 0)
			{
			sscanf (keyword_str, "X1ALC%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), readout_int-1, 1, working_str);
			}

		if (strncmp (keyword_str, "Y1ALC", 5) == 0)
			{
			sscanf (keyword_str, "Y1ALC%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), readout_int-1, 2, working_str);
			}

		if (strncmp (keyword_str, "X2ALC", 5) == 0)
			{
			sscanf (keyword_str, "X2ALC%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), readout_int-1, 3, working_str);
			}

		if (strncmp (keyword_str, "Y2ALC", 5) == 0)
			{
			sscanf (keyword_str, "Y2ALC%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), readout_int-1, 4, working_str);
			}

		if (strncmp (keyword_str, "X1ARV", 5) == 0)
			{
			sscanf (keyword_str, "X1ARV%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), readout_int-1, 1, working_str);
			}

		if (strncmp (keyword_str, "Y1ARV", 5) == 0)
			{
			sscanf (keyword_str, "Y1ARV%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), readout_int-1, 2, working_str);
			}

		if (strncmp (keyword_str, "X2ARV", 5) == 0)
			{
			sscanf (keyword_str, "X2ARV%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), readout_int-1, 3, working_str);
			}

		if (strncmp (keyword_str, "Y2ARV", 5) == 0)
			{
			sscanf (keyword_str, "Y2ARV%d", &readout_int);
			fscanf (keyword_file, "%s", working_str);
			gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), readout_int-1, 4, working_str);
			}

		if (strcmp (keyword_str, "X1A_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "ld_x1a_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "X2A_DEL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "ld_x2a_del_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		/* *************************** FITTING TAB ****************************** */

		if (strcmp (keyword_str, "N1_VAL:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "fitting_n1_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		if (strcmp (keyword_str, "N2_VAL:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "fitting_n2_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		if (strcmp (keyword_str, "N1L_VAL:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "fitting_n1l_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		if (strcmp (keyword_str, "N2L_VAL:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "fitting_n2l_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		if (strcmp (keyword_str, "XLAMDA_VAL:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE, "fitting_xlamda_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "ISYM_ON:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE, "fitting_isym_switch");
			if (readout_int == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			if (readout_int == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
			}

		if (strcmp (keyword_str, "LC_PHSTRT:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_phstrt_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "LC_PHEND:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_phend_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "RV_PHSTRT:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_phstrt_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "RV_PHEND:") == 0)
			{
			fscanf (keyword_file, "%lf", &readout_dbl);
			readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_phend_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);
			}

		if (strcmp (keyword_str, "LC_VERTICES:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_vertexes_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		if (strcmp (keyword_str, "RV_VERTICES:") == 0)
			{
			fscanf (keyword_file, "%d", &readout_int);
			readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_vertexes_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_int);
			}

		if (strcmp (keyword_str, "LC_INDEP:") == 0)
			{
			for (i = 1; i <= 6; i++) fgetc (keyword_file);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_independent_combo_box_entry");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "LC_DEP:") == 0)
			{
			for (i = 1; i <= 8; i++) fgetc (keyword_file);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_dependent_combo_box_entry");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "RV_INDEP:") == 0)
			{
			for (i = 1; i <= 6; i++) fgetc (keyword_file);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_independent_combo_box_entry");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}

		if (strcmp (keyword_str, "RV_DEP:") == 0)
			{
			for (i = 1; i <= 8; i++) fgetc (keyword_file);
			fgets (working_str, 255, keyword_file);
			strip_string_tail (working_str);
			readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_dependent_combo_box_entry");
			gtk_entry_set_text (GTK_ENTRY (readout_widget), working_str);
			}
		}
	while (feof (keyword_file) == 0);

	fclose (keyword_file);
	}

int check_directory_consistency (GtkWidget *filesel1, GtkWidget *filesel2)
	{
	char *filename1 = gtk_file_selection_get_filename (GTK_FILE_SELECTION (filesel1));
	char *filename2 = gtk_file_selection_get_filename (GTK_FILE_SELECTION (filesel2));

	char stripped1_string[255];
	char *stripped1 = stripped1_string;

	char stripped2_string[255];
	char *stripped2 = stripped2_string;

	int predicted_length;

	strcpy (stripped1, filename1);
	strcpy (stripped2, filename2);

	/* First we have to strip the filenames that might be at the end:           */
	if (filename1[strlen(filename1)-1] != '/')
		{
		while (strchr (stripped1, '/') != NULL)
			{
			stripped1 = strchr (stripped1, '/');
			sscanf (stripped1, "/%s", stripped1);
			}
		predicted_length = strlen (filename1) - strlen (stripped1);
		strncpy (stripped1, filename1, predicted_length);
		stripped1[predicted_length] = '\0';
		}

	if (filename2[strlen(filename2)-1] != '/')
		{
		strcpy (stripped2, filename2);
		while (strchr (stripped2, '/') != NULL)
			{
			stripped2 = strchr (stripped2, '/');
			sscanf (stripped2, "/%s", stripped2);
			}
		predicted_length = strlen (filename2) - strlen (stripped2);
		strncpy (stripped2, filename2, predicted_length);
		stripped2[predicted_length] = '\0';
		}

	if (strcmp (stripped1, stripped2) == 0) return 1; else return 0;
	}

void update_keyword_file_list ()
	{
	char *filename_str = gtk_file_selection_get_filename (GTK_FILE_SELECTION (PHOEBE_file_selector));

	char stripped_string[255];
	char *stripped_str = stripped_string;

	int predicted_length;

	strcpy (stripped_str, filename_str);

	while (strchr (stripped_str, '/') != NULL)
		{
		stripped_str = strchr (stripped_str, '/');
		sscanf (stripped_str, "/%s", stripped_str);
		}

	gtk_clist_append (GTK_CLIST (GTK_FILE_SELECTION (PHOEBE_file_selector)->file_list), &stripped_str);
	gtk_clist_sort (GTK_CLIST (GTK_FILE_SELECTION (PHOEBE_file_selector)->file_list));

/* SOON TO BE OBSOLETE: */
	if (check_directory_consistency (PHOEBE_file_selector, PHOEBE_open_keyword_file) == 1)
		{
		gtk_clist_append (GTK_CLIST (GTK_FILE_SELECTION (PHOEBE_open_keyword_file)->file_list), &stripped_str);
		gtk_clist_sort (GTK_CLIST (GTK_FILE_SELECTION (PHOEBE_open_keyword_file)->file_list));
		}
/* ******************** */
	}

void add_entry_to_data_sheet_list (char *keyword, char *value)
	{
	/* This function takes two strings and appends them to the data sheet.      */

	GtkWidget *param_list = lookup_widget (PHOEBE_data_sheet, "data_sheet_info_list");
	char entry_string[2][255];
	char *entry[2] = {entry_string[0], entry_string[1]};

	sprintf (entry[0], "%s", keyword);
	sprintf (entry[1], "%s", value);

	gtk_clist_append (GTK_CLIST (param_list), entry);
	}

void add_parameter_to_data_sheet_list (char *keyword, PHOEBE_keyword delimeter)
	{
	/* This function queries the widget given as an argument for its value and  */
	/* appends it to the data sheet.                                            */

	GtkWidget *param_list = lookup_widget (PHOEBE_data_sheet, "data_sheet_info_list");

	char entry_string[2][255];
	char *entry[2] = {entry_string[0], entry_string[1]};

	GtkWidget *readout_widget;
	int        readout_int;
	double     readout_dbl;
	char      *readout_str;

	readout_widget = phoebe_widget (delimeter);
	sprintf (entry[0], keyword);

	if (GTK_IS_SPIN_BUTTON (readout_widget))
		{
		/* This means we have a widget with numeric value. Now we have to figure  */
		/* out if it's an integer (0 digits) or a double (more that 0 digits):    */
		if (GTK_SPIN_BUTTON (readout_widget)->digits == 0)
			{
			readout_int = gtk_spin_button_get_value_as_int   (GTK_SPIN_BUTTON (readout_widget));
			sprintf (entry[1], "%d", readout_int);
			}
		else
			{
			readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
			sprintf (entry[1], "%5.5lf", readout_dbl);
			}
		}
	if ( (GTK_IS_ENTRY (readout_widget)) && (! GTK_IS_SPIN_BUTTON (readout_widget)) )
		{
		/* This means we have an entry. Since GTK_IS_ENTRY returns true for spin- */
		/* buttons as well, we have to test it the way written above.             */
		readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
		sprintf (entry[1], "%s", readout_str);
		}
	if (GTK_IS_LABEL (readout_widget))
		{
		/* This means we have a label. These widgets are usually some calculated  */
		/* parameter values that the user cannot change.                          */
		gtk_label_get (GTK_LABEL (readout_widget), &readout_str);
		sprintf (entry[1], "%s", readout_str);
		}
	if (GTK_IS_TOGGLE_BUTTON (readout_widget))
		{
		/* This means we have a toggle button. These are switches.                */
		if (GTK_TOGGLE_BUTTON (readout_widget)->active) sprintf (entry[1], "yes");
		                                           else sprintf (entry[1], "no");
		}

	gtk_clist_append (GTK_CLIST (param_list), entry);
	}

void add_all_parameters_to_data_sheet_list ()
	{
	/* This function flushes all parameters that have assigned keywords in PHO- */
	/* EBE (defined in phoebe_global.h) to the data sheet window. If the number */
	/* isn't assigned in enum struct yet, enum returns the last assigned value, */
	/* so comparing it against itself is our test function.                     */

	int i = 0;
	
	char working_string[255];
	char *working_str = working_string;

	char comparison_string[255];
	char *comparison_str = comparison_string;

	sprintf (working_str,    "1");
	sprintf (comparison_str, "2");

	while (0 != 1)
		{
		phoebe_common_name (i, &working_str);
		if (strcmp (comparison_str, working_str) == 0) break;
		add_parameter_to_data_sheet_list (working_str, i);
		strcpy (comparison_str, working_str);
		i++;
		}
	}

void add_relevant_parameters_to_data_sheet_list ()
	{
	/* This function flushes parameter values that are relevant for publication */
	/* or otherwise important. All one has to do to add/remove them is to add   */
	/* or remove PHOEBE keywords from the list below (and change the i limit).  */

	PHOEBE_keyword keyword[] = {SMA, RM, INCL, VGA, TAVH, TAVC, PHSV, PCSV,
	                      LOGG1, LOGG2, MET1, MET2, E, PERR0, F1, F2, ALB1, ALB2};

	int i;

	char working_string[255];
	char *working_str = working_string;

	for (i = 0; i < 18; i++)
		{
		phoebe_common_name (keyword[i], &working_str);
		add_parameter_to_data_sheet_list (working_str, keyword[i]);
		}
	}

void save_data_sheet_parameters_to_file (char *filename)
	{
	int rows, i;
	char *readout_str;
	GtkWidget *data_sheet = lookup_widget (PHOEBE_data_sheet, "data_sheet_info_list");
	FILE *output;

	output = fopen (filename, "w");
	rows = (GTK_CLIST (data_sheet))->rows;
	for (i = 0; i < rows; i++)
		{
		gtk_clist_get_text (GTK_CLIST (data_sheet), i, 0, &readout_str);
		fprintf (output, "%s\t", readout_str);
		gtk_clist_get_text (GTK_CLIST (data_sheet), i, 1, &readout_str);
		fprintf (output, "%s\n", readout_str);
		}
	print_to_status_bar ("Data Sheet saved to disk.");
	fclose (output);
	}

int import_from_fotel (char *filename, char *passed_prefix)
	{
	FILE *input, *output, *phoebe_file;

	char   comment_line[255], readout_line[255], output_name[255], phoebe_name[255], filter[255];
	double hjd, mag, wgt;
	int    chn, typ;
	int    i, j, lccounter = 1, rvcounter = 1, lcno = 0, rvno = 0;

	char   *prefix;

	typedef struct record
		{
		double hjd;
		double mag;
		double wgt;
		int    chn;
		int    typ;
		} record;

	struct
		{
		int     *recno;
		int     *types;
		record **records;
		} data;

	data.recno   = malloc (31 * sizeof   ( *(data.recno)));
	data.types   = malloc (31 * sizeof   ( *(data.types)));
	data.records = malloc (31 * sizeof ( *(data.records)));

	for (i = 0; i < 31; i++)
		{
		data.recno[i]   = 0;
		data.types[i]   = -1;
		data.records[i] = NULL;
		}

	input = fopen (filename, "r");
	if (input == 0)
		{
		phoebe_warning ("\nFile '%s' not found, aborting.\n\n", filename);
		return -1;
		}

	if (PHOEBE_DATA_DIR[strlen(PHOEBE_DATA_DIR)-1] == '/') PHOEBE_DATA_DIR[strlen(PHOEBE_DATA_DIR)-1] = '\0';

	if (strlen (passed_prefix) == 0) prefix = strrchr (filename, '/') + sizeof (char);
	else prefix = passed_prefix;

	/* The first line is a comment, we'll copy it to all PHOEBE files. */
	fgets (comment_line, 255, input);

	/* Get the data: */
	while (!feof (input))
		{
		fgets (readout_line, 255, input);
		if (feof (input)) break;
		if (sscanf (readout_line, "%lf %lf %lf %d %d", &hjd, &mag, &wgt, &chn, &typ) != 5) continue;
		data.recno[chn]++;
		data.types[chn] = typ;
		data.records[chn] = realloc (data.records[chn], data.recno[chn] * sizeof (*(data.records[chn])));
		data.records[chn][data.recno[chn]-1].hjd = hjd;
		data.records[chn][data.recno[chn]-1].mag = mag;
		data.records[chn][data.recno[chn]-1].wgt = wgt;
		}

	/* Count the number of curves: */
	for (i = 0; i < 31; i++)
		if (data.types[i] != -1)
			switch (data.types[i])
				{
				case  1: rvno++; break;
				case  2: rvno++; break;
				case 13:         break;
				default: lcno++; break;
				}

	/* Write out the data: */
	sprintf (phoebe_name, "%s/%s.phoebe", PHOEBE_DATA_DIR, prefix);
	phoebe_file = fopen (phoebe_name, "w");

	fprintf (phoebe_file, "NAME    = \"%s\"\n", prefix);
	fprintf (phoebe_file, "LCNO    = %d\n", lcno);
	fprintf (phoebe_file, "RVNO    = %d\n", rvno);

	for (i = 0; i < 31; i++)
		{
		if (data.types[i] != -1)
			{
			if (data.types[i] == 1)
				{
				sprintf (output_name, "%s/%s.rv1.%d", PHOEBE_DATA_DIR, prefix, i);

				fprintf (phoebe_file, "RVCOL1%d = \"Time\"\n", rvcounter);
				fprintf (phoebe_file, "RVCOL2%d = \"RV in km/s\"\n", rvcounter);
				fprintf (phoebe_file, "RVCOL3%d = \"Weight (real)\"\n", rvcounter);
				fprintf (phoebe_file, "RVFN%d   = \"%s\"\n", rvcounter, output_name);
				fprintf (phoebe_file, "RVSIG%d  = 10.0\n", rvcounter);
				fprintf (phoebe_file, "RVFLT%d  = \"861nm (RVIJ)\"\n", rvcounter);

				rvcounter++;
				}
			else if (data.types[i] ==  2)
				{
				sprintf (output_name, "%s/%s.rv2.%d", PHOEBE_DATA_DIR, prefix, i);

				fprintf (phoebe_file, "RVCOL1%d = \"Time\"\n", rvcounter);
				fprintf (phoebe_file, "RVCOL2%d = \"RV in km/s\"\n", rvcounter);
				fprintf (phoebe_file, "RVCOL3%d = \"Weight (real)\"\n", rvcounter);
				fprintf (phoebe_file, "RVFN%d   = \"%s\"\n", rvcounter, output_name);
				fprintf (phoebe_file, "RVSIG%d  = 10.0\n", rvcounter);
				fprintf (phoebe_file, "RVFLT%d  = \"861nm (RVIJ)\"\n", rvcounter);
				
				rvcounter++;
				}
			else if (data.types[i] == 13) sprintf (output_name, "%s.rv3", prefix);
			else
				{
				sprintf (output_name, "%s/%s.%d.%d", PHOEBE_DATA_DIR, prefix, data.types[i], i);

				fprintf (phoebe_file, "LCCOL1%d = \"Time\"\n", lccounter);
				fprintf (phoebe_file, "LCCOL2%d = \"Magnitude\"\n", lccounter);
				fprintf (phoebe_file, "LCCOL3%d = \"Weight (real)\"\n", lccounter);
				fprintf (phoebe_file, "LCFN%d   = \"%s\"\n", lccounter, output_name);
				fprintf (phoebe_file, "LCSIG%d  = 0.01\n", lccounter);

				switch (data.types[i])
					{
					case  3: sprintf (filter, "550nm (V)"); break;
					case  4: sprintf (filter, "440nm (B)"); break;
					case  5: sprintf (filter, "360nm (U)"); break;
					default: sprintf (filter, "Undefined"); break;
					}

				fprintf (phoebe_file, "LCFLT%d  = \"%s\"\n", lccounter, filter);

				lccounter++;
				}

			output = fopen (output_name, "w");
			fprintf (output, "# %s\n", comment_line);
			for (j = 0; j < data.recno[i]; j++)
				fprintf (output, "%lf\t%lf\t%lf\n", data.records[i][j].hjd, data.records[i][j].mag, data.records[i][j].wgt);
			fclose (output);
			}
		}

	fclose (phoebe_file);

	/* Free the memory: */
	free   (data.recno);
	free   (data.types);
	for (i = 0; i < 31; i++)
		if (data.records[i] != NULL) free (data.records[i]);
	free (data.records);

	open_keyword_file (phoebe_name);

	enumerate_passbands ();
	gui_update_passbands ();

	on_data_lc_filter_changed ();
	on_data_rv_filter_changed ();
	add_filters_to_available_filter_lists ();
	}

int enumerate_passbands ()
	{
	int lcno = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rvno = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));
	int i, j, no = 1;

	for (i = 0; i < lcno; i++)
		{
		for (j = i+1; j < lcno; j++)
			{
			if (strcmp (PHOEBE_lc_data[i].filter, PHOEBE_lc_data[j].filter) == 0)
				{
				no++;
				sprintf (PHOEBE_lc_data[j].filter, "%s #%d", PHOEBE_lc_data[i].filter, no);
				}
			}
		if (no != 1)
			{
			no = 1;
			sprintf (PHOEBE_lc_data[i].filter, "%s #%d", PHOEBE_lc_data[i].filter, no);
			}
		}

	for (i = 0; i < rvno; i++)
		{
		for (j = i+1; j < rvno; j++)
			{
			if (strcmp (PHOEBE_rv_data[i].filter, PHOEBE_rv_data[j].filter) == 0)
				{
				no++;
				sprintf (PHOEBE_rv_data[j].filter, "%s #%d", PHOEBE_rv_data[i].filter, no);
				}
			}
		if (no != 1)
			{
			no = 1;
			sprintf (PHOEBE_rv_data[i].filter, "%s #%d", PHOEBE_rv_data[i].filter, no);
			}
		}

	return 0;
	}

int gui_update_passbands ()
	{
	int lcno = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rvno = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));
	int i;

	for (i = 0; i < lcno; i++)
		gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list")), i, 3, PHOEBE_lc_data[i].filter);
	for (i = 0; i < rvno; i++)
		gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list")), i, 3, PHOEBE_rv_data[i].filter);

	return 0;
	}
