#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <errno.h>
#include <gtk/gtk.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "phoebe_allocations.h"
#include "phoebe_chi2.h"
#include "phoebe_error_handling.h"
#include "phoebe_global.h"
#include "phoebe_grid.h"
#include "phoebe_gui.h"
#include "phoebe_gui_accessories.h"
#include "phoebe_gui_callbacks.h"
#include "phoebe_gui_fitting.h"
#include "phoebe_gui_keyword.h"
#include "phoebe_gui_ld.h"
#include "phoebe_gui_plot.h"
#include "phoebe_gui_support.h"
#include "phoebe_limb_darkening.h"
#include "phoebe_phsv_pcsv.h"
#include "phoebe_plot.h"
#include "phoebe_scripting.h"
#include "phoebe_transformations.h"

void on_switches_toggled (GtkToggleButton *togglebutton, gpointer user_data)
	{
	/* This function takes care of shading, which represents availability of    */
	/* some specific widget; it is attached to a toggle-button change. If the   */
	/* toggle button is turned on, the widget will be available.                */

	if (GTK_TOGGLE_BUTTON (user_data)->active == TRUE)
		gtk_widget_set_sensitive (GTK_WIDGET (togglebutton), TRUE);
	else
		gtk_widget_set_sensitive (GTK_WIDGET (togglebutton), FALSE);
	}

void on_switches_reverse_toggled (GtkToggleButton *togglebutton, gpointer user_data)
	{
	/* This function takes care of shading, which represents availability of    */
	/* some specific widget; it is attached to a toggle-button change. If the   */
	/* toggle button is turned on, the widget will be unavailable.              */

	if (GTK_TOGGLE_BUTTON (user_data)->active == TRUE)
		gtk_widget_set_sensitive (GTK_WIDGET (togglebutton), FALSE);
	else
		gtk_widget_set_sensitive (GTK_WIDGET (togglebutton), TRUE);
	}

void on_data_lc_no_value_changed (GtkEditable *editable, gpointer user_data)
{
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));

	/* Be sure that the 2D parameter correlation Calculate button is off if     */
	/* there are no lightcurves present:                                        */
	if (lc_no == 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "fitting_chi2_calculate_button"), FALSE);
	if (lc_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "fitting_chi2_calculate_button"), TRUE);
	if (lc_no == 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "fitting_chi2_plot_to_file_button"), FALSE);
	if (lc_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "fitting_chi2_plot_to_file_button"), TRUE);

	allocate_memory_for_data_record (&PHOEBE_lc_data, lc_no);
	add_empty_record_to_all_lc_dependent_info_lists ();
/*	add_filters_to_available_filter_lists ();*/
	read_in_data_file_specifics ();
}

void on_data_rv_no_value_changed (GtkEditable *editable, gpointer user_data)
	{
	/* This function takes care of shading of radial velocity fields that are  */
	/* supposed to be available or unavailable, depending on RVNo.             */

	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));
	GtkWidget *readout_widget;

	/* Be sure that the SMA adjustability switch is off if there are no RVs:    */
	readout_widget = lookup_widget (PHOEBE, "system_sma_adjust");
	if (rv_no == 0)
		{
		if (GTK_TOGGLE_BUTTON (readout_widget)->active) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
		gtk_widget_set_sensitive (readout_widget, FALSE);
		}
	if (rv_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "system_sma_adjust"), TRUE);

	/* Be sure that the VGA adjustability switch is off if there are no RVs:    */
	readout_widget = lookup_widget (PHOEBE, "system_vga_adjust");
	if (rv_no == 0)
		{
		if (GTK_TOGGLE_BUTTON (readout_widget)->active) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
		gtk_widget_set_sensitive (readout_widget, FALSE);
		}
	if (rv_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "system_vga_adjust"), TRUE);

	allocate_memory_for_data_record (&PHOEBE_rv_data, rv_no);
	add_empty_record_to_all_rv_dependent_info_lists ();
	add_filters_to_available_filter_lists ();
	read_in_data_file_specifics ();
	}

void on_data_lc_filter_changed ()
	{
	/* This is not an actual callback, because CList widget doesn't support     */
	/* "changed" signal emission. If there is such a signal in GTK2.0, it will  */
	/* be fixed.                                                                */

	/* This function changes the labels "Undefined" and "None Specified" to     */
	/* filter names.                                                            */

	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int i;

	for (i = 0; i < lc_no; i++)
		{
		/* First, let's take care of the luminosities:                            */
		gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_lc_info_list")), i, 0, PHOEBE_lc_data[i].filter);

		/* Next, let's take care of the 3rd light:                                */
		gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_el3_info_list")), i, 0, PHOEBE_lc_data[i].filter);

		/* Then, let's change the weighting labels:                               */
		gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_weighting_info_list")), i, 0, PHOEBE_lc_data[i].filter);

		/* After that, let's change limb darkening labels:                        */
		gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), i, 0, PHOEBE_lc_data[i].filter);

		/* And finally, let's change file info labels:                            */
		gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_files_info_list")), i, 0, PHOEBE_lc_data[i].filter);
		}
	}

void on_data_rv_filter_changed ()
	{
	/* This is not an actual callback, because CList widget doesn't support     */
	/* "changed" signal emission. If there is such a signal in GTK2.0, it will  */
	/* be fixed.                                                                */

	/* This function changes the labels "Undefined" and "None Specified" to     */
	/* filter names.                                                            */

	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));
	int i;

	for (i = 0; i < rv_no; i++)
		{
		/* Let's change limb darkening labels:                                    */
		gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), i, 0, PHOEBE_rv_data[i].filter);

		/* And finally, let's change file info labels:                            */
		gtk_clist_set_text (GTK_CLIST (lookup_widget (PHOEBE, "data_files_info_list")), lc_no+i, 0, PHOEBE_rv_data[i].filter);
		}
	}

void on_configuration_browse_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_configuration_browse);

	gtk_object_set_data (GTK_OBJECT (PHOEBE_configuration_browse), "browse_button", button);
	}

void on_open_data_file_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	/* This function assigns a string to point to the chosen keyword file that  */
	/* will be opened in a moment.                                              */

	char *readout_str;

	readout_str = gtk_file_selection_get_filename (GTK_FILE_SELECTION (PHOEBE_open_data_file));
	gtk_entry_set_text (GTK_ENTRY (lookup_widget (PHOEBE_open_data_file, "output_entry")), readout_str);

	gtk_widget_hide (PHOEBE_open_data_file);
	}

void on_configuration_browse_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	char *file_name_ptr;

	GtkWidget *file_name = lookup_widget (GTK_WIDGET (PHOEBE_configuration_browse), "browse_button");

	file_name_ptr = gtk_file_selection_get_filename (GTK_FILE_SELECTION (PHOEBE_configuration_browse));
	gtk_entry_set_text (GTK_ENTRY (file_name), file_name_ptr);

	gtk_widget_hide (PHOEBE_configuration_browse);
	}

void on_component_phsv_calculate_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *readout_widget;
	double readout_dbl;

	readout_widget = lookup_widget (PHOEBE, "system_rm_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_calculate_phsv, "calculate_phsv_rm_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);

	readout_widget = lookup_widget (PHOEBE, "orbit_f1_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_calculate_phsv, "calculate_phsv_f1_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);

	print_to_status_bar ("PHSV calculation initiated...");

	gtk_widget_show (PHOEBE_calculate_phsv);
	}

void on_component_pcsv_calculate_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *readout_widget;
	double readout_dbl;

	readout_widget = lookup_widget (PHOEBE, "system_rm_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_calculate_pcsv, "calculate_pcsv_rm_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);

	readout_widget = lookup_widget (PHOEBE, "orbit_f1_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_calculate_pcsv, "calculate_pcsv_f1_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);

	print_to_status_bar ("PCSV calculation initiated...");

	gtk_widget_show (PHOEBE_calculate_pcsv);
	}

void on_menu_bar_file_new_activated (GtkMenuItem *menuitem, gpointer user_data)
	{
	GtkWidget *warning_window;

	warning_window = create_warning_window (
		"PHOEBE Question",
		"Reset all settings?",
		"By resetting all unsaved data will be lost.",
		"Are you sure?",
		on_warning_on_new_ok_button_clicked,
		gtk_widget_destroy);

	gtk_object_set_data (GTK_OBJECT (PHOEBE), "warning_window", warning_window);
	}

void on_menu_bar_file_exit_activated (GtkMenuItem *menuitem, gpointer user_data)
	{
	GtkWidget *warning_window;

	if (PHOEBE_CONFIRM_ON_QUIT == 1)
		warning_window = create_warning_window (
			"PHOEBE Question",
			"Quit PHOEBE?",
			"By quitting PHOEBE all unsaved data will be lost.",
			"Are you sure you want to quit?",
			on_warning_on_exit_ok_button_clicked,
			gtk_widget_destroy);
	else
		on_warning_on_exit_ok_button_clicked (NULL, NULL);
	}

void on_menu_bar_file_import_from_dci_activate (GtkMenuItem *menuitem, gpointer user_data)
	{
	read_out_dci_file ("/home/andrej/programming/development/phoebe/src/test.dci");
	return;
	}

void on_menu_bar_file_export_to_dci_activate (GtkMenuItem *menuitem, gpointer user_data)
	{
	phoebe_warning ("not implemented");
	}

void on_warning_on_new_ok_button_clicked (GtkWidget *widget, gpointer user_data)
	{
	/* This function resets PHOEBE parameters to default values:              */

	char filename_string[255];
	char *filename = filename_string;

	GtkWidget *warning_window = lookup_widget (PHOEBE, "warning_window");

	GtkWidget *notice_window;

	sprintf (filename, "%s/default.phoebe", PHOEBE_DEFAULTS_DIR);

	if (file_exists (filename))
		{
		open_keyword_file (filename);
		sprintf (PHOEBE_KEYWORD_FILENAME, "Undefined");
		print_to_status_bar ("PHOEBE reset complete.");
		}
	else
		notice_window = create_notice_window (
			"PHOEBE Notice",
			"PHOEBE Notice: Defaults file cannot be found",
			"The defaults file, \"default.phoebe\", resides in PHOEBE defaults directory.", "Please verify the path to the defaults directory in Settings->Configuration menu.",
			 gtk_widget_destroy);

	gtk_widget_destroy (warning_window);
	}

void on_warning_on_exit_ok_button_clicked (GtkWidget *widget, gpointer user_data)
	{
	/* This function cleans all temporary files and terminates PHOEBE cleanly:  */

	char system_string[255];
	char *system_str = system_string;

	/* Let's clean everything up first: */
	sprintf (system_str, "rm -f %s/phoebe_*", PHOEBE_TEMP_DIR);
	system (system_str);

	/* Return the locale setting to the original state:                         */
	setlocale (LC_NUMERIC, PHOEBE_LOCALE);

	gtk_main_quit ();
	}

void on_calculate_phsv_update_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *old_phsv_value = lookup_widget (GTK_WIDGET (PHOEBE), "component_phsv_value");
	GtkWidget *new_phsv_value = lookup_widget (GTK_WIDGET (PHOEBE_calculate_phsv), "calculate_phsv_phsv_value");

	gtk_spin_button_set_value (GTK_SPIN_BUTTON (old_phsv_value),
	      gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (new_phsv_value)));
	}

void on_calculate_pcsv_update_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *old_pcsv_value = lookup_widget (GTK_WIDGET (PHOEBE), "component_pcsv_value");
	GtkWidget *new_pcsv_value = lookup_widget (GTK_WIDGET (PHOEBE_calculate_pcsv), "calculate_pcsv_pcsv_value");

	gtk_spin_button_set_value (GTK_SPIN_BUTTON (old_pcsv_value),
	      gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (new_pcsv_value)));
	}

void on_calculate_phsv_calculate_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *calculate_phsv_circular = lookup_widget (PHOEBE_calculate_phsv, "calculate_phsv_circular_orbit");
	GtkWidget *calculate_phsv_d = lookup_widget (PHOEBE_calculate_phsv, "calculate_phsv_d_value");
	GtkWidget *calculate_phsv_rm = lookup_widget (PHOEBE_calculate_phsv, "calculate_phsv_rm_value");
	GtkWidget *calculate_phsv_r = lookup_widget (PHOEBE_calculate_phsv, "calculate_phsv_r_value");
	GtkWidget *calculate_phsv_phsv = lookup_widget (PHOEBE_calculate_phsv, "calculate_phsv_phsv_value");
	GtkWidget *calculate_phsv_f, *calculate_phsv_lambda, *calculate_phsv_nu;

	double D, q, r, F, lambda, nu, phsv;

	D = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (calculate_phsv_d));
	q = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (calculate_phsv_rm));
	r = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (calculate_phsv_r));

	if (GTK_TOGGLE_BUTTON (calculate_phsv_circular)->active)
		phsv = calculate_phsv_value (0, D, q, r, 0, 0, 0);
	else
		{
		calculate_phsv_f = lookup_widget (PHOEBE_calculate_phsv, "calculate_phsv_f1_value");
		calculate_phsv_lambda = lookup_widget (PHOEBE_calculate_phsv, "calculate_phsv_lambda_value");
		calculate_phsv_nu = lookup_widget (PHOEBE_calculate_phsv, "calculate_phsv_nu_value");

		F = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (calculate_phsv_f));
		lambda = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (calculate_phsv_lambda));
		nu = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (calculate_phsv_nu));

		phsv = calculate_phsv_value (1, D, q, r, F, lambda, nu);
		}

	gtk_spin_button_set_value (GTK_SPIN_BUTTON (calculate_phsv_phsv), phsv);
	}

void on_calculate_pcsv_calculate_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *calculate_pcsv_circular = lookup_widget (GTK_WIDGET (PHOEBE_calculate_pcsv), "calculate_pcsv_circular_orbit");
	GtkWidget *calculate_pcsv_d = lookup_widget (GTK_WIDGET (PHOEBE_calculate_pcsv), "calculate_pcsv_d_value");
	GtkWidget *calculate_pcsv_rm = lookup_widget (GTK_WIDGET (PHOEBE_calculate_pcsv), "calculate_pcsv_rm_value");
	GtkWidget *calculate_pcsv_r = lookup_widget (GTK_WIDGET (PHOEBE_calculate_pcsv), "calculate_pcsv_r_value");
	GtkWidget *calculate_pcsv_pcsv = lookup_widget (GTK_WIDGET (PHOEBE_calculate_pcsv), "calculate_pcsv_pcsv_value");
	GtkWidget *calculate_pcsv_f, *calculate_pcsv_lambda, *calculate_pcsv_nu;

	double D, q, r, F, lambda, nu, pcsv;

	D = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (calculate_pcsv_d));
	q = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (calculate_pcsv_rm));
	r = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (calculate_pcsv_r));

	if (GTK_TOGGLE_BUTTON (calculate_pcsv_circular)->active)
		{
		pcsv = calculate_pcsv_value (0, D, q, r, 0, 0, 0);
		}
	else
		{
		calculate_pcsv_f = lookup_widget (GTK_WIDGET (PHOEBE_calculate_pcsv), "calculate_pcsv_f1_value");
		calculate_pcsv_lambda = lookup_widget (GTK_WIDGET (PHOEBE_calculate_pcsv), "calculate_pcsv_lambda_value");
		calculate_pcsv_nu = lookup_widget (GTK_WIDGET (PHOEBE_calculate_pcsv), "calculate_pcsv_nu_value");

		F = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (calculate_pcsv_f));
		lambda = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (calculate_pcsv_lambda));
		nu = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (calculate_pcsv_nu));

		pcsv = calculate_pcsv_value (1, D, q, r, F, lambda, nu);
		}

	gtk_spin_button_set_value (GTK_SPIN_BUTTON (calculate_pcsv_pcsv), pcsv);
	}

void on_save_button_clicked (GtkButton *button, gpointer user_data)
	{
	char working_string[255];
	char *working_str = working_string;

	GtkWidget *warning_window;

	if (strcmp (PHOEBE_KEYWORD_FILENAME, "Undefined") == 0)
		{
		gtk_window_set_title (GTK_WINDOW (PHOEBE_file_selector), "Save PHOEBE Keyword File");
		gtk_label_set_text (GTK_LABEL (GTK_BIN (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button"))->child), "Save");
		gtk_signal_connect (GTK_OBJECT (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button")), "clicked", GTK_SIGNAL_FUNC (on_save_keyword_file_ok_button_clicked), NULL);
		gtk_widget_show (PHOEBE_file_selector);
		}
	else
		{
		if (PHOEBE_CONFIRM_ON_SAVE == 1)
			warning_window = create_warning_window (
				"Warning",
				"Overwrite keyword file?",
			  "This will overwrite an existing keyword file.",
				"Are you sure you want to proceed?",
				on_warning_confirm_on_save_ok_button_clicked,
				gtk_widget_destroy);
		else
			{
			save_keyword_file (PHOEBE_KEYWORD_FILENAME);
			sprintf (working_str, "Current keyword file saved to %s.", PHOEBE_KEYWORD_FILENAME);
			print_to_status_bar (working_str);
			}
		}
	}

void on_save_as_button_clicked (GtkMenuItem *menuitem, gpointer user_data)
	{
	gtk_window_set_title (GTK_WINDOW (PHOEBE_file_selector), "Save PHOEBE Keyword File");
	gtk_label_set_text (GTK_LABEL (GTK_BIN (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button"))->child), "Save");
	gtk_signal_connect (GTK_OBJECT (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button")), "clicked", GTK_SIGNAL_FUNC (on_save_keyword_file_ok_button_clicked), NULL);
	gtk_widget_show (PHOEBE_file_selector);
	}

void on_save_keyword_file_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	/* This function assigns a filename to the keyword file into which the con- */
	/* tents of PHOEBE will be written into. It also checks if that file aready */
	/* exists and if it does, it displays a warning. Finally, when the new file */
	/* is saved, it is appended to the file selection window.                   */

	GtkWidget *warning_window;
	char *filename_str = gtk_file_selection_get_filename (GTK_FILE_SELECTION (PHOEBE_file_selector));

	if (filename_str[strlen(filename_str)-1] == '/')
		{
		/* This means that the output file isn't a file, but a directory!         */
		warning_window = create_notice_window (
			"Notice",
			"Filename choice problem",
		  "Seems that you have accidentally left the",
			"filename blank or selected the directory.",
			gtk_widget_destroy);
		return;
		}
	if (file_exists (filename_str))
		{
		warning_window = create_warning_window (
			"Warning",
			"Overwrite keyword file?",
		  "This will overwrite an existing keyword file.",
			"Are you sure you want to proceed?",
			on_warning_keyword_file_exists_ok_button_clicked,
			gtk_widget_destroy);
		gtk_object_set_data (GTK_OBJECT (PHOEBE), "warning_window", warning_window);
		}
	else
		{
		save_keyword_file (filename_str);
		sprintf (PHOEBE_KEYWORD_FILENAME, "%s", filename_str);

		/* This updates the keyword GUI to contain the saved name: */
		update_keyword_file_list ();

		gtk_signal_disconnect_by_func (GTK_OBJECT (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button")), GTK_SIGNAL_FUNC (on_save_keyword_file_ok_button_clicked), NULL);
		gtk_widget_hide (PHOEBE_file_selector);
		print_to_status_bar ("Keyword File Saved...");
		}
	}

void on_open_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_open_keyword_file);
	}

void on_open_keyword_file_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	char *filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (PHOEBE_open_keyword_file));
	struct stat fileinfo;
	GtkWidget *warning_window;

	/* Let's check whether this file exists and is readable by owner:           */
	stat (filename, &fileinfo);
	if (S_ISREG (fileinfo.st_mode) == 0)
		{
		warning_window = create_notice_window (
			"Warning",
			"Cannot open the keyword file",
		  "The file you have chosen to open doesn't seem",
			"to be a keyword file. Please choose another file.",
			gtk_widget_destroy);
		return;
		}

	/* Let's write this filename to the global variable:                        */
	sprintf (PHOEBE_KEYWORD_FILENAME, "%s", filename);

	open_keyword_file (filename);
	gtk_widget_hide (PHOEBE_open_keyword_file);

	/* We have no callback, so we have to change labels manually:               */
	on_data_lc_filter_changed ();
	on_data_rv_filter_changed ();
	add_filters_to_available_filter_lists ();
	read_in_data_file_specifics ();

	print_to_status_bar ("Keyword File Opened... ");
	}

void on_lc_plot_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_plot_lc);
	}

void on_rv_plot_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_plot_rv);
	}

void on_plot_lc_plot_button_clicked (GtkButton *button, gpointer user_data)
	{
	print_to_status_bar ("LC Plotting Window opened... ");
	plot_lc_plot (x11, NULL);
	}

void on_plot_lc_clear_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *readout_widget;

	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_image_frame");
	draw_image_to_screen (readout_widget, "empty_lc.xpm");

	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_chi2_ptsno_value");
	gtk_label_set_text (GTK_LABEL (readout_widget), "0");

	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_chi2_weighted_sigma_value");
	gtk_label_set_text (GTK_LABEL (readout_widget), "not calculated");

	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_chi2_unweighted_sigma_value");
	gtk_label_set_text (GTK_LABEL (readout_widget), "not calculated");
	}

void on_plot_lc_done_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_plot_lc);	
	}

void on_plot_lc_shift_up_clicked (GtkButton *button, gpointer user_data)
	{
	print_to_status_bar ("Plot Shifted Up...");

	plot_lc_shift_up ();
	}

void on_plot_lc_shift_left_clicked (GtkButton *button, gpointer user_data)
	{
	print_to_status_bar ("Plot Shifted Left...");

	plot_lc_shift_left ();
	}

void on_plot_lc_shift_down_clicked (GtkButton *button, gpointer user_data)
	{
	print_to_status_bar ("Plot Shifted Down...");

	plot_lc_shift_down ();
	}

void on_plot_lc_shift_right_clicked (GtkButton *button, gpointer user_data)
	{
	print_to_status_bar ("Plot Shifted Right...");

	plot_lc_shift_right ();
	}

void on_plot_lc_zoom_in_button_clicked (GtkButton *button, gpointer user_data)
	{
	print_to_status_bar ("Plot Zoomed In...");

	plot_lc_zoom_in ();
	}

void on_plot_lc_zoom_out_button_clicked (GtkButton *button, gpointer user_data)
	{
	print_to_status_bar ("Plot Zoomed Out...");

	plot_lc_zoom_out ();
	}

void on_plot_lc_reset_button_clicked (GtkButton *button, gpointer user_data)
	{
	LC_ZOOM_FACTOR = 0.0;
	LC_X_OFFSET = 0.0;
	LC_Y_OFFSET = 0.0;

	on_plot_lc_plot_button_clicked (GTK_BUTTON (button), NULL);
	}

void on_menu_bar_settings_configure_clicked (GtkMenuItem *menuitem, gpointer user_data)
	{
	/* This callback will fill in the current values to Configuration window.   */
	/* It is very important that this is done here and not in the beginning,    */
	/* because otherwise temporary changes wouldn't be reflected.               */

	GtkWidget *readout_widget;
	
	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_base_directory");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_BASE_DIR);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_source_directory");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_SOURCE_DIR);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_defaults_directory");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_DEFAULTS_DIR);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_working_directory");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_TEMP_DIR);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_data_directory");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_DATA_DIR);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_lc_directory");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_LC_DIR);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_dc_directory");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_DC_DIR);

	if (strcmp (PHOEBE_PLOTTING_PACKAGE, "sm") == 0) readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_sm_switch");
	if (strcmp (PHOEBE_PLOTTING_PACKAGE, "gnuplot") == 0) readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_gnuplot_switch");
	if (strcmp (PHOEBE_PLOTTING_PACKAGE, "pgplot") == 0) readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_pgplot_switch");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_ld_switch");
	if (PHOEBE_LD_SWITCH == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
	if (PHOEBE_LD_SWITCH == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_ld_directory");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_LD_DIR);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_3d_plot_callback_option");
	if (PHOEBE_3D_PLOT_CALLBACK_OPTION == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
	if (PHOEBE_3D_PLOT_CALLBACK_OPTION == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_confirm_on_save");
	if (PHOEBE_CONFIRM_ON_SAVE == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
	if (PHOEBE_CONFIRM_ON_SAVE == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_confirm_on_quit");
	if (PHOEBE_CONFIRM_ON_QUIT == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
	if (PHOEBE_CONFIRM_ON_QUIT == 1) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
	
	gtk_widget_show (PHOEBE_configuration);
	}

void on_configuration_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	/* This function takes the values that are currently in the Configuration   */
	/* window and applies them to the current session. The values do not per-   */
	/* tain after restart.                                                      */

	GtkWidget *readout_widget;
	GtkWidget *notice_window;

	char working_string[255];
	char *working_str = working_string;
	char *readout_str;

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_base_directory");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (PHOEBE_BASE_DIR, "%s", readout_str);

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_source_directory");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (PHOEBE_SOURCE_DIR, "%s", readout_str);

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_defaults_directory");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (PHOEBE_DEFAULTS_DIR, "%s", readout_str);
	if (access (PHOEBE_DEFAULTS_DIR, R_OK) == -1)
		{
		notice_window = create_notice_window (
			"PHOEBE notice",
			"PHOEBE defaults directory selection issue",
			"The directory you have currently chosen to contain the defaults doesn't have",
			"read priviliges. Please change permissions or choose another directory.",
			gtk_widget_destroy);
		return;
		}

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_working_directory");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (PHOEBE_TEMP_DIR, "%s", readout_str);
	if (access (PHOEBE_TEMP_DIR, W_OK) == -1)
		{
		notice_window = create_notice_window (
			"PHOEBE notice",
			"PHOEBE temporary directory selection issue",
			"The directory you have currently chosen to be temporary (storage for temporary files)",
			"doesn't allow you to write to it. Please change permissions or choose another directory.",
			gtk_widget_destroy);
		return;
		}

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_data_directory");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (PHOEBE_DATA_DIR, "%s", readout_str);
	if (access (PHOEBE_DATA_DIR, W_OK) == -1)
		{
		notice_window = create_notice_window (
			"PHOEBE notice",
			"PHOEBE data directory selection issue",
			"The directory you have currently chosen to contain data files doesn't have",
			"write priviliges. Please change permissions or choose another directory.",
			gtk_widget_destroy);
		return;
		}

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_lc_directory");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (PHOEBE_LC_DIR, "%s", readout_str);
	sprintf (working_str, "%s/lc", readout_str);
	if (!file_exists (working_str))
		{
		notice_window = create_notice_window (
			"PHOEBE notice",
			"WD directory selection issue",
			"The directory you have currently chosen to contain WD's lc executable (must be named lc)",
			"doesn't appear to be in. Please check permissions or choose another directory.",
			gtk_widget_destroy);
		return;
		}

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_dc_directory");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (PHOEBE_DC_DIR, "%s", readout_str);
	sprintf (working_str, "%s/dc", readout_str);
	if (!file_exists (working_str))
		{
		notice_window = create_notice_window (
			"PHOEBE notice",
			"WD directory selection issue",
			"The directory you have currently chosen to contain WD's dc executable (must be named dc)",
			"doesn't appear to be in. Please check permissions or choose another directory.",
			gtk_widget_destroy);
		return;
		}

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_sm_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		sprintf (PHOEBE_PLOTTING_PACKAGE, "sm");
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_gnuplot_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		sprintf (PHOEBE_PLOTTING_PACKAGE, "gnuplot");
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_pgplot_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		sprintf (PHOEBE_PLOTTING_PACKAGE, "pgplot");

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_ld_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		PHOEBE_LD_SWITCH = 1;
	else
		PHOEBE_LD_SWITCH = 0;

	if (PHOEBE_LD_SWITCH == 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "ld_vanhamme_interpolation"), FALSE);
	if (PHOEBE_LD_SWITCH == 1) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "ld_vanhamme_interpolation"), TRUE);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_ld_directory");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (PHOEBE_LD_DIR, "%s", readout_str);
	sprintf (working_str, "%s/ld_availability.data", readout_str);
	if ( (PHOEBE_LD_SWITCH == 1) && (!file_exists (working_str)) )
		{
		notice_window = create_notice_window (
			"PHOEBE notice",
			"PHOEBE Limb Darkening directory selection issue",
			"The directory you have currently chosen to contain Van Hamme's LD tables doesn't contain the table",
			"'ld_availability.data', which is necessary. Please check permissions or choose another directory.",
			gtk_widget_destroy);
		return;
		}

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_3d_plot_callback_option");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		PHOEBE_3D_PLOT_CALLBACK_OPTION = 1;
	else
		PHOEBE_3D_PLOT_CALLBACK_OPTION = 0;

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_confirm_on_save");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		PHOEBE_CONFIRM_ON_SAVE = 1;
	else
		PHOEBE_CONFIRM_ON_SAVE = 0;

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_confirm_on_quit");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		PHOEBE_CONFIRM_ON_QUIT = 1;
	else
		PHOEBE_CONFIRM_ON_QUIT = 0;

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_warn_on_synthetic_scatter");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		PHOEBE_WARN_ON_SYNTHETIC_SCATTER = 1;
	else
		PHOEBE_WARN_ON_SYNTHETIC_SCATTER = 0;

	/* Put the devices into the Plot-to-File window:                            */
	create_plot_to_file_drop_down_menu ();

	print_to_status_bar ("Temporary PHOEBE configuration applied. Defaults will be restored after restart.");
	gtk_widget_hide (PHOEBE_configuration);
	}

void on_configuration_save_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *warning_window;

	if (file_exists (PHOEBE_CONFIG))
		{
		warning_window = create_warning_window
			("PHOEBE configuration file already exists",
			 "Overwrite existing PHOEBE configuration?",
			 "A PHOEBE configuration file phoebe.config already exists in PHOEBE home directory.",
			 "Are you sure you want to overwrite it?",
			 on_warning_configuration_file_exists_ok_button_clicked,
			 gtk_widget_destroy);
		gtk_object_set_data (GTK_OBJECT (PHOEBE), "warning_window", warning_window);
		}
	else
		configuration_save_file (GTK_WIDGET (button), user_data);
	}

void on_warning_no_configuration_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *warning_window = lookup_widget (PHOEBE, "warning_window");
	GtkWidget *settings = lookup_widget (PHOEBE, "menu_bar_settings_configuration");

	char working_string[255];
	char *working_str = working_string;

	mkdir (PHOEBE_HOME_DIR, 0755);

	gtk_widget_hide (warning_window);
	on_menu_bar_settings_configure_clicked (GTK_MENU_ITEM (settings), user_data);

	sprintf (working_str, "PHOEBE Configuration directory %s created...", PHOEBE_HOME_DIR);
	print_to_status_bar (working_str);
	}

void on_warning_keyword_file_exists_ok_button_clicked (GtkWidget *widget, gpointer user_data)
	{
	GtkWidget *warning_window = lookup_widget (PHOEBE, "warning_window");
	char *filename_str = gtk_file_selection_get_filename (GTK_FILE_SELECTION (PHOEBE_file_selector));

	gtk_widget_destroy (warning_window);

	save_keyword_file (filename_str);
	sprintf (PHOEBE_KEYWORD_FILENAME, "%s", filename_str);

	gtk_signal_disconnect_by_func (GTK_OBJECT (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button")), GTK_SIGNAL_FUNC (on_save_keyword_file_ok_button_clicked), NULL);
	gtk_widget_hide (PHOEBE_file_selector);
	print_to_status_bar ("Keyword File Overwritten...");
	}

void on_warning_confirm_on_save_ok_button_clicked (GtkWidget *widget, gpointer user_data)
	{
	char working_string[255];
	char *working_str = working_string;

	gtk_widget_destroy (widget);

	save_keyword_file (PHOEBE_KEYWORD_FILENAME);
	sprintf (working_str, "Current keyword file saved to %s.", PHOEBE_KEYWORD_FILENAME);
	print_to_status_bar (working_str);
	}

void on_warning_configuration_file_exists_ok_button_clicked (GtkWidget *widget, gpointer user_data)
	{
	GtkWidget *warning_window = lookup_widget (GTK_WIDGET (PHOEBE), "warning_window");
	gtk_widget_destroy (warning_window);

	configuration_save_file (widget, user_data);
	}

void on_plot_rv_plot_button_clicked (GtkButton *button, gpointer user_data)
	{
	print_to_status_bar ("RV Plotting Window opened... ");
	plot_rv_plot (x11, NULL);
	}

void on_plot_rv_done_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_plot_rv);
	}

void on_plot_rv_shift_up_clicked (GtkButton *button, gpointer user_data)
	{
	plot_rv_shift_up ();
	}

void on_plot_rv_shift_left_clicked (GtkButton *button, gpointer user_data)
	{
	plot_rv_shift_left ();
	}

void on_plot_rv_shift_down_clicked (GtkButton *button, gpointer user_data)
	{
	plot_rv_shift_down ();
	}

void on_plot_rv_shift_right_clicked (GtkButton *button, gpointer user_data)
	{
	plot_rv_shift_right ();
	}

void on_plot_rv_reset_button_clicked (GtkButton *button, gpointer user_data)
	{
	RV_ZOOM_FACTOR = 0.0;
	RV_X_OFFSET = 0.0;
	RV_Y_OFFSET = 0.0;

	on_plot_rv_plot_button_clicked (GTK_BUTTON (button), NULL);
	}

void on_plot_rv_zoom_out_button_clicked (GtkButton *button, gpointer user_data)
	{
	plot_rv_zoom_out ();
	}

void on_plot_rv_zoom_in_button_clicked (GtkButton *button, gpointer user_data)
	{
	plot_rv_zoom_in ();
	}

void on_plot_rv_clear_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *readout_widget;

	readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_image_frame");
	draw_image_to_screen (readout_widget, "empty_rv.xpm");

	readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_chi2_ptsno_value");
	gtk_label_set_text (GTK_LABEL (readout_widget), "0");

	readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_chi2_weighted_sigma_value");
	gtk_label_set_text (GTK_LABEL (readout_widget), "not calculated");

	readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_chi2_unweighted_sigma_value");
	gtk_label_set_text (GTK_LABEL (readout_widget), "not calculated");
	}

void on_plot_lc_dependent_variable_changed (GtkEditable *editable, gpointer user_data)
	{
	/* This function disables data switch if the user chooses to plot such      */
	/* plots where data plotting has no sense. Also, it takes care of what le-  */
	/* vel-dependent value (flux factor) should be displayed.                   */

	GtkWidget *readout_widget;

	GtkWidget *data = lookup_widget (PHOEBE_plot_lc, "plot_lc_experimental_data");
	GtkWidget *lc_no = lookup_widget (PHOEBE, "data_lc_no_value");

	char *readout_str;

	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_dependent_combo_box_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));

	/* Make flux-oriented widgets sensitive only in case of normalized flux:    */
	if (strcmp (readout_str, "Normalized Flux") == 0)
		{
		readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_factor_label");
		gtk_widget_set_sensitive (readout_widget, TRUE);
		readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_factor_value");
		gtk_widget_set_sensitive (readout_widget, TRUE);
		readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_phnorm_label");
		gtk_widget_set_sensitive (readout_widget, TRUE);
		readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_phnorm_value");
		gtk_widget_set_sensitive (readout_widget, TRUE);
		}
	else
		{
		readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_factor_label");
		gtk_widget_set_sensitive (readout_widget, FALSE);
		readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_factor_value");
		gtk_widget_set_sensitive (readout_widget, FALSE);
		readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_phnorm_label");
		gtk_widget_set_sensitive (readout_widget, FALSE);
		readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_phnorm_value");
		gtk_widget_set_sensitive (readout_widget, FALSE);
		}
	}

void on_plot_rv_dependent_variable_changed (GtkEditable *editable, gpointer user_data)
	{
	/* This function disables data switch if the user chooses to plot such      */
	/* plots where data plotting has no sense.                                  */

	GtkWidget *dependent = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_dependent_combo_box_entry");
	GtkWidget *data = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_experimental_data");
	GtkWidget *data_switch = lookup_widget (GTK_WIDGET (PHOEBE_plot_rv), "plot_rv_data_switch");
	GtkWidget *rv_no = lookup_widget (GTK_WIDGET (PHOEBE), "data_rv_no_value");

	char *readout_str;

	readout_str = gtk_entry_get_text (GTK_ENTRY (dependent));

	/* It should make toggle button available only if data is available: */

	if ( ( GTK_TOGGLE_BUTTON (data_switch)->active == TRUE ) &&
	     ( gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (rv_no)) != 0 ) )
		{
		if ( ( strcmp (readout_str, "Primary eclipse-proximity corrections")   == 0 ) ||
		     ( strcmp (readout_str, "Secondary eclipse-proximity corrections") == 0 ) )
					gtk_widget_set_sensitive (GTK_WIDGET (data), FALSE);
		else
					gtk_widget_set_sensitive (GTK_WIDGET (data), TRUE);
		}
	}

void on_ld_interpolation_clicked (GtkButton *button, gpointer user_data)
	{
	set_values_of_ld_window ();
	gtk_widget_show (PHOEBE_ld_interpolation);
	}

void on_ld_interpolation_interpolate_button_clicked (GtkButton *button, gpointer user_data)
	{
	PHOEBE_vector ld_coefs;
	GtkWidget *readout_widget;

	char *readout_str;

	int T;
	double lg, M;
	int ld;
	
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_ldlaw_box_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	if (strcmp (readout_str, "Linear Cosine Law") == 0) ld = 0;
	if (strcmp (readout_str, "Logarithmic Law") == 0)   ld = 1;
	if (strcmp (readout_str, "Square Root Law") == 0)   ld = 2;

	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_filter_box_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));

	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_tavh_value");
	T = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_primary_logg_value");
	lg = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_primary_metallicity_value");
	M = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	
	ld_coefs = interpolate_from_ld_tables (readout_str, T, lg, M, ld);

	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_x1a_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), ld_coefs.x);
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_y1a_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), ld_coefs.y);

	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_tavc_value");
	T = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_secondary_logg_value");
	lg = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_secondary_metallicity_value");
	M = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

	ld_coefs = interpolate_from_ld_tables (readout_str, T, lg, M, ld);

	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_x2a_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), ld_coefs.x);
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_y2a_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), ld_coefs.y);
	}

void on_ld_interpolation_update_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *ld_list;

	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));

	GtkWidget *readout_widget;
	double readout_dbl;

	char *readout_str;

	char working_string[255];
	char *working_str = working_string;

	int i;
	int bolometric = 0;
	int lc_match = 0;
	int rv_match = 0;

	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_filter_box_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));

	if (strcmp (readout_str, "Bolometric") == 0) bolometric = 1;
	else
		{
		/* Check whether we update LC or RV coefficients and assign i to the par- */
		/* ticular filter:                                                        */
		for (i = 0; i < lc_no; i++)
			if (strcmp (readout_str, PHOEBE_lc_data[i].filter) == 0) { lc_match = 1; break; }
		if (lc_match == 0)
			for (i = 0; i < rv_no; i++)
				if (strcmp (readout_str, PHOEBE_rv_data[i].filter) == 0) { rv_match = 1; break; }

		if (lc_match == 1) ld_list = lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list");
		if (rv_match == 1) ld_list = lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list");

		if ( (lc_match == 0) && (rv_match == 0) ) phoebe_fatal ("Severe Logistical Problem in on_ld_interpolation_update_button_clicked ().");
		}
	
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_x1a_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", readout_dbl);
	if (bolometric == 1) gtk_spin_button_set_value (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "ld_xbol1_value")), readout_dbl);
	else gtk_clist_set_text (GTK_CLIST (ld_list), i, 1, working_str);

	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_y1a_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", readout_dbl);
	if (bolometric == 1) gtk_spin_button_set_value (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "ld_ybol1_value")), readout_dbl);
	else gtk_clist_set_text (GTK_CLIST (ld_list), i, 2, working_str);

	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_x2a_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", readout_dbl);
	if (bolometric == 1) gtk_spin_button_set_value (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "ld_xbol2_value")), readout_dbl);
	else gtk_clist_set_text (GTK_CLIST (ld_list), i, 3, working_str);

	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_y2a_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", readout_dbl);
	if (bolometric == 1) gtk_spin_button_set_value (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "ld_ybol2_value")), readout_dbl);
	else gtk_clist_set_text (GTK_CLIST (ld_list), i, 4, working_str);
	}

void on_ld_interpolation_update_all_button_clicked (GtkButton *button, gpointer user_data)
	{
	phoebe_warning ("Function not implemented yet.");
	}

void on_menu_bar_about_clicked (GtkMenuItem *menuitem, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_about);
	print_to_status_bar ("About PHOEBE...");
	}

void on_fitting_chi2_calculate_button_clicked (GtkButton *button, gpointer user_data)
	{
	char filename_str[255];
	char *filename = filename_str;

	sprintf (filename, "%s/phoebe_c2.xpm", PHOEBE_TEMP_DIR);
	plot_chi2_plot (x11, filename);
	}

void on_luminosities_seed_button_clicked (GtkButton *button, gpointer user_data)
	{
	int seed;
	GtkWidget *readout_widget = lookup_widget (PHOEBE, "luminosities_seed_value");

	srand (time (0));
	seed = (int) (100000001.0 + (double) rand () / RAND_MAX * 100000000.0);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), seed);
	}

void on_fitting_mms_value_changed (GtkEditable *editable, gpointer user_data)
	{
	int i;
	int mms_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "fitting_mms_value")));

	const char *mms[] = {"fitting_mms_hbox_1", "fitting_mms_hbox_2", "fitting_mms_hbox_3", "fitting_mms_hbox_4", "fitting_mms_hbox_5"};

	for (i = 0; i < mms_no; i++)
		gtk_widget_set_sensitive (lookup_widget (PHOEBE, mms[i]), TRUE);
	for (i = mms_no; i < 5; i++)
		gtk_widget_set_sensitive (lookup_widget (PHOEBE, mms[i]), FALSE);
	}

void on_utilities_calculate_grid_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *grid_list = lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_list");
	int i;

	char *row1[] = {"1.", "0.30", "5500",  "0.40", "0.10", "0.60", "coupled"};
	char *row2[] = {"2.", "0.40", "6000",  "0.50", "0.15", "0.70", "coupled"};
	char *row3[] = {"3.", "0.50", "7000",  "0.60", "0.20", "0.80", "coupled"};
	char *row4[] = {"4.", "0.60", "8000",  "0.70", "0.25", "0.90", "coupled"};
	char *row5[] = {"5.", "0.70", "8500",  "0.80", "0.30", "1.00", "coupled"};
	char *row6[] = {"6.", "0.75", "9000",  "0.90", "0.35", "1.10", "coupled"};
	char *row7[] = {"7.", "0.80", "9500",  "1.00", "0.40", "1.20", "coupled"};
	char *row8[] = {"8.", "0.90", "10000", "1.10", "0.45", "1.50", "coupled"};

	gtk_clist_clear (GTK_CLIST (grid_list));

	gtk_clist_set_column_title (GTK_CLIST (grid_list), 0, "Node");
	gtk_clist_set_column_title (GTK_CLIST (grid_list), 1, "q");
	gtk_clist_set_column_title (GTK_CLIST (grid_list), 2, "T1[K]");
	gtk_clist_set_column_title (GTK_CLIST (grid_list), 3, "T2/T1");
	gtk_clist_set_column_title (GTK_CLIST (grid_list), 4, "R1/a");
	gtk_clist_set_column_title (GTK_CLIST (grid_list), 5, "R2/R1");
	gtk_clist_set_column_title (GTK_CLIST (grid_list), 6, "i");

	for (i = 0; i < 7; i++)
		gtk_clist_set_column_justification (GTK_CLIST (grid_list), i, GTK_JUSTIFY_FILL);
	gtk_clist_append (GTK_CLIST (grid_list), row1);
	gtk_clist_append (GTK_CLIST (grid_list), row2);
	gtk_clist_append (GTK_CLIST (grid_list), row3);
	gtk_clist_append (GTK_CLIST (grid_list), row4);
	gtk_clist_append (GTK_CLIST (grid_list), row5);
	gtk_clist_append (GTK_CLIST (grid_list), row6);
	gtk_clist_append (GTK_CLIST (grid_list), row7);
	gtk_clist_append (GTK_CLIST (grid_list), row8);

	gtk_widget_show (PHOEBE_calculate_grid);
	}

void on_utilities_use_grid_button_clicked (GtkButton *button, gpointer user_data)
	{
	
	}

void on_synthetic_grid_calculate_button_clicked (GtkButton *button, gpointer user_data)
	{
	int i, j;
	char *readout_str;

	GtkWidget *grid_list   = lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_list");

	int params_no   = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_params_value")));
	int nodes_no    = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_nodes_value")));
	int vertexes_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_vertexes_value")));
	int filters_no  = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_filters_value")));

	double grid_nodes[6][8];

	/* These will go to the calculation function: */

	double R;
	int i0, i1, i2, i3, i4, i5;
	int filt;

	char working_string[255];
	char *working_str = working_string;

	PHOEBE_main_parameters main;
	PHOEBE_switches switches;
	PHOEBE_curve_parameters curve;
	PHOEBE_limb_darkening ld;
	PHOEBE_spots spots;
	PHOEBE_wl_dependent_parameters mono;

	int syn_points;
	PHOEBE_vector *syn_data = NULL;

	FILE *grid_file;

	GtkWidget *progress_bar = lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_progress_bar");
	double percentage = 0.0;

	GtkWidget *notice_window;

	char *filter_names[] = {"synthetic_grid_filter_1_entry", "synthetic_grid_filter_2_entry", "synthetic_grid_filter_3_entry"};

	time_t current_time;
	
	for (i = 0; i < params_no; i++)
		for (j = 0; j < nodes_no; j++)
			{
			gtk_clist_get_text (GTK_CLIST (grid_list), j, i+1, &readout_str);
			if (strcmp (readout_str, "coupled") != 0)
				grid_nodes[i][j] = atof (readout_str);
			else
				grid_nodes[i][j] = -1.0;                      /* change to sqrt (-1)? */
			}

	/* The basic idea now would be to call the calculation function located so- */
	/* mewhere else, but right now we shall keep it here for testing purposes!  */

	/* Initialize constant parameters: */
	main.SMA     = 1.0;    switches.MPAGE   = 1;    ld.LD        = 1;
	main.PERIOD  = 1.0;    switches.MODE    = 2;    ld.XBOL1     = 1.0;
	main.HJD0    = 0.5;    switches.NLC     = 0;    ld.XBOL2     = 1.0;
	main.VGA     = 0.0;    switches.IFVC1   = 0;    ld.YBOL1     = 1.0;
	main.GR1     = 1.0;    switches.IFVC2   = 0;    ld.YBOL2     = 1.0;
	main.GR2     = 1.0;    switches.BINNING = 0;
	main.ALB1    = 1.0;    switches.BINNO   = 0;    spots.IFSMV1 = 0.0;
	main.ALB2    = 1.0;    switches.NPPL    = 1;    spots.IFSMV2 = 0.0;
	main.F1      = 1.0;    switches.MREF    = 0;    spots.KSPA   = 0.0;
	main.F2      = 1.0;    switches.NREF    = 0;    spots.NSPA   = 0.0;
	main.E       = 0.0;    switches.ICOR1   = 0;    spots.KSPB   = 0.0;
	main.PERR0   = 0.0;    switches.ICOR2   = 0;    spots.NSPB   = 0.0;
	main.DPERDT  = 0.0;    switches.JDPHS   = 2;    
	main.DPDT    = 0.0;    switches.NOISE   = 0;    
	main.PSHIFT  = 0.0;    switches.IPB     = 0;    
                         switches.IFAT1   = 0;    
  curve.PHNORM = 0.25;   switches.IFAT2   = 0;    
  curve.FACTOR = 1.0;    switches.N1      = 30;   
  curve.HJDST  = 0.0;    switches.N2      = 30;   
  curve.HJDSP  = 1.0;    switches.N1L     = 5;    
  curve.HJDIN  = 0.0;    switches.N2L     = 5;
  curve.PHSTRT = -0.5;   switches.ISYM    = 0;    mono.HLA     = 10.0;
  curve.PHSTOP = 0.5;    switches.K0      = 0;    mono.CLA     = 10.0;
                         switches.KDISK   = 0;    mono.X1A     = 1.0;
                         switches.THE     = 0;    mono.X2A     = 1.0;
                                                  mono.Y1A     = 1.0;
                                                  mono.Y2A     = 1.0;
  curve.PHIN  = 1.0 / (vertexes_no - 1);          mono.EL3     = 0.0;
                                                  mono.OPSF    = 0.0;
                                                  mono.SIGMA   = 1.0;

	for (i = 0; i < filters_no; i++)
		{
		readout_str = gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE_calculate_grid, filter_names[i])));
		if (strcmp (readout_str, "Undefined") == 0)
			{
			notice_window = create_notice_window ("PHOEBE Notice", "PHOEBE Notice: Filter missing", "You have not assigned enough filters in the", "calculation window. Please supply the missing information!", gtk_widget_destroy);
			return;
			}
		}

	grid_file = fopen ("src/grid.data", "w");

	/* Let's create a small header file:                                        */
	current_time = time (NULL);
	fprintf (grid_file, "# PHOEBE synthetic LC grid created:  %s", asctime (localtime(&current_time)));
	fprintf (grid_file, "#\n");
	fprintf (grid_file, "# Number of gridded parameters:      %d\n", params_no);
	fprintf (grid_file, "# Number of nodes per parameter:     %d\n", nodes_no);
	fprintf (grid_file, "# Number of vertexes per lightcurve: %d\n", vertexes_no);
	fprintf (grid_file, "# Number of used filters:            %d\n", filters_no);
	fprintf (grid_file, "#\n");
	for (i = 0; i < params_no; i++)
		{
		readout_str = gtk_clist_get_column_title (GTK_CLIST (grid_list), i+1);
		fprintf (grid_file, "# P%d: %6s: ", i+1, readout_str);
		for (j = 0; j < nodes_no; j++)
			{
			if (grid_nodes[i][j] > 0) fprintf (grid_file, "%9.2lf", grid_nodes[i][j]);
			else                      fprintf (grid_file, "%9s", "coupled");
			}
		fprintf (grid_file, "\n");
		}
	fprintf (grid_file, "#\n");
	for (i = 0; i < filters_no; i++)
		{
		readout_str = gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE_calculate_grid, filter_names[i])));
		fprintf (grid_file, "# F%d: %15s\n", i+1, readout_str);
		}
	fprintf (grid_file, "#\n");

	gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_calculate_button")), FALSE);

	for (i0 = 0; i0 < nodes_no; i0++)
		{
		main.RM = grid_nodes[0][i0];

		for (i1 = 0; i1 < nodes_no; i1++)
			{
			main.TAVH = grid_nodes[1][i1];

			for (i2 = 0; i2 < nodes_no; i2++)
				{
				main.TAVC = main.TAVH * grid_nodes[2][i2];

				for (i3 = 0; i3 < nodes_no; i3++)
					{
					R = grid_nodes[3][i3];
					main.PHSV = calculate_phsv_value (0, 1, main.RM, R, 1, 0, 0);
					main.PCSV = calculate_pcsv_value (0, 1, main.RM, R, 1, 0, 0);

					for (i4 = 0; i4 < nodes_no; i4++)
						{
						for (i5 = 0; i5 < nodes_no; i5++)
							{
							main.XINCL = 90.0 - i5 * 180.0 / 7.0 / M_PI * acos (R + R * grid_nodes[4][i4]);

							for (filt = 0; filt < filters_no; filt++)
								{
								readout_str = gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE_calculate_grid, filter_names[filt])));
								sscanf (readout_str, "%lf nm", &mono.WLA);

								create_lci_input_file ("phoebe_lc", main, switches, ld, spots, curve, mono);

								i = scan_temporary_directory_for_lci_file_index ("phoebe_lc");
								sprintf (working_str, "%s/lc < %s/phoebe_lc_%03d.lci > %s/phoebe_lc_%03d.lco", PHOEBE_LC_DIR, PHOEBE_TEMP_DIR, i, PHOEBE_TEMP_DIR, i);
								system (working_str);
/* FIX ME !!! */ /*
								syn_points = get_synthetic_data (2, 6, &syn_data, PHOEBE_lc);
*/ /* ********** */
								for (i = 0; i < syn_points; i++) fprintf (grid_file, "%f", (float) syn_data[i].y);
								fprintf (grid_file, "\n");

								while (gtk_events_pending()) gtk_main_iteration ();
								percentage += 1.0 / pow (nodes_no, 6) / filters_no;
								gtk_progress_bar_update (GTK_PROGRESS_BAR (progress_bar), percentage);
								}
							}
						}
					}
				}
			}
		}

	fclose (grid_file);

	gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_calculate_button")), TRUE);
	gtk_label_set_text (GTK_LABEL (GTK_BIN (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_cancel_button"))->child), "OK");
	}

void on_synthetic_grid_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_calculate_grid);
	}

void on_synthetic_grid_filters_value_changed (GtkEditable *editable, gpointer user_data)
	{
	int params_no   = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_params_value")));
	int nodes_no    = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_nodes_value")));
	int vertexes_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_vertexes_value")));
	int filters_no  = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_filters_value")));

	char working_string[255];
	char *working_str = working_string;

	int i;

	char *widgets[] = {"synthetic_grid_filter_1_combo", "synthetic_grid_filter_2_combo", "synthetic_grid_filter_3_combo"};
	
	for (i = 0; i < filters_no; i++)
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_calculate_grid, widgets[i])), TRUE);
	for (i = filters_no; i < 3; i++)
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_calculate_grid, widgets[i])), FALSE);

	calculate_estimated_synthetic_grid_file_size (params_no, nodes_no, vertexes_no, filters_no, &working_str);
	gtk_label_set_text (GTK_LABEL (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_size_label")), working_str);
	}

void on_synthetic_grid_params_value_changed (GtkEditable *editable, gpointer user_data)
	{
	int params_no   = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_params_value")));
	int nodes_no    = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_nodes_value")));
	int vertexes_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_vertexes_value")));
	int filters_no  = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_filters_value")));

	char working_string[255];
	char *working_str = working_string;

	calculate_estimated_synthetic_grid_file_size (params_no, nodes_no, vertexes_no, filters_no, &working_str);
	gtk_label_set_text (GTK_LABEL (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_size_label")), working_str);
	}

void on_synthetic_grid_vertexes_value_changed (GtkEditable *editable, gpointer user_data)
	{
	int params_no   = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_params_value")));
	int nodes_no    = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_nodes_value")));
	int vertexes_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_vertexes_value")));
	int filters_no  = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_filters_value")));

	char working_string[255];
	char *working_str = working_string;

	calculate_estimated_synthetic_grid_file_size (params_no, nodes_no, vertexes_no, filters_no, &working_str);
	gtk_label_set_text (GTK_LABEL (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_size_label")), working_str);
	}

void on_synthetic_grid_nodes_value_changed (GtkEditable *editable, gpointer user_data)
	{
	int params_no   = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_params_value")));
	int nodes_no    = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_nodes_value")));
	int vertexes_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_vertexes_value")));
	int filters_no  = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_filters_value")));

	char working_string[255];
	char *working_str = working_string;

	GtkWidget *grid_list = lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_list");
	int rows_already_present = GTK_CLIST (grid_list)->rows;
	int i;

	char entry_string[7][10];
	char *entry[7] = {entry_string[0], entry_string[1], entry_string[2], entry_string[3], entry_string[4], entry_string[5], entry_string[6]};

	if (nodes_no < rows_already_present)
		{
		for (i = rows_already_present; i > nodes_no; i--)
			gtk_clist_remove (GTK_CLIST (grid_list), i-1);
		}

	if (nodes_no > rows_already_present)
		for (i = rows_already_present; i < nodes_no; i++)
			{
			sprintf (entry[0], "%d.", i+1);
			sprintf (entry[1], "1.0");
			sprintf (entry[2], "6000");
			sprintf (entry[3], "1.0");
			sprintf (entry[4], "0.1");
			sprintf (entry[5], "1.0");
			sprintf (entry[6], "coupled");

			gtk_clist_append (GTK_CLIST (grid_list), entry);
			}

	calculate_estimated_synthetic_grid_file_size (params_no, nodes_no, vertexes_no, filters_no, &working_str);
	gtk_label_set_text (GTK_LABEL (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_size_label")), working_str);
	}

void on_synthetic_grid_edit_entry_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *grid_list = lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_list");
	int selected_row = (int) ((GList *) (GTK_CLIST (grid_list)->selection))->data;

	GtkWidget *readout_widget;
	char *readout_str;

	char working_string[255];
	char *working_str = working_string;

	readout_widget = lookup_widget (PHOEBE_calculate_grid_edit_parameters, "synthetic_grid_parameters_main_label");
	sprintf (working_str, "Synthetic Grid Entry at Node %d:", selected_row + 1);
	gtk_label_set_text (GTK_LABEL (readout_widget), working_str);

	readout_widget = lookup_widget (PHOEBE_calculate_grid_edit_parameters, "synthetic_grid_parameters_q_value");
	gtk_clist_get_text (GTK_CLIST (grid_list), selected_row, 1, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_calculate_grid_edit_parameters, "synthetic_grid_parameters_T1_value");
	gtk_clist_get_text (GTK_CLIST (grid_list), selected_row, 2, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_calculate_grid_edit_parameters, "synthetic_grid_parameters_T2T1_value");
	gtk_clist_get_text (GTK_CLIST (grid_list), selected_row, 3, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_calculate_grid_edit_parameters, "synthetic_grid_parameters_R1a_value");
	gtk_clist_get_text (GTK_CLIST (grid_list), selected_row, 4, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_calculate_grid_edit_parameters, "synthetic_grid_parameters_R2R1_value");
	gtk_clist_get_text (GTK_CLIST (grid_list), selected_row, 5, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	/* Unfortunately, this line must be commented, otherwise double-clicking    */
	/* doesn't work (disabling grid_list disables "event" callback too).        */

	/* gtk_widget_set_sensitive (grid_list, FALSE); */

	gtk_widget_show (PHOEBE_calculate_grid_edit_parameters);
	}

gboolean on_synthetic_grid_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data)
	{
	GtkWidget *grid_list = lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_list");

	if ( event->type == GDK_2BUTTON_PRESS )
		on_synthetic_grid_edit_entry_button_clicked (GTK_BUTTON (lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_edit_entry_button")), (gpointer) grid_list);

	return FALSE;
	}

void on_synthetic_grid_parameters_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *grid_list = lookup_widget (PHOEBE_calculate_grid, "synthetic_grid_list");
	int selected_row = (int) ((GList *) (GTK_CLIST (grid_list)->selection))->data;

	GtkWidget *readout_widget;
	double readout_dbl;
	int readout_int;

	char working_string[255];
	char *working_str = working_string;

	readout_widget = lookup_widget (PHOEBE_calculate_grid_edit_parameters, "synthetic_grid_parameters_q_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%2.2lf", readout_dbl);
	gtk_clist_set_text (GTK_CLIST (grid_list), selected_row, 1, working_str);

	readout_widget = lookup_widget (PHOEBE_calculate_grid_edit_parameters, "synthetic_grid_parameters_T1_value");
	readout_int = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%d", readout_int);
	gtk_clist_set_text (GTK_CLIST (grid_list), selected_row, 2, working_str);

	readout_widget = lookup_widget (PHOEBE_calculate_grid_edit_parameters, "synthetic_grid_parameters_T2T1_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%2.2lf", readout_dbl);
	gtk_clist_set_text (GTK_CLIST (grid_list), selected_row, 3, working_str);

	readout_widget = lookup_widget (PHOEBE_calculate_grid_edit_parameters, "synthetic_grid_parameters_R1a_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%2.2lf", readout_dbl);
	gtk_clist_set_text (GTK_CLIST (grid_list), selected_row, 4, working_str);

	readout_widget = lookup_widget (PHOEBE_calculate_grid_edit_parameters, "synthetic_grid_parameters_R2R1_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%2.2lf", readout_dbl);
	gtk_clist_set_text (GTK_CLIST (grid_list), selected_row, 5, working_str);

	gtk_widget_hide (PHOEBE_calculate_grid_edit_parameters);
	}

void on_synthetic_grid_parameters_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_calculate_grid_edit_parameters);
	}

void on_data_lc_edit_data_entry_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *lc_list = lookup_widget (PHOEBE, "data_lc_info_list");
	int selected_row = (int) ((GList *) (GTK_CLIST (lc_list)->selection))->data;

	GtkWidget *readout_widget;

	readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_column_1_entry");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_lc_data[selected_row].column1);

	readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_column_2_entry");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_lc_data[selected_row].column2);

	readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_column_3_entry");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_lc_data[selected_row].column3);
	
	readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_filename_entry");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_lc_data[selected_row].filename);

	readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_sigma_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (PHOEBE_lc_data[selected_row].sigma));

	readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_filter_button");
	gtk_label_set_text (GTK_LABEL (GTK_BIN(readout_widget)->child), PHOEBE_lc_data[selected_row].filter);

	gtk_widget_show (PHOEBE_assign_data_file);
	}

gboolean on_data_lc_info_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data)
	{
	GtkWidget *lc_list = lookup_widget (PHOEBE, "data_lc_info_list");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));

	if ( (event->type == GDK_2BUTTON_PRESS) && (lc_no != 0) )
		on_data_lc_edit_data_entry_button_clicked (GTK_BUTTON (lookup_widget (PHOEBE, "data_lc_edit_data_entry_button")), (gpointer) lc_list);

	return FALSE;
	}

void on_data_rv_edit_data_entry_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *rv_list = lookup_widget (PHOEBE, "data_rv_info_list");
	int selected_row = (int) ((GList *) (GTK_CLIST (rv_list)->selection))->data;

	GtkWidget *readout_widget;

	readout_widget = lookup_widget (PHOEBE_assign_rv_data_file, "data_file_column_1_entry");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_rv_data[selected_row].column1);

	readout_widget = lookup_widget (PHOEBE_assign_rv_data_file, "data_file_column_2_entry");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_rv_data[selected_row].column2);

	readout_widget = lookup_widget (PHOEBE_assign_rv_data_file, "data_file_column_3_entry");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_rv_data[selected_row].column3);
	
	readout_widget = lookup_widget (PHOEBE_assign_rv_data_file, "data_file_filename_entry");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), PHOEBE_rv_data[selected_row].filename);

	readout_widget = lookup_widget (PHOEBE_assign_rv_data_file, "data_file_sigma_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (PHOEBE_rv_data[selected_row].sigma));

	readout_widget = lookup_widget (PHOEBE_assign_rv_data_file, "data_file_filter_button");
	gtk_label_set_text (GTK_LABEL (GTK_BIN(readout_widget)->child), PHOEBE_rv_data[selected_row].filter);

	gtk_widget_show (PHOEBE_assign_rv_data_file);
	}

gboolean on_data_rv_info_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data)
	{
	GtkWidget *rv_list = lookup_widget (PHOEBE, "data_rv_info_list");
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));

	if ( (event->type == GDK_2BUTTON_PRESS) && (rv_no != 0) )
		on_data_rv_edit_data_entry_button_clicked (GTK_BUTTON (lookup_widget (PHOEBE, "data_rv_edit_data_entry_button")), (gpointer) rv_list);

	return FALSE;
	}

void on_data_rv_file_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *rv_list = lookup_widget (PHOEBE, "data_rv_info_list");

	int selected_row = (int) ((GList *) (GTK_CLIST (rv_list)->selection))->data;

	read_in_data_file_info (PHOEBE_assign_rv_data_file, &PHOEBE_rv_data[selected_row]);

	/* And now let's fill that row with new information:                        */
	gtk_clist_set_text (GTK_CLIST (rv_list), selected_row, 1, PHOEBE_rv_data[selected_row].filename);
	gtk_clist_set_text (GTK_CLIST (rv_list), selected_row, 2, PHOEBE_rv_data[selected_row].sigma);
	gtk_clist_set_text (GTK_CLIST (rv_list), selected_row, 3, PHOEBE_rv_data[selected_row].filter);

	/* Since we have no callback for changing labels, we have to do it manual-  */
	/* ly:                                                                      */
	on_data_rv_filter_changed ();
	add_filters_to_available_filter_lists ();

	/* Finally, let's hide the window and return to the main window.            */
	gtk_widget_hide (PHOEBE_assign_rv_data_file);
	}

void on_data_rv_file_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_assign_rv_data_file);
	}

void on_data_file_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *lc_list = lookup_widget (PHOEBE, "data_lc_info_list");

	int selected_row = (int) ((GList *) (GTK_CLIST (lc_list)->selection))->data;

	read_in_data_file_info (PHOEBE_assign_data_file, &PHOEBE_lc_data[selected_row]);

	/* And now let's fill that row with new information:                        */
	gtk_clist_set_text (GTK_CLIST (lc_list), selected_row, 1, PHOEBE_lc_data[selected_row].filename);
	gtk_clist_set_text (GTK_CLIST (lc_list), selected_row, 2, PHOEBE_lc_data[selected_row].sigma);
	gtk_clist_set_text (GTK_CLIST (lc_list), selected_row, 3, PHOEBE_lc_data[selected_row].filter);

	/* Since we have no callback for changing labels, we have to do it manual-  */
	/* ly:                                                                      */
	on_data_lc_filter_changed ();
	add_filters_to_available_filter_lists ();

	/* Finally, let's hide the window and return to the main window.            */
	gtk_widget_hide (PHOEBE_assign_data_file);

	return;
	}

void on_data_file_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_assign_data_file);
	}

void on_data_file_browse_button_clicked (GtkButton *button, gpointer user_data)
	{
	/* Function description... */

	/* We don't want to have file selection widgets for each different browse   */
	/* button, so we make a following trick: we assign an "output_entry" name   */
	/* to the calling entry widget; this is stored in user_data. The widget may */
	/* be either PHOEBE_assign_data_file for LCs or PHOEBE_assign_rv_data_file  */
	/* for RVs. Entry widgets in both parents have the same local names, so it  */
	/* it is safe to declare it this way. This declaration in no way overrides  */
	/* the original name declaration.                                           */
	gtk_object_set_data (GTK_OBJECT (PHOEBE_open_data_file), "output_entry", lookup_widget (GTK_WIDGET (user_data), "data_file_filename_entry"));

	gtk_widget_show (PHOEBE_open_data_file);
	}

void on_luminosities_lc_edit_entry_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *lc_list = lookup_widget (PHOEBE, "luminosities_lc_info_list");
	GtkWidget *readout_widget;

	int selected_row;
	char *readout_str;

	/* Let's find the selected row:                                             */
	selected_row = (int) ((GList *) (GTK_CLIST (lc_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_filter_value");
	gtk_clist_get_text (GTK_CLIST (lc_list), selected_row, 0, &readout_str);
	gtk_label_set_text (GTK_LABEL (readout_widget), readout_str);

	readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_hla_value");
	gtk_clist_get_text (GTK_CLIST (lc_list), selected_row, 1, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_value");
	gtk_clist_get_text (GTK_CLIST (lc_list), selected_row, 2, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	gtk_widget_show (PHOEBE_assign_lc_luminosity);
	}

gboolean on_luminosities_lc_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data)
	{
	GtkWidget *lc_list = lookup_widget (PHOEBE, "luminosities_lc_info_list");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));

	if ( (event->type == GDK_2BUTTON_PRESS) && (lc_no != 0) )
		on_luminosities_lc_edit_entry_button_clicked (GTK_BUTTON (lookup_widget (PHOEBE, "luminosities_lc_edit_entry_button")), (gpointer) lc_list);

	return FALSE;
	}

void on_assign_lc_luminosity_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *lc_list = lookup_widget (PHOEBE, "luminosities_lc_info_list");
	GtkWidget *readout_widget;

	int selected_row;
	double value;

	char working_string[255];
	char *working_str = working_string;

	char *readout_str;

	/* Let's find the selected row:                                             */
	selected_row = (int) ((GList *) (GTK_CLIST (lc_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_hla_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%5.5lf", value);
	gtk_clist_set_text (GTK_CLIST (lc_list), selected_row, 1, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%5.5lf", value);
	gtk_clist_set_text (GTK_CLIST (lc_list), selected_row, 2, working_str);

	gtk_widget_hide (PHOEBE_assign_lc_luminosity);
	}

void on_assign_lc_luminosity_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_assign_lc_luminosity);
	}

void on_defaults_button_clicked (GtkButton *button, gpointer user_data)
	{
	char filename_string[255];
	char *filename = filename_string;

	GtkWidget *notice_window;

	sprintf (filename, "%s/default.phoebe", PHOEBE_DEFAULTS_DIR);

	if (file_exists (filename))
		{
		open_keyword_file (filename);
		sprintf (PHOEBE_KEYWORD_FILENAME, "Undefined");
		print_to_status_bar ("Defaults restored.");
		}
	else
		notice_window = create_notice_window (
			"PHOEBE Notice",
			"PHOEBE Notice: Defaults file cannot be found",
			"The defaults file, \"default.phoebe\", resides in PHOEBE defaults directory.", "Please verify the path to the defaults directory in Settings->Configuration menu.",
			 gtk_widget_destroy);
	}

gboolean on_luminosities_el3_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data)
	{
	GtkWidget *el3_list = lookup_widget (PHOEBE, "luminosities_el3_info_list");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));

	if ( (event->type == GDK_2BUTTON_PRESS) && (lc_no != 0) )
		on_luminosities_el3_edit_entry_button_clicked (GTK_BUTTON (lookup_widget (PHOEBE, "luminosities_el3_edit_entry_button")), (gpointer) el3_list);

	return FALSE;
	}

void on_luminosities_el3_edit_entry_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *el3_list = lookup_widget (PHOEBE, "luminosities_el3_info_list");
	GtkWidget *readout_widget;

	int selected_row;
	char *readout_str;

	/* Let's find the selected row:                                             */
	selected_row = (int) ((GList *) (GTK_CLIST (el3_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_assign_el3, "assign_el3_filter_value");
	gtk_clist_get_text (GTK_CLIST (el3_list), selected_row, 0, &readout_str);
	gtk_label_set_text (GTK_LABEL (readout_widget), readout_str);

	readout_widget = lookup_widget (PHOEBE_assign_el3, "assign_el3_el3_value");
	gtk_clist_get_text (GTK_CLIST (el3_list), selected_row, 1, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_el3, "assign_el3_opsf_value");
	gtk_clist_get_text (GTK_CLIST (el3_list), selected_row, 2, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	gtk_widget_show (PHOEBE_assign_el3);
	}

void on_assign_el3_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *el3_list = lookup_widget (PHOEBE, "luminosities_el3_info_list");
	GtkWidget *readout_widget;

	int selected_row;
	double value;

	char *readout_str;

	char working_string[255];
	char *working_str = working_string;

	/* Let's find the selected row:                                             */
	selected_row = (int) ((GList *) (GTK_CLIST (el3_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_assign_el3, "assign_el3_el3_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", value);
	gtk_clist_set_text (GTK_CLIST (el3_list), selected_row, 1, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_el3, "assign_el3_opsf_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", value);
	gtk_clist_set_text (GTK_CLIST (el3_list), selected_row, 2, working_str);

	gtk_widget_hide (PHOEBE_assign_el3);
	}

void on_assign_el3_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_assign_el3);
	}

gboolean on_ld_monochromatic_lc_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data)
	{
	GtkWidget *ld_list = lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));

	if ( (event->type == GDK_2BUTTON_PRESS) && (lc_no != 0) )
		on_ld_monochromatic_lc_edit_entry_button_clicked (GTK_BUTTON (lookup_widget (PHOEBE, "luminosities_lc_edit_entry_button")), (gpointer) ld_list);

	return FALSE;
	}

void on_ld_monochromatic_lc_edit_entry_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *ld_list = lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list");
	GtkWidget *readout_widget;

	int selected_row;
	char *readout_str;

	/* Let's find the selected row:                                             */
	selected_row = (int) ((GList *) (GTK_CLIST (ld_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_lc, "assign_ld_monochromatic_lc_filter_value");
	gtk_clist_get_text (GTK_CLIST (ld_list), selected_row, 0, &readout_str);
	gtk_label_set_text (GTK_LABEL (readout_widget), readout_str);

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_lc, "assign_ld_monochromatic_lc_x1a_value");
	gtk_clist_get_text (GTK_CLIST (ld_list), selected_row, 1, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_lc, "assign_ld_monochromatic_lc_y1a_value");
	gtk_clist_get_text (GTK_CLIST (ld_list), selected_row, 2, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_lc, "assign_ld_monochromatic_lc_x2a_value");
	gtk_clist_get_text (GTK_CLIST (ld_list), selected_row, 3, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_lc, "assign_ld_monochromatic_lc_y2a_value");
	gtk_clist_get_text (GTK_CLIST (ld_list), selected_row, 4, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	gtk_widget_show (PHOEBE_assign_ld_monochromatic_lc);
	}

void on_assign_ld_monochromatic_lc_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *ld_list = lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list");
	GtkWidget *readout_widget;

	int selected_row;
	double value;

	char *readout_str;

	char working_string[255];
	char *working_str = working_string;

	/* Let's find the selected row:                                             */
	selected_row = (int) ((GList *) (GTK_CLIST (ld_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_lc, "assign_ld_monochromatic_lc_x1a_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", value);
	gtk_clist_set_text (GTK_CLIST (ld_list), selected_row, 1, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_lc, "assign_ld_monochromatic_lc_y1a_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", value);
	gtk_clist_set_text (GTK_CLIST (ld_list), selected_row, 2, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_lc, "assign_ld_monochromatic_lc_x2a_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", value);
	gtk_clist_set_text (GTK_CLIST (ld_list), selected_row, 3, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_lc, "assign_ld_monochromatic_lc_y2a_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", value);
	gtk_clist_set_text (GTK_CLIST (ld_list), selected_row, 4, working_str);

	gtk_widget_hide (PHOEBE_assign_ld_monochromatic_lc);
	}

void on_assign_ld_monochromatic_lc_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_assign_ld_monochromatic_lc);
	}

gboolean on_luminosities_weighting_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data)
	{
	GtkWidget *w_list = lookup_widget (PHOEBE, "luminosities_weighting_info_list");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));

	if ( (event->type == GDK_2BUTTON_PRESS) && (lc_no != 0) )
		on_luminosities_weighting_edit_entry_button_clicked (GTK_BUTTON (lookup_widget (PHOEBE, "luminosities_weighting_edit_entry_button")), (gpointer) w_list);

	return FALSE;
	}

void on_luminosities_weighting_edit_entry_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *w_list = lookup_widget (PHOEBE, "luminosities_weighting_info_list");
	GtkWidget *readout_widget;

	int selected_row;

	char *readout_str;

	/* Let's find the selected row:                                             */
	selected_row = (int) ((GList *) (GTK_CLIST (w_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_assign_weighting, "assign_weighting_weighting_list_entry");
	gtk_clist_get_text (GTK_CLIST (w_list), selected_row, 1, &readout_str);
	gtk_entry_set_text (GTK_ENTRY (readout_widget), readout_str);

	gtk_widget_show (PHOEBE_assign_weighting);
	}

gboolean on_spots_primary_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data)
	{
	GtkWidget *w_list = lookup_widget (PHOEBE, "spots_primary_info_list");

	if (event->type == GDK_2BUTTON_PRESS)
		on_spots_edit_primary_button_clicked (GTK_BUTTON (lookup_widget (PHOEBE, "spots_edit_primary_button")), (gpointer) w_list);

	return FALSE;
	}

void on_spots_edit_primary_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *readout_widget;
	GtkWidget *sp_list = lookup_widget (PHOEBE, "spots_primary_info_list");
	int selected_row = (int) ((GList *) (GTK_CLIST (sp_list)->selection))->data;
	char *readout_str;
	
	readout_widget = lookup_widget (PHOEBE_assign_primary_spots, "assign_spots_xlat_value");
	gtk_clist_get_text (GTK_CLIST (sp_list), selected_row, 1, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_primary_spots, "assign_spots_xlong_value");
	gtk_clist_get_text (GTK_CLIST (sp_list), selected_row, 2, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_primary_spots, "assign_spots_radsp_value");
	gtk_clist_get_text (GTK_CLIST (sp_list), selected_row, 3, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_primary_spots, "assign_spots_temsp_value");
	gtk_clist_get_text (GTK_CLIST (sp_list), selected_row, 4, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	gtk_widget_show (PHOEBE_assign_primary_spots);
	}

gboolean on_spots_secondary_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data)
	{
	GtkWidget *w_list = lookup_widget (PHOEBE, "spots_secondary_info_list");

	if (event->type == GDK_2BUTTON_PRESS)
		on_spots_edit_secondary_button_clicked (GTK_BUTTON (lookup_widget (PHOEBE, "spots_edit_secondary_button")), (gpointer) w_list);

	return FALSE;
	}

void on_spots_edit_secondary_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *readout_widget;
	GtkWidget *sp_list = lookup_widget (PHOEBE, "spots_secondary_info_list");
	int selected_row = (int) ((GList *) (GTK_CLIST (sp_list)->selection))->data;
	char *readout_str;
	
	readout_widget = lookup_widget (PHOEBE_assign_secondary_spots, "assign_spots_xlat_value");
	gtk_clist_get_text (GTK_CLIST (sp_list), selected_row, 1, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_secondary_spots, "assign_spots_xlong_value");
	gtk_clist_get_text (GTK_CLIST (sp_list), selected_row, 2, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_secondary_spots, "assign_spots_radsp_value");
	gtk_clist_get_text (GTK_CLIST (sp_list), selected_row, 3, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_secondary_spots, "assign_spots_temsp_value");
	gtk_clist_get_text (GTK_CLIST (sp_list), selected_row, 4, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	gtk_widget_show (PHOEBE_assign_secondary_spots);
	}

void on_assign_weighting_ok_button_clicked  (GtkButton *button, gpointer user_data)
	{
	GtkWidget *w_list = lookup_widget (PHOEBE, "luminosities_weighting_info_list");
	GtkWidget *readout_widget;

	int selected_row;

	char *readout_str;

	/* Let's find the selected row:                                             */
	selected_row = (int) ((GList *) (GTK_CLIST (w_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_assign_weighting, "assign_weighting_weighting_list_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	gtk_clist_set_text (GTK_CLIST (w_list), selected_row, 1, readout_str);

	gtk_widget_hide (PHOEBE_assign_weighting);
	}

void on_assign_weighting_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_assign_weighting);
	}

gboolean on_ld_monochromatic_rv_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data)
	{
	GtkWidget *ld_list = lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list");
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));

	if ( (event->type == GDK_2BUTTON_PRESS) && (rv_no != 0) )
		on_ld_monochromatic_rv_edit_entry_button_clicked (GTK_BUTTON (lookup_widget (PHOEBE, "luminosities_rv_edit_entry_button")), (gpointer) ld_list);

	return FALSE;
	}

void on_ld_monochromatic_rv_edit_entry_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *ld_list = lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list");
	GtkWidget *readout_widget;

	int selected_row;
	char *readout_str;

	/* Let's find the selected row:                                             */
	selected_row = (int) ((GList *) (GTK_CLIST (ld_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_rv, "assign_ld_monochromatic_rv_filter_value");
	gtk_clist_get_text (GTK_CLIST (ld_list), selected_row, 0, &readout_str);
	gtk_label_set_text (GTK_LABEL (readout_widget), readout_str);

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_rv, "assign_ld_monochromatic_rv_x1a_value");
	gtk_clist_get_text (GTK_CLIST (ld_list), selected_row, 1, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_rv, "assign_ld_monochromatic_rv_y1a_value");
	gtk_clist_get_text (GTK_CLIST (ld_list), selected_row, 2, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_rv, "assign_ld_monochromatic_rv_x2a_value");
	gtk_clist_get_text (GTK_CLIST (ld_list), selected_row, 3, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_rv, "assign_ld_monochromatic_rv_y2a_value");
	gtk_clist_get_text (GTK_CLIST (ld_list), selected_row, 4, &readout_str);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));

	gtk_widget_show (PHOEBE_assign_ld_monochromatic_rv);
	}

void on_assign_ld_monochromatic_rv_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *ld_list = lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list");
	GtkWidget *readout_widget;

	int selected_row;
	double value;

	char *readout_str;

	char working_string[255];
	char *working_str = working_string;

	/* Let's find the selected row:                                             */
	selected_row = (int) ((GList *) (GTK_CLIST (ld_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_rv, "assign_ld_monochromatic_rv_x1a_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", value);
	gtk_clist_set_text (GTK_CLIST (ld_list), selected_row, 1, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_rv, "assign_ld_monochromatic_rv_y1a_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", value);
	gtk_clist_set_text (GTK_CLIST (ld_list), selected_row, 2, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_rv, "assign_ld_monochromatic_rv_x2a_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", value);
	gtk_clist_set_text (GTK_CLIST (ld_list), selected_row, 3, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_ld_monochromatic_rv, "assign_ld_monochromatic_rv_y2a_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%lf", value);
	gtk_clist_set_text (GTK_CLIST (ld_list), selected_row, 4, working_str);

	gtk_widget_hide (PHOEBE_assign_ld_monochromatic_rv);
	}

void on_assign_ld_monochromatic_rv_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_assign_ld_monochromatic_rv);
	}

void populate_dc_chi2_info_list ()
	{
	GtkWidget *chi2_list = lookup_widget (PHOEBE_dc, "dc_chi2_info_list");
	int lc_no = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rv_no = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));

	int i;

	char entry_string[4][20];
	char *entry[4] = {entry_string[0], entry_string[1], entry_string[2], entry_string[3]};

	gtk_clist_clear (GTK_CLIST (chi2_list));
	
	for (i = 0; i < rv_no; i++)
		{
		sprintf (entry[0], "%s", PHOEBE_rv_data[i].filter);
		sprintf (entry[1], "not calculated");
		sprintf (entry[2], "not calculated");
		sprintf (entry[3], "not calculated");
		gtk_clist_append (GTK_CLIST (chi2_list), entry);
		}
	for (i = 0; i < lc_no; i++)
		{
		sprintf (entry[0], "%s", PHOEBE_lc_data[i].filter);
		sprintf (entry[1], "not calculated");
		sprintf (entry[2], "not calculated");
		sprintf (entry[3], "not calculated");
		gtk_clist_append (GTK_CLIST (chi2_list), entry);
		}
	}

void populate_dc_parameters_info_list ()
	{
	GtkWidget *param_list = lookup_widget (PHOEBE_dc, "dc_parameters_info_list");
	int lc_no = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int i, j;
	int KEP[35];

	const char *keps[] = {"spots_xlat1_adjust", "spots_xlong1_adjust", "spots_radsp1_adjust", "spots_temsp1_adjust", "spots_xlat2_adjust", "spots_xlong2_adjust", "spots_radsp2_adjust", "spots_temsp2_adjust", "system_sma_adjust", "orbit_e_adjust", "orbit_perr0_adjust", "orbit_f1_adjust", "orbit_f2_adjust", "system_pshift_adjust", "system_vga_adjust", "system_incl_adjust", "surface_gr1_adjust", "surface_gr2_adjust", "component_tavh_adjust", "component_tavc_adjust", "surface_alb1_adjust", "surface_alb2_adjust", "component_phsv_adjust", "component_pcsv_adjust", "system_rm_adjust", "system_hjd0_adjust", "system_period_adjust", "system_dpdt_adjust", "orbit_dperdt_adjust", "", "luminosities_hla_adjust", "luminosities_cla_adjust", "ld_x1a_adjust", "ld_x2a_adjust", "luminosities_el3_adjust"};
	const char *values[] = {"", "", "", "", "", "", "", "", "system_sma_value", "orbit_e_value", "orbit_perr0_value", "orbit_f1_value", "orbit_f2_value", "system_pshift_value", "system_vga_value", "system_incl_value", "surface_gr1_value", "surface_gr2_value", "component_tavh_value", "component_tavc_value", "surface_alb1_value", "surface_alb2_value", "component_phsv_value", "component_pcsv_value", "system_rm_value", "system_hjd0_value", "system_period_value", "system_dpdt_value", "orbit_dperdt_value", "", "", "", "", "", ""};
	const char *keyword[] = {"XLAT1", "XLONG1", "RADSP1", "TEMSP1", "XLAT2", "XLONG2", "RADSP2", "TEMSP2", "SMA", "E", "PERR0", "F1", "F2", "PSHIFT", "VGA", "XINCL", "GR1", "GR2", "T1", "T2", "ALB1", "ALB2", "POT1", "POT2", "Q", "HJD0", "PERIOD", "DPDT", "DPERDT", "reserved", "HLA", "CLA", "X1A", "X2A", "EL3"};

	char entry_string[5][20];
	char *entry[5] = {entry_string[0], entry_string[1], entry_string[2], entry_string[3], entry_string[4]};

	GtkWidget *readout_widget;
	char *readout_str;

	PHOEBE_spots spots;

	/*
	 * We need info on spots because it would be too bloated to read the values
	 * from their widgets.
	 */

	allocate_memory_for_spots (&spots);
	read_in_spots (&spots);

	gtk_clist_clear (GTK_CLIST (param_list));

	for (i = 0; i <= 34; i++) {
		/* Reserved channel: */
		if (i == 29) continue;

		/* Read out KEP value: */
		readout_widget = lookup_widget (PHOEBE, keps[i]);
		if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) KEP[i] = 0; else KEP[i] = 1;

                            /* SPOTS */  /* HJD0 */   /* P0  */    /* DPDT */   /* DPERDT */ /* HLA */    /* CLA */    /* X1A */    /* X2A */    /* EL3 */
		if ( (KEP[i] == 0) && (i > 7) && (i != 25) && (i != 26) && (i != 27) && (i != 28) && (i != 30) && (i != 31) && (i != 32) && (i != 33) && (i != 34) ) {
			sprintf (entry[0], "%s", keyword[i]);
			sprintf (entry[1], "%lf", gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, values[i]))));
			sprintf (entry[2], "not calculated");
			sprintf (entry[3], "not calculated");
			sprintf (entry[4], "not calculated");
			gtk_clist_append (GTK_CLIST (param_list), entry);
		}
		if ( (KEP[i] == 0) && (i < 4) /* SPOTS1 */) {
			sprintf (entry[0], "%s", keyword[i]);
			if (spots.KSPA == 1) readout_widget = lookup_widget (PHOEBE, "spots_primary_info_list");
			if (spots.KSPA == 2) readout_widget = lookup_widget (PHOEBE, "spots_secondary_info_list");
			gtk_clist_get_text (GTK_CLIST (readout_widget), spots.NSPA-1, i+1, &readout_str);
			sprintf (entry[1], "%s", readout_str);
			sprintf (entry[2], "not calculated");
			sprintf (entry[3], "not calculated");
			sprintf (entry[4], "not calculated");
			gtk_clist_append (GTK_CLIST (param_list), entry);
		}
		if ( (KEP[i] == 0) && (i >= 4) && (i < 8) /* SPOTS2 */) {
			sprintf (entry[0], "%s", keyword[i]);
			if (spots.KSPB == 1) readout_widget = lookup_widget (PHOEBE, "spots_primary_info_list");
			if (spots.KSPB == 2) readout_widget = lookup_widget (PHOEBE, "spots_secondary_info_list");
			gtk_clist_get_text (GTK_CLIST (readout_widget), spots.NSPB-1, i-3, &readout_str);
			sprintf (entry[1], "%s", readout_str);
			sprintf (entry[2], "not calculated");
			sprintf (entry[3], "not calculated");
			sprintf (entry[4], "not calculated");
			gtk_clist_append (GTK_CLIST (param_list), entry);
		}
		if ( (KEP[i] == 0) && (i == 25) /* HJD0 */) {
			sprintf (entry[0], "%s", keyword[i]);
			sprintf (entry[1], "%s", gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE, values[i]))));
			sprintf (entry[2], "not calculated");
			sprintf (entry[3], "not calculated");
			sprintf (entry[4], "not calculated");
			gtk_clist_append (GTK_CLIST (param_list), entry);
		}
		if ( (KEP[i] == 0) && (i == 26) /* PERIOD */) {
			sprintf (entry[0], "%s", keyword[i]);
			sprintf (entry[1], "%s", gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE, values[i]))));
			sprintf (entry[2], "not calculated");
			sprintf (entry[3], "not calculated");
			sprintf (entry[4], "not calculated");
			gtk_clist_append (GTK_CLIST (param_list), entry);
		}
		if ( (KEP[i] == 0) && (i == 27) /* DPDT */) {
			sprintf (entry[0], "%s", keyword[i]);
			sprintf (entry[1], "%s", gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE, values[i]))));
			sprintf (entry[2], "not calculated");
			sprintf (entry[3], "not calculated");
			sprintf (entry[4], "not calculated");
			gtk_clist_append (GTK_CLIST (param_list), entry);
		}
		if ( (KEP[i] == 0) && (i == 28) /* DPERDT */) {
			sprintf (entry[0], "%s", keyword[i]);
			sprintf (entry[1], "%s", gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE, values[i]))));
			sprintf (entry[2], "not calculated");
			sprintf (entry[3], "not calculated");
			sprintf (entry[4], "not calculated");
			gtk_clist_append (GTK_CLIST (param_list), entry);
		}
		if ( (KEP[i] == 0) && (i == 30) /* HLA */) {
			for (j = 0; j < lc_no; j++) {
				sprintf (entry[0], "%s [%d]", keyword[i], j+1);
				gtk_clist_get_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_lc_info_list")), j, 1, &readout_str);
				sprintf (entry[1], "%s", readout_str);
				sprintf (entry[2], "not calculated");
				sprintf (entry[3], "not calculated");
				sprintf (entry[4], "not calculated");
				gtk_clist_append (GTK_CLIST (param_list), entry);
			}
		}
		if ( (KEP[i] == 0) && (i == 31) /* CLA */) {
			for (j = 0; j < lc_no; j++) {
				sprintf (entry[0], "%s [%d]", keyword[i], j+1);
				gtk_clist_get_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_lc_info_list")), j, 2, &readout_str);
				sprintf (entry[1], "%s", readout_str);
				sprintf (entry[2], "not calculated");
				sprintf (entry[3], "not calculated");
				sprintf (entry[4], "not calculated");
				gtk_clist_append (GTK_CLIST (param_list), entry);
			}
		}
		if ( (KEP[i] == 0) && (i == 32) /* X1A */) {
			for (j = 0; j < lc_no; j++) {
				sprintf (entry[0], "%s [%d]", keyword[i], j+1);
				gtk_clist_get_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), j, 1, &readout_str);
				sprintf (entry[1], "%s", readout_str);
				sprintf (entry[2], "not calculated");
				sprintf (entry[3], "not calculated");
				sprintf (entry[4], "not calculated");
				gtk_clist_append (GTK_CLIST (param_list), entry);
			}
		}
		if ( (KEP[i] == 0) && (i == 33) /* X2A */) {
			for (j = 0; j < lc_no; j++) {
				sprintf (entry[0], "%s [%d]", keyword[i], j+1);
				gtk_clist_get_text (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), j, 3, &readout_str);
				sprintf (entry[1], "%s", readout_str);
				sprintf (entry[2], "not calculated");
				sprintf (entry[3], "not calculated");
				sprintf (entry[4], "not calculated");
				gtk_clist_append (GTK_CLIST (param_list), entry);
			}
		}
		if ( (KEP[i] == 0) && (i == 34) /* EL3 */) {
			int el3_switch;

			readout_widget = lookup_widget (PHOEBE, "luminosities_el3_flux_switch");
			if (GTK_TOGGLE_BUTTON (readout_widget)->active) el3_switch = 1; else el3_switch = 0;

			for (j = 0; j < lc_no; j++) {
				if (el3_switch == 0) {
					/* This means that 3rd light is given in percentage:      */
					double L1, L2, L3;
					char el3_str[20];
					readout_widget = lookup_widget (PHOEBE, "luminosities_lc_info_list");
					gtk_clist_get_text (GTK_CLIST (readout_widget), j, 1, &readout_str);
					L1 = atof (readout_str);
					gtk_clist_get_text (GTK_CLIST (readout_widget), j, 2, &readout_str);
					L2 = atof (readout_str);
					gtk_clist_get_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_el3_info_list")), j, 1, &readout_str);
					L3 = atof (readout_str);
					L3 *= (L1 + L2)/4.0/3.1415926/(1.0-L3);
					sprintf (el3_str, "%lf", L3);
					sprintf (entry[0], "%s [%d]", keyword[i], j+1);
					sprintf (entry[1], "%s", el3_str);
					sprintf (entry[2], "not calculated");
					sprintf (entry[3], "not calculated");
					sprintf (entry[4], "not calculated");
					gtk_clist_append (GTK_CLIST (param_list), entry);
				}
				else {
					/* This means that 3rd light is given in flux:            */
					gtk_clist_get_text (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_el3_info_list")), j, 1, &readout_str);
					sprintf (entry[0], "%s [%d]", keyword[i], j+1);
					sprintf (entry[1], "%s", readout_str);
					sprintf (entry[2], "not calculated");
					sprintf (entry[3], "not calculated");
					sprintf (entry[4], "not calculated");
					gtk_clist_append (GTK_CLIST (param_list), entry);
				}
			}
		}
	}

	free_memory_allocated_for_spots (&spots);

	return;
}

void on_dc_calculate_button_clicked (GtkButton *button, gpointer user_data)
	{
	double DEL[35];
	int KEP[35];
	int i, j, k;

	char working_string[255];
	char *working_str = working_string;

	char value_string[15];
	GtkWidget *readout_widget;

	const char *dels[] = {"", "", "", "", "", "", "", "", "system_sma_step_value", "orbit_e_del_value", "orbit_perr0_del_value", "orbit_f1_del_value", "orbit_f2_del_value", "system_pshift_step_value", "system_vga_step_value", "system_incl_step_value", "surface_gr1_del_value", "surface_gr2_del_value", "component_tavh_del_value", "component_tavc_del_value", "surface_alb1_del_value", "surface_alb2_del_value", "component_phsv_del_value", "component_pcsv_del_value", "system_rm_step_value", "system_hjd0_step_value", "system_period_step_value", "system_dpdt_step_value", "orbit_dperdt_del_value", "", "luminosities_hla_del_value", "luminosities_cla_del_value", "ld_x1a_del_value", "ld_x2a_del_value", "luminosities_el3_del_value"};
	const char *keps[] = {"spots_xlat1_adjust", "spots_xlong1_adjust", "spots_radsp1_adjust", "spots_temsp1_adjust", "spots_xlat2_adjust", "spots_xlong2_adjust", "spots_radsp2_adjust", "spots_temsp2_adjust", "system_sma_adjust", "orbit_e_adjust", "orbit_perr0_adjust", "orbit_f1_adjust", "orbit_f2_adjust", "system_pshift_adjust", "system_vga_adjust", "system_incl_adjust", "surface_gr1_adjust", "surface_gr2_adjust", "component_tavh_adjust", "component_tavc_adjust", "surface_alb1_adjust", "surface_alb2_adjust", "component_phsv_adjust", "component_pcsv_adjust", "system_rm_adjust", "system_hjd0_adjust", "system_period_adjust", "system_dpdt_adjust", "orbit_dperdt_adjust", "", "luminosities_hla_adjust", "luminosities_cla_adjust", "ld_x1a_adjust", "ld_x2a_adjust", "luminosities_el3_adjust"};

	PHOEBE_main_parameters main     = read_in_main_parameters ();
	PHOEBE_limb_darkening  ld       = read_in_ld_coefficients ();
	PHOEBE_spots           spots;
	PHOEBE_switches        switches = read_in_switches        ();
	PHOEBE_mms             mms      = read_in_mms             ();

	PHOEBE_dco_record      dco_record;
	double *correlation_matrix = NULL;

	GtkWidget *dc_cm_info_list_table;
	GtkWidget *dc_cm_info_list;
	GtkWidget *dc_levels_list;
	char **dc_cm_list_column;
	char **dc_levels;
	double window_width, window_height;
	int el3_switch;

	char arg1[255], arg2[255], arg3[255], arg4[255];
	char *argv[4] = {arg1, arg2, arg3, arg4};

	allocate_memory_for_spots (&spots);
	read_in_spots (&spots);

	/* First, let us read out what is the independent variable that the user    */
	/* wants: this is the toggle-button in the Fitting tab:                     */
	readout_widget = lookup_widget (PHOEBE, "fitting_independent_variable_phases_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) switches.JDPHS = 2; else switches.JDPHS = 1;

	/* Let's set all DELs and KEPs to 0: */
	for (i = 0; i <= 34; i++)
		{
		DEL[i] = 0.0;
		KEP[i] = 1;
		}

	/* Here we go from 0 instead of 1 because cfortran.h takes care of OB1: */
	for (i = 0; i <= 34; i++)
		{
		/* Reserved channel: */
		if (i == 29) continue;

		/* Read out KEP values:                                                   */
		readout_widget = lookup_widget (PHOEBE, keps[i]);
		if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE) KEP[i] = 0; else KEP[i] = 1;

		/* Read out DEL values; the following ones are automatic:                 */
		if (i ==  8) continue;    /* SMA    */
		if (i == 14) continue;    /* VGA    */
		if (i == 25) continue;    /* HJD0   */
		if (i == 26) continue;    /* PERIOD */
		if (i == 27) continue;    /* DPDT   */
		if (i == 28) continue;    /* DPERDT */

		/* We don't have DEL values for spots supported yet:                      */
		if ( (i >= 0) && (i <= 7) )
			{
			if ( (i == 1) || (i == 5) ) DEL[i] = 0.1; else DEL[i] = 0.01;
			continue;
			}

		readout_widget = lookup_widget (PHOEBE, dels[i]);
		DEL[i] = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

		/* We have to fix units for T1 and T2 to T/10000K; VGA has its own DEL    */
		/* computation and the units of DEL are thus irrelevant.                  */
		if ( (i == 18) || (i == 19) ) DEL[i] /= 10000.0;
		}

	create_dci_input_file (DEL, KEP, main, ld, spots, switches, mms);
	/* Let's call WD's dc program on the created input file:                  */
	i = scan_temporary_directory_for_dci_file_index ("phoebe_dc");
	sprintf (working_str, "%s/dc < %s/phoebe_dc_%03d.dci > %s/phoebe_dc_%03d.dco", PHOEBE_DC_DIR, PHOEBE_TEMP_DIR, i, PHOEBE_TEMP_DIR, i);
	system (working_str);

	/* Assign a filename to the current DCO process and read in the calculated  */
	/* data and binary parameters:                                              */
	i = scan_temporary_directory_for_dci_file_index ("phoebe_dc");
	sprintf (working_str, "%s/phoebe_dc_%03d.dco", PHOEBE_TEMP_DIR, i);

	/* Initialize arrays that will contain data from dco file:                  */
	dco_record.points_no      = phoebe_malloc ((switches.NLC + switches.IFVC1 + switches.IFVC2) * sizeof (*dco_record.points_no));
	dco_record.chi2           = phoebe_malloc ((switches.NLC + switches.IFVC1 + switches.IFVC2) * sizeof (*dco_record.chi2));
	dco_record.L1             = phoebe_malloc (switches.NLC * sizeof (*dco_record.L1));
	dco_record.L2             = phoebe_malloc (switches.NLC * sizeof (*dco_record.L2));
	dco_record.L3             = phoebe_malloc (switches.NLC * sizeof (*dco_record.L3));

	readout_widget = lookup_widget (PHOEBE_dc, "dc_parameters_info_list");
	i = GTK_CLIST (readout_widget)->rows;      /* How many parameters are there */
	dco_record.param_no       = phoebe_malloc (i * sizeof (*dco_record.param_no));
	dco_record.curve_no       = phoebe_malloc (i * sizeof (*dco_record.curve_no));
	dco_record.original_value = phoebe_malloc (i * sizeof (*dco_record.original_value));
	dco_record.correction     = phoebe_malloc (i * sizeof (*dco_record.correction));
	dco_record.modified_value = phoebe_malloc (i * sizeof (*dco_record.modified_value));
	dco_record.sigma          = phoebe_malloc (i * sizeof (*dco_record.sigma));

	/* Initialize the correlation matrix space:                                 */
	correlation_matrix = phoebe_malloc (i*i * sizeof (*correlation_matrix));

	/* If 3rd light is given in % and *not* fitted, and if L1s are fitted,    */
	/* DC corrections need to be modified; that's why we need this:           */
	readout_widget = lookup_widget (PHOEBE, "luminosities_el3_flux_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) el3_switch = 0; else el3_switch = 1;
	readout_widget = lookup_widget (PHOEBE, "luminosities_el3_adjust");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active) el3_switch = 0;

	read_in_dco_values (working_str, &dco_record, correlation_matrix, el3_switch);

	/* 1. step: update parameter values:                                        */
	readout_widget = lookup_widget (PHOEBE_dc, "dc_parameters_info_list");
	for (j = 0; j < i; j++)
		{
		/* If we fitted any of the double precision parameters, we have to print  */
		/* them that accurately:                                                  */
		if (
			 dco_record.param_no[j] == 26 /* HJD0   */ ||
			 dco_record.param_no[j] == 27 /* PERIOD */ ||
			 dco_record.param_no[j] == 28 /* DPDT   */ ||
			 dco_record.param_no[j] == 29 /* DPERDT */
			 )
			{
			sprintf (working_str, "%15.16G", dco_record.original_value[j]);
			gtk_clist_set_text (GTK_CLIST (readout_widget), j, 1, working_str);
			sprintf (working_str, "%15.16G", dco_record.correction[j]);
			gtk_clist_set_text (GTK_CLIST (readout_widget), j, 2, working_str);
			sprintf (working_str, "%15.16G", dco_record.modified_value[j]);
			gtk_clist_set_text (GTK_CLIST (readout_widget), j, 3, working_str);
			sprintf (working_str, "%15.16G", dco_record.sigma[j]);
			gtk_clist_set_text (GTK_CLIST (readout_widget), j, 4, working_str);
			}
		else
			{
			sprintf (working_str, "%G", dco_record.original_value[j]);
			gtk_clist_set_text (GTK_CLIST (readout_widget), j, 1, working_str);
			sprintf (working_str, "%G", dco_record.correction[j]);
			gtk_clist_set_text (GTK_CLIST (readout_widget), j, 2, working_str);
			sprintf (working_str, "%G", dco_record.modified_value[j]);
			gtk_clist_set_text (GTK_CLIST (readout_widget), j, 3, working_str);
			sprintf (working_str, "%G", dco_record.sigma[j]);
			gtk_clist_set_text (GTK_CLIST (readout_widget), j, 4, working_str);
			}
		}

	/* 2. step: update chi2 values:                                             */
	readout_widget = lookup_widget (PHOEBE_dc, "dc_chi2_info_list");
	for (j = 0; j < switches.NLC + switches.IFVC1 + switches.IFVC2; j++)
		{
		sprintf (working_str, "%d", dco_record.points_no[j]);
		gtk_clist_set_text (GTK_CLIST (readout_widget), j, 1, working_str);
		sprintf (working_str, "%lf", dco_record.chi2[j]);
		gtk_clist_set_text (GTK_CLIST (readout_widget), j, 3, working_str);
		}

	/* 3. step: update correlation matrix output:                               */

	/* If the matrix exists from previous calculation, destroy it:              */
	if (GTK_BIN (lookup_widget (PHOEBE_dc_correlation_matrix, "dc_correlation_matrix_main_frame"))->child != NULL)
		gtk_widget_destroy (GTK_WIDGET (GTK_BIN (lookup_widget (PHOEBE_dc_correlation_matrix, "dc_correlation_matrix_main_frame"))->child));

	/* Let's resize the window:                                                 */
	if (i < 10) window_width  = 48+(i+1)*67; else window_width  = 48+11*67;
	if (i < 10) window_height = 62+(i+1)*16; else window_height = 62+11*16;
	gtk_window_set_default_size (GTK_WINDOW (PHOEBE_dc_correlation_matrix), window_width, window_height);

	dc_cm_info_list_table = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_ref (dc_cm_info_list_table);
	gtk_object_set_data_full (GTK_OBJECT (PHOEBE_dc_correlation_matrix), "dc_parameters_info_list_table", dc_cm_info_list_table, (GtkDestroyNotify) gtk_widget_unref);
	gtk_widget_show (dc_cm_info_list_table);
	gtk_container_add (GTK_CONTAINER (lookup_widget (PHOEBE_dc_correlation_matrix, "dc_correlation_matrix_main_frame")), dc_cm_info_list_table);
	gtk_container_set_border_width (GTK_CONTAINER (dc_cm_info_list_table), 5);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (dc_cm_info_list_table), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	/* We create the list with (i+1) dimension because of heading labels.       */
	dc_cm_info_list = gtk_clist_new (i+1);
	gtk_widget_ref (dc_cm_info_list);
	gtk_object_set_data_full (GTK_OBJECT (PHOEBE_dc_correlation_matrix), "dc_cm_info_list", dc_cm_info_list, (GtkDestroyNotify) gtk_widget_unref);
	gtk_widget_show (dc_cm_info_list);
	gtk_container_add (GTK_CONTAINER (dc_cm_info_list_table), dc_cm_info_list);
	for (j = 0; j <= i; j++)
		{
		gtk_clist_set_column_width (GTK_CLIST (dc_cm_info_list), j, 60);
		gtk_clist_set_column_justification (GTK_CLIST (dc_cm_info_list), j, GTK_JUSTIFY_RIGHT);
		}
	gtk_clist_set_column_justification (GTK_CLIST (dc_cm_info_list), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_column_titles_hide (GTK_CLIST (dc_cm_info_list));

	/* First we allocate space for a single row entry:                          */
	dc_cm_list_column = phoebe_malloc ( (i+1) * sizeof (char *) );
	for (j = 0; j <= i; j++)
		dc_cm_list_column[j] = phoebe_malloc (15 * sizeof (char));

	/* Let's populate the heading row:                                          */
	readout_widget = lookup_widget (PHOEBE_dc, "dc_parameters_info_list");
	sprintf (dc_cm_list_column[0], "");
	for (j = 1; j <= i; j++)
		{
		gtk_clist_get_text (GTK_CLIST (readout_widget), j-1, 0, &working_str);
		sprintf (dc_cm_list_column[j], "%s", working_str);
		}
	gtk_clist_append (GTK_CLIST (dc_cm_info_list), dc_cm_list_column);

	/* Next, we put in all correlation matrix values:                           */
	for (j = 0; j < i; j++)
		{
		gtk_clist_get_text (GTK_CLIST (readout_widget), j, 0, &working_str);
		sprintf (dc_cm_list_column[0], "%s", working_str);
		for (k = 1; k <= i; k++)
			sprintf (dc_cm_list_column[k], "%lf", correlation_matrix[j*i+(k-1)]);
		gtk_clist_append (GTK_CLIST (dc_cm_info_list), dc_cm_list_column);
		}

	/* 4th step: populate passband luminosities:                                */
	dc_levels_list = lookup_widget (PHOEBE_dc, "dc_levels_list");
	gtk_clist_clear (GTK_CLIST (dc_levels_list));
	gtk_clist_set_column_justification (GTK_CLIST (dc_levels_list), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (dc_levels_list), 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (dc_levels_list), 2, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (dc_levels_list), 3, GTK_JUSTIFY_CENTER);

	/* Finally, let's free the row space:                                       */
	for (j = 0; j <= i; j++) free (dc_cm_list_column[j]);
	free (dc_cm_list_column);

	dc_levels = phoebe_malloc (4 * sizeof (*dc_levels));

	for (j = 0; j < switches.NLC; j++)
		{
		dc_levels[0] = strdup (PHOEBE_lc_data[j].filter);

		sprintf (value_string, "%5.5lf", dco_record.L1[j]);
		dc_levels[1] = strdup (value_string);

		sprintf (value_string, "%5.5lf", dco_record.L2[j]);
		dc_levels[2] = strdup (value_string);

		sprintf (value_string, "%5.5lf", dco_record.L3[j]);
		dc_levels[3] = strdup (value_string);

		gtk_clist_append (GTK_CLIST (dc_levels_list), dc_levels);
		free (dc_levels[0]); free (dc_levels[1]); free (dc_levels[2]); free (dc_levels[3]);
		}
	free (dc_levels);

	/* Free all dco_record arrays:                                              */
	free (dco_record.points_no);
	free (dco_record.chi2);
	free (dco_record.param_no);
	free (dco_record.curve_no);
	free (dco_record.original_value);
	free (dco_record.correction);
	free (dco_record.modified_value);
	free (dco_record.sigma);
	free (dco_record.L1);
	free (dco_record.L2);
	free (dco_record.L3);
	
	/* Free the correlation matrix:                                             */
	free (correlation_matrix);
	}

void on_dc_update_corrections_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *par_list = lookup_widget (PHOEBE_dc, "dc_parameters_info_list");
	int rows_present = GTK_CLIST (par_list)->rows;

	const char *values[] = {"", "", "", "", "", "", "", "", "system_sma_value", "orbit_e_value", "orbit_perr0_value", "orbit_f1_value", "orbit_f2_value", "system_pshift_value", "system_vga_value", "system_incl_value", "surface_gr1_value", "surface_gr2_value", "component_tavh_value", "component_tavc_value", "surface_alb1_value", "surface_alb2_value", "component_phsv_value", "component_pcsv_value", "system_rm_value", "system_hjd0_value", "system_period_value", "system_dpdt_value", "orbit_dperdt_value", "", "", "", "", "", ""};
	const char *keyword[] = {"XLAT1", "XLONG1", "RADSP1", "TEMSP1", "XLAT2", "XLONG2", "RADSP2", "TEMSP2", "SMA", "E", "PERR0", "F1", "F2", "PSHIFT", "VGA", "XINCL", "GR1", "GR2", "T1", "T2", "ALB1", "ALB2", "POT1", "POT2", "Q", "HJD0", "PERIOD", "DPDT", "DPERDT", "reserved", "HLA", "CLA", "X1A", "X2A", "EL3"};

	int i, j;

	GtkWidget *readout_widget;
	char      *readout_str;
	int        readout_int;

	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));

	/* First, let's check if the list contains any elements:                    */
	if (rows_present == 0) return;

	/* Next, let's check if we have anything to update, because if the user     */
	/* clicked on this button when nothing was calculated, atof() would fail.   */
	gtk_clist_get_text (GTK_CLIST (par_list), 0, 3, &readout_str);
	if (strcmp (readout_str, "not calculated") == 0) return;
	
	for (i = 0; i < rows_present; i++)
		{
		gtk_clist_get_text (GTK_CLIST (par_list), i, 0, &readout_str);
		for (j = 0; j < 35; j++)
			{
			if (strcmp (readout_str, keyword[j]) == 0)
				{
				gtk_clist_get_text (GTK_CLIST (par_list), i, 3, &readout_str);
				if (strcmp (values[j], "") != 0)
					readout_widget = lookup_widget (PHOEBE, values[j]);

				/* At this point we must differentiate between spin buttons and entry */
				/* boxes (for double-precision parameters):                           */
				if ( (strcmp (keyword[j], "DPDT") == 0)   ||
				     (strcmp (keyword[j], "HJD0") == 0)   ||
				     (strcmp (keyword[j], "PERIOD") == 0) ||
				     (strcmp (keyword[j], "HJD0") == 0)   ||
				     (strcmp (keyword[j], "DPERDT") == 0) )
					gtk_entry_set_text (GTK_ENTRY (readout_widget), readout_str);
				else
					if ( (strncmp (keyword[j], "XLAT", 4) == 0)  ||
					     (strncmp (keyword[j], "XLONG", 5) == 0) ||
					     (strncmp (keyword[j], "RADSP", 5) == 0) ||
					     (strncmp (keyword[j], "TEMSP", 5) == 0) )
						{
						GtkWidget *parent;
						PHOEBE_spots spots;

						allocate_memory_for_spots (&spots);
						read_in_spots (&spots);

						if (strcmp (keyword[j], "XLAT1") == 0) {
							if (spots.KSPA == 1) parent = lookup_widget (PHOEBE, "spots_primary_info_list");
							else                 parent = lookup_widget (PHOEBE, "spots_secondary_info_list");
							gtk_clist_set_text (GTK_CLIST (parent), spots.NSPA - 1, 1, readout_str);
						}
						if (strcmp (keyword[j], "XLONG1") == 0) {
							if (spots.KSPA == 1) parent = lookup_widget (PHOEBE, "spots_primary_info_list");
							else                 parent = lookup_widget (PHOEBE, "spots_secondary_info_list");
							gtk_clist_set_text (GTK_CLIST (parent), spots.NSPA - 1, 2, readout_str);
						}
						if (strcmp (keyword[j], "RADSP1") == 0) {
							if (spots.KSPA == 1) parent = lookup_widget (PHOEBE, "spots_primary_info_list");
							else                 parent = lookup_widget (PHOEBE, "spots_secondary_info_list");
							gtk_clist_set_text (GTK_CLIST (parent), spots.NSPA - 1, 3, readout_str);
						}
						if (strcmp (keyword[j], "TEMSP1") == 0) {
							if (spots.KSPA == 1) parent = lookup_widget (PHOEBE, "spots_primary_info_list");
							else                 parent = lookup_widget (PHOEBE, "spots_secondary_info_list");
							gtk_clist_set_text (GTK_CLIST (parent), spots.NSPA - 1, 4, readout_str);
						}

						if (strcmp (keyword[j], "XLAT2") == 0) {
							if (spots.KSPB == 1) parent = lookup_widget (PHOEBE, "spots_primary_info_list");
							else                 parent = lookup_widget (PHOEBE, "spots_secondary_info_list");
							gtk_clist_set_text (GTK_CLIST (parent), spots.NSPB - 1, 1, readout_str);
						}
						if (strcmp (keyword[j], "XLONG2") == 0) {
							if (spots.KSPB == 1) parent = lookup_widget (PHOEBE, "spots_primary_info_list");
							else                 parent = lookup_widget (PHOEBE, "spots_secondary_info_list");
							gtk_clist_set_text (GTK_CLIST (parent), spots.NSPB - 1, 2, readout_str);
						}
						if (strcmp (keyword[j], "RADSP2") == 0) {
							if (spots.KSPB == 1) parent = lookup_widget (PHOEBE, "spots_primary_info_list");
							else                 parent = lookup_widget (PHOEBE, "spots_secondary_info_list");
							gtk_clist_set_text (GTK_CLIST (parent), spots.NSPB - 1, 3, readout_str);
						}
						if (strcmp (keyword[j], "TEMSP2") == 0) {
							if (spots.KSPB == 1) parent = lookup_widget (PHOEBE, "spots_primary_info_list");
							else                 parent = lookup_widget (PHOEBE, "spots_secondary_info_list");
							gtk_clist_set_text (GTK_CLIST (parent), spots.NSPB - 1, 4, readout_str);
						}
/*
						if (spots.KSPA != 0) {
							if (spots.KSPA == 1)
								parent = lookup_widget (PHOEBE, "spots_primary_info_list");
							if (spots.KSPA == 2)
								parent = lookup_widget (PHOEBE, "spots_secondary_info_list");

							if (strncmp (keyword[j], "XLAT", 4) == 0)
								gtk_clist_set_text (GTK_CLIST (parent), spots.NSPA - 1, 1, readout_str);
							if (strncmp (keyword[j], "XLONG", 5) == 0)
								gtk_clist_set_text (GTK_CLIST (parent), spots.NSPA - 1, 2, readout_str);
							if (strncmp (keyword[j], "RADSP", 5) == 0)
								gtk_clist_set_text (GTK_CLIST (parent), spots.NSPA - 1, 3, readout_str);
							if (strncmp (keyword[j], "TEMSP", 5) == 0)
								gtk_clist_set_text (GTK_CLIST (parent), spots.NSPA - 1, 4, readout_str);
						}

						if (spots.KSPB != 0) {
							if (spots.KSPB == 1)
								parent = lookup_widget (PHOEBE, "spots_primary_info_list");
							if (spots.KSPB == 2)
								parent = lookup_widget (PHOEBE, "spots_secondary_info_list");

							if (strncmp (keyword[j], "XLAT", 4) == 0)
								gtk_clist_set_text (GTK_CLIST (parent), spots.NSPB - 1, 1, readout_str);
							if (strncmp (keyword[j], "XLONG", 5) == 0)
								gtk_clist_set_text (GTK_CLIST (parent), spots.NSPB - 1, 2, readout_str);
							if (strncmp (keyword[j], "RADSP", 5) == 0)
								gtk_clist_set_text (GTK_CLIST (parent), spots.NSPB - 1, 3, readout_str);
							if (strncmp (keyword[j], "TEMSP", 5) == 0)
								gtk_clist_set_text (GTK_CLIST (parent), spots.NSPB - 1, 4, readout_str);
						}
*/
						free_memory_allocated_for_spots (&spots);
						}
					else
						gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), atof (readout_str));
				}
			if (strncmp (readout_str, keyword[j], 3) == 0)
				{
				/* We have to take care of the curve-dependent parameters HLA, CLA,   */
				/* X1A, X2A and EL3:                                                  */
				if (strncmp (readout_str, "HLA", 3) == 0)
					{
					sscanf (readout_str, "HLA [%d]", &readout_int);
					gtk_clist_get_text (GTK_CLIST (par_list), i, 3, &readout_str);
					readout_widget = lookup_widget (PHOEBE, "luminosities_lc_info_list");
					gtk_clist_set_text (GTK_CLIST (readout_widget), readout_int - 1, 1, readout_str);
					}
				if (strncmp (readout_str, "CLA", 3) == 0)
					{
					sscanf (readout_str, "CLA [%d]", &readout_int);
					gtk_clist_get_text (GTK_CLIST (par_list), i, 3, &readout_str);
					readout_widget = lookup_widget (PHOEBE, "luminosities_lc_info_list");
					gtk_clist_set_text (GTK_CLIST (readout_widget), readout_int - 1, 2, readout_str);
					}
				if (strncmp (readout_str, "X1A", 3) == 0)
					{
					sscanf (readout_str, "X1A [%d]", &readout_int);
					gtk_clist_get_text (GTK_CLIST (par_list), i, 3, &readout_str);
					readout_widget = lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list");
					gtk_clist_set_text (GTK_CLIST (readout_widget), readout_int - 1, 1, readout_str);
					}
				if (strncmp (readout_str, "X2A", 3) == 0)
					{
					sscanf (readout_str, "X2A [%d]", &readout_int);
					gtk_clist_get_text (GTK_CLIST (par_list), i, 3, &readout_str);
					readout_widget = lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list");
					gtk_clist_set_text (GTK_CLIST (readout_widget), readout_int - 1, 3, readout_str);
					}
				if (strncmp (readout_str, "EL3", 3) == 0) {
					int el3_switch;

					sscanf (readout_str, "EL3 [%d]", &readout_int);

					readout_widget = lookup_widget (PHOEBE, "luminosities_el3_flux_switch");
					if (GTK_TOGGLE_BUTTON (readout_widget)->active) el3_switch = 1; else el3_switch = 0;

					if (el3_switch == 0) {
						/* This means that 3rd light is given in percentage:  */
						double L1, L2, L3;
						char el3_str[20];
						readout_widget = lookup_widget (PHOEBE, "luminosities_lc_info_list");
						gtk_clist_get_text (GTK_CLIST (readout_widget), readout_int - 1, 1, &readout_str);
						L1 = atof (readout_str);
						gtk_clist_get_text (GTK_CLIST (readout_widget), readout_int - 1, 2, &readout_str);
						L2 = atof (readout_str);
						gtk_clist_get_text (GTK_CLIST (par_list), i, 3, &readout_str);
						L3 = atof (readout_str);
						/* L3 is returned in flux, but we need percentages:   */
						L3 *= 4.0*3.1415926/(L1 + L2 + 4.0*3.1415926*L3);
						sprintf (el3_str, "%lf", L3);
						readout_widget = lookup_widget (PHOEBE, "luminosities_el3_info_list");
						gtk_clist_set_text (GTK_CLIST (readout_widget), readout_int - 1, 1, el3_str);
					}
					else {
						/* This means that 3rd light is given in flux:        */
						gtk_clist_get_text (GTK_CLIST (par_list), i, 3, &readout_str);
						readout_widget = lookup_widget (PHOEBE, "luminosities_el3_info_list");
						gtk_clist_set_text (GTK_CLIST (readout_widget), readout_int - 1, 1, readout_str);
					}
				}

				}
			}
		}

	/* Update the L2 values:                                                  */
	for (i = 0; i < lc_no; i++) {
		readout_widget = lookup_widget (PHOEBE_dc, "dc_levels_list");
		gtk_clist_get_text (GTK_CLIST (readout_widget), i, 2, &readout_str);
		readout_widget = lookup_widget (PHOEBE, "luminosities_lc_info_list");
		gtk_clist_set_text (GTK_CLIST (readout_widget), i, 2, readout_str);
	}

	/* We have now updated all main PHOEBE widgets, we have to update DC window */
	/* as well (move changed to original value and erase corrections):          */
	populate_dc_parameters_info_list ();

	/* If automatic limb darkening interpolation is turned on, let's do it:     */

	if (PHOEBE_LD_SWITCH && GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "ld_automatic_interpolation_switch"))->active)
		{
		PHOEBE_vector ld_coefs;
		int ld;
		int T1, T2;
		double lgg1, lgg2, M1, M2;
		char valstr[15];

		readout_widget = lookup_widget (PHOEBE, "ld_ld_law_combo_box_entry");
		readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
		if (strcmp (readout_str, "Linear Cosine Law") == 0) ld = 0;
		if (strcmp (readout_str,   "Logarithmic Law") == 0) ld = 1;
		if (strcmp (readout_str,   "Square Root Law") == 0) ld = 2;

		readout_widget = lookup_widget (PHOEBE, "component_tavh_value");
		T1 = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));
		readout_widget = lookup_widget (PHOEBE, "component_tavc_value");
		T2 = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (readout_widget));

		readout_widget = lookup_widget (PHOEBE, "component_logg1_value");
		lgg1 = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
		readout_widget = lookup_widget (PHOEBE, "component_logg2_value");
		lgg2 = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

		readout_widget = lookup_widget (PHOEBE, "component_met1_value");
		M1 = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
		readout_widget = lookup_widget (PHOEBE, "component_met2_value");
		M2 = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));

		for (i = 0; i < lc_no; i++)
			{
			readout_widget = lookup_widget (PHOEBE, "data_lc_info_list");
			gtk_clist_get_text (GTK_CLIST (readout_widget), i, 3, &readout_str);

			ld_coefs = interpolate_from_ld_tables (readout_str, T1, lgg1, M1, ld);
			readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_x1a_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), ld_coefs.x);
			readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_y1a_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), ld_coefs.y);

			readout_widget = lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list");
			sprintf (valstr, "%lf", ld_coefs.x);
			gtk_clist_set_text (GTK_CLIST (readout_widget), i, 1, valstr);
			sprintf (valstr, "%lf", ld_coefs.y);
			gtk_clist_set_text (GTK_CLIST (readout_widget), i, 2, valstr);

			ld_coefs = interpolate_from_ld_tables (readout_str, T2, lgg2, M2, ld);
			readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_x2a_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), ld_coefs.x);
			readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_y2a_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), ld_coefs.y);

			readout_widget = lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list");
			sprintf (valstr, "%lf", ld_coefs.x);
			gtk_clist_set_text (GTK_CLIST (readout_widget), i, 3, valstr);
			sprintf (valstr, "%lf", ld_coefs.y);
			gtk_clist_set_text (GTK_CLIST (readout_widget), i, 4, valstr);
			}
		for (i = 0; i < rv_no; i++)
			{
			readout_widget = lookup_widget (PHOEBE, "data_rv_info_list");
			gtk_clist_get_text (GTK_CLIST (readout_widget), i, 3, &readout_str);

			ld_coefs = interpolate_from_ld_tables (readout_str, T1, lgg1, M1, ld);
			readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_x1a_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), ld_coefs.x);
			readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_y1a_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), ld_coefs.y);

			readout_widget = lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list");
			sprintf (valstr, "%lf", ld_coefs.x);
			gtk_clist_set_text (GTK_CLIST (readout_widget), i, 1, valstr);
			sprintf (valstr, "%lf", ld_coefs.y);
			gtk_clist_set_text (GTK_CLIST (readout_widget), i, 2, valstr);

			ld_coefs = interpolate_from_ld_tables (readout_str, T2, lgg2, M2, ld);
			readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_x2a_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), ld_coefs.x);
			readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_y2a_value");
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), ld_coefs.y);

			readout_widget = lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list");
			sprintf (valstr, "%lf", ld_coefs.x);
			gtk_clist_set_text (GTK_CLIST (readout_widget), i, 3, valstr);
			sprintf (valstr, "%lf", ld_coefs.y);
			gtk_clist_set_text (GTK_CLIST (readout_widget), i, 4, valstr);
			}
		}

	/* Finally, we have to update chi2 info list:                               */
	readout_widget = lookup_widget (PHOEBE_dc, "dc_chi2_info_list");
	rows_present = GTK_CLIST (readout_widget)->rows;
	for (i = 0; i < rows_present; i++)
		{
		gtk_clist_get_text (GTK_CLIST (readout_widget), i, 3, &readout_str);
		gtk_clist_set_text (GTK_CLIST (readout_widget), i, 2, readout_str);
		gtk_clist_set_text (GTK_CLIST (readout_widget), i, 3, "not calculated");
		}
	}

void on_dc_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_dc);
	}

void on_dc_update_selection_button_clicked (GtkButton *button, gpointer user_data)
	{
	}

void on_dc_show_quickbar_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_fitting_quickbar);
	}

void on_fitting_fit_button_clicked (GtkButton *button, gpointer user_data)
	{
	/* This function shows the fitting window on the screen. The values within  */
	/* need not be populated here, for every click (toggle) of Adjust switches  */
	/* is catched and the change reflected in this window through a separate    */
	/* callback.                                                                */

	gtk_widget_show (PHOEBE_dc);
	}

void on_adjust_switch_toggled_update_fitting_window (GtkToggleButton *togglebutton, gpointer user_data)
	{
	populate_dc_parameters_info_list ();
	populate_dc_chi2_info_list ();
	}

void on_plot_lc_plot_to_file_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_plot_to_file);
	gtk_object_set_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on", user_data);
	}

void on_plot_rv_plot_to_file_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_plot_to_file);
	gtk_object_set_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on", user_data);
	}

void on_fitting_chi2_plot_to_file_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_plot_to_file);
	gtk_object_set_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on", user_data);
	}

void on_luminosities_star_image_plot_to_file_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_plot_to_file);
	gtk_object_set_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on", user_data);
	}

void on_plot_to_file_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	char *device = gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE_plot_to_file, "plot_to_file_device_list_entry")));

	char prefix_string[255];
	char *prefix_str = prefix_string;

	char working_string[255];
	char *working_str = working_string;

	if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_lc, "plot_lc_plot_to_file_button"))
		sprintf (prefix_str, "my_lc_plot");
	if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_rv, "plot_rv_plot_to_file_button"))
		sprintf (prefix_str, "my_rv_plot");
	if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "fitting_chi2_plot_to_file_button"))
		sprintf (prefix_str, "my_chi2_plot");
	if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "luminosities_star_image_plot_to_file_button"))
		sprintf (prefix_str, "my_3d_plot");

	if (strcmp (device, "Encapsulated Postscript (.eps)") == 0)
		sprintf (working_str, "%s.eps", prefix_str);
	if (strcmp (device, "Plain Text Table (.ascii)") == 0)
		sprintf (working_str, "%s.ascii", prefix_str);
	if (strcmp (device, "X-Windows Pixmap (.xpm)") == 0)
		sprintf (working_str, "%s.xpm", prefix_str);
	if (strcmp (device, "Graphics Interchange Format (.gif)") == 0)
		sprintf (working_str, "%s.gif", prefix_str);
	if (strcmp (device, "Small GIF: 256x128 (.gif)") == 0)
		sprintf (working_str, "%s.gif", prefix_str);
	if (strcmp (device, "Portable Pixmap (.ppm)") == 0)
		sprintf (working_str, "%s.ppm", prefix_str);
	if (strcmp (device, "Portable Network Graphics (.png)") == 0)
		sprintf (working_str, "%s.png", prefix_str);

	gtk_file_selection_set_filename (GTK_FILE_SELECTION (PHOEBE_plot_to_file_selector), working_str);

	gtk_widget_hide (PHOEBE_plot_to_file);
	gtk_widget_show (PHOEBE_plot_to_file_selector);
	}

void on_plot_to_file_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_plot_to_file);
	}

void on_plot_to_file_selector_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	char *device = gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE_plot_to_file, "plot_to_file_device_list_entry")));
	char *filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (PHOEBE_plot_to_file_selector));

	/* We will use different approach with Chi2, because the file selector per- */
	/* sists far too long otherwise.                                            */

	if (strcmp (device, "Encapsulated Postscript (.eps)") == 0)
		{
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_lc, "plot_lc_plot_to_file_button"))
			plot_lc_plot (eps, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_rv, "plot_rv_plot_to_file_button"))
			plot_rv_plot (eps, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "fitting_chi2_plot_to_file_button"))
			{
			gtk_widget_hide (PHOEBE_plot_to_file_selector);
			plot_chi2_plot (eps, filename);
			return;
			}
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "luminosities_star_image_plot_to_file_button"))
			plot_3d_image_plot (eps, filename);
		}
	if (strcmp (device, "Plain Text Table (.ascii)") == 0)
		{
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_lc, "plot_lc_plot_to_file_button"))
			plot_lc_plot (ascii, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_rv, "plot_rv_plot_to_file_button"))
			plot_rv_plot (ascii, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "fitting_chi2_plot_to_file_button"))
			{
			gtk_widget_hide (PHOEBE_plot_to_file_selector);
			plot_chi2_plot (ascii, filename);
			return;
			}
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "luminosities_star_image_plot_to_file_button"))
			plot_3d_image_plot (ascii, filename);
		}
	if (strcmp (device, "X-Windows Pixmap (.xpm)") == 0)
		{
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_lc, "plot_lc_plot_to_file_button"))
			plot_lc_plot (xpm, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_rv, "plot_rv_plot_to_file_button"))
			plot_rv_plot (xpm, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "fitting_chi2_plot_to_file_button"))
			{
			gtk_widget_hide (PHOEBE_plot_to_file_selector);
			plot_chi2_plot (xpm, filename);
			return;
			}
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "luminosities_star_image_plot_to_file_button"))
			plot_3d_image_plot (xpm, filename);
		}
	if (strcmp (device, "Graphics Interchange Format (.gif)") == 0)
		{
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_lc, "plot_lc_plot_to_file_button"))
			plot_lc_plot (gif, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_rv, "plot_rv_plot_to_file_button"))
			plot_rv_plot (gif, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "fitting_chi2_plot_to_file_button"))
			{
			gtk_widget_hide (PHOEBE_plot_to_file_selector);
			plot_chi2_plot (gif, filename);
			return;
			}
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "luminosities_star_image_plot_to_file_button"))
			plot_3d_image_plot (gif, filename);
		}
	if (strcmp (device, "Small GIF: 256x128 (.gif)") == 0)
		{
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_lc, "plot_lc_plot_to_file_button"))
			plot_lc_plot (tinygif, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_rv, "plot_rv_plot_to_file_button"))
			plot_rv_plot (tinygif, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "fitting_chi2_plot_to_file_button"))
			{
			gtk_widget_hide (PHOEBE_plot_to_file_selector);
			plot_chi2_plot (tinygif, filename);
			return;
			}
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "luminosities_star_image_plot_to_file_button"))
			plot_3d_image_plot (tinygif, filename);
		}
	if (strcmp (device, "Portable Pixmap (.ppm)") == 0)
		{
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_lc, "plot_lc_plot_to_file_button"))
			plot_lc_plot (ppm, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_rv, "plot_rv_plot_to_file_button"))
			plot_rv_plot (ppm, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "fitting_chi2_plot_to_file_button"))
			{
			gtk_widget_hide (PHOEBE_plot_to_file_selector);
			plot_chi2_plot (ppm, filename);
			return;
			}
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "luminosities_star_image_plot_to_file_button"))
			plot_3d_image_plot (ppm, filename);
		}

	if (strcmp (device, "Portable Network Graphics (.png)") == 0)
		{
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_lc, "plot_lc_plot_to_file_button"))
			plot_lc_plot (png, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE_plot_rv, "plot_rv_plot_to_file_button"))
			plot_rv_plot (png, filename);
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "fitting_chi2_plot_to_file_button"))
			{
			gtk_widget_hide (PHOEBE_plot_to_file_selector);
			plot_chi2_plot (png, filename);
			return;
			}
		if (GTK_WIDGET (gtk_object_get_data (GTK_OBJECT (PHOEBE_plot_to_file), "initiated_by_clicking_on")) == lookup_widget (PHOEBE, "luminosities_star_image_plot_to_file_button"))
			plot_3d_image_plot (png, filename);
		}

	gtk_widget_hide (PHOEBE_plot_to_file_selector);
	}

void on_plot_to_file_selector_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_plot_to_file_selector);
	}

void on_data_model_entry_changed (GtkEditable *editable, gpointer user_data)
	{
	/* First let's put together a list of constrained parameters along with all */
	/* associated widgets for easier handling; be sure to put adjustment swit-  */
	/* ches first, since we'll be turning them off when they aren't available.  */

	const char *phsv[] = {"component_phsv_adjust", "component_phsv_label", "component_phsv_calculate_button", "component_phsv_description", "component_phsv_value", "component_phsv_del_label", "component_phsv_del_value"};
	const char *pcsv[] = {"component_pcsv_adjust", "component_pcsv_label", "component_pcsv_calculate_button", "component_pcsv_description", "component_pcsv_value", "component_pcsv_del_label", "component_pcsv_del_value"};
	const char *gr2[]  = {"surface_gr2_adjust", "surface_gr2_label", "surface_gr2_description", "surface_gr2_value", "surface_gr2_del_label", "surface_gr2_del_value"};
	const char *alb2[] = {"surface_alb2_adjust", "surface_alb2_label", "surface_alb2_description", "surface_alb2_value", "surface_alb2_del_label", "surface_alb2_del_value"};
	const char *tavc[] = {"component_tavc_adjust", "component_tavc_label", "component_tavc_description", "component_tavc_value", "component_tavc_del_label", "component_tavc_del_value"};
	const char *cla[]  = {"luminosities_cla_adjust", "luminosities_lc_info_secondary_star_label", "luminosities_cla_del_label", "luminosities_cla_del_value"};
	const char *ld[]   = {"ld_x2a_adjust", "ld_monochromatic_lc_x2a_label", "ld_monochromatic_lc_y2a_label", "ld_monochromatic_rv_x2a_label", "ld_monochromatic_rv_y2a_label", "ld_x2a_del_label", "ld_x2a_del_value"};
	const char *the[]  = {"data_the_description", "data_the_label", "data_the_value", "data_the_description_2"};
	int i;

	char *readout_str = gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE, "data_model_list_entry")));
	GtkWidget *readout_widget;

	if (strcmp (readout_str, "General binary system (no constraints)") == 0)
		{
		/* There are no solution constraints:                                     */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, phsv[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, pcsv[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, gr2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, alb2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, tavc[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, cla[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_label");
			gtk_widget_set_sensitive (readout_widget, TRUE);
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_value");
			gtk_widget_set_sensitive (readout_widget, TRUE);
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, ld[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, the[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* IPB switch isn't allowed:                                              */
		readout_widget = lookup_widget (PHOEBE, "luminosities_ipb_switch");
		gtk_widget_set_sensitive (readout_widget, FALSE);
		}

	if (strcmp (readout_str, "Detached binary") == 0)
		{
		/* 0. Surface potential PHSV isn't constrained:                           */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, phsv[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 1. Surface potential PCSV isn't constrained:                           */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, pcsv[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 2. Gravity brightening GR2 isn't constrained:                          */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, gr2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 3. Bolometric albedo ALB2 isn't constrained:                           */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, alb2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 4. Secondary temperature TAVC isn't constrained:                       */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, tavc[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 5. Secondary star luminosities CLA are constrained:                    */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, cla[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_label");
			gtk_widget_set_sensitive (readout_widget, FALSE);
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_value");
			gtk_widget_set_sensitive (readout_widget, FALSE);
		/* 6. Limb darkening coefficients X2A and Y2A aren't constrained:         */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, ld[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 7. The duration of eclipse for X-Ray binaries is constrained:          */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, the[i]);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* IPB switch is allowed:                                                 */
		readout_widget = lookup_widget (PHOEBE, "luminosities_ipb_switch");
		gtk_widget_set_sensitive (readout_widget, TRUE);
		}

	if (strcmp (readout_str, "Semi-detached binary, primary star fills Roche lobe") == 0)
		{
		/* 0. Surface potential PHSV is constrained:                              */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, phsv[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}

		/* 1. Surface potential PCSV isn't constrained:                           */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, pcsv[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 2. Gravity brightening GR2 isn't constrained:                          */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, gr2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 3. Bolometric albedo ALB2 isn't constrained:                           */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, alb2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 4. Secondary temperature TAVC isn't constrained:                       */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, tavc[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 5. Secondary star luminosities CLA are constrained:                    */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, cla[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_label");
			gtk_widget_set_sensitive (readout_widget, FALSE);
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_value");
			gtk_widget_set_sensitive (readout_widget, FALSE);
		/* 6. Limb darkening coefficients X2A and Y2A aren't constrained:         */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, ld[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 7. The duration of eclipse for X-Ray binaries is constrained:          */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, the[i]);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* IPB switch is allowed:                                                 */
		readout_widget = lookup_widget (PHOEBE, "luminosities_ipb_switch");
		gtk_widget_set_sensitive (readout_widget, TRUE);
		}

	if (strcmp (readout_str, "Semi-detached binary, secondary star fills Roche lobe") == 0)
		{
		/* 0. Surface potential PHSV isn't constrained:                           */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, phsv[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}

		/* 1. Surface potential PCSV is constrained:                              */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, pcsv[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* 2. Gravity brightening GR2 isn't constrained:                          */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, gr2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 3. Bolometric albedo ALB2 isn't constrained:                           */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, alb2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 4. Secondary temperature TAVC isn't constrained:                       */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, tavc[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 5. Secondary star luminosities CLA are constrained:                    */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, cla[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_label");
			gtk_widget_set_sensitive (readout_widget, FALSE);
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_value");
			gtk_widget_set_sensitive (readout_widget, FALSE);
		/* 6. Limb darkening coefficients X2A and Y2A aren't constrained:         */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, ld[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 7. The duration of eclipse for X-Ray binaries is constrained:          */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, the[i]);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* IPB switch is allowed:                                                 */
		readout_widget = lookup_widget (PHOEBE, "luminosities_ipb_switch");
		gtk_widget_set_sensitive (readout_widget, TRUE);
		}
	
	if (strcmp (readout_str, "Double contact binary") == 0)
		{
		/* 0. Surface potential PHSV is constrained:                              */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, phsv[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* 1. Surface potential PCSV is constrained:                              */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, pcsv[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* 2. Gravity brightening GR2 is not constrained:                         */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, gr2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 3. Bolometric albedo ALB2 is not constrained:                          */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, alb2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 4. Secondary temperature TAVC is not constrained:                      */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, tavc[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 5. Secondary star luminosities CLA are constrained:                    */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, cla[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_label");
			gtk_widget_set_sensitive (readout_widget, FALSE);
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_value");
			gtk_widget_set_sensitive (readout_widget, FALSE);
		/* 6. Limb darkening coefficients X2A and Y2A are constrained:            */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, ld[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* 7. The duration of eclipse for X-Ray binaries is constrained:          */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, the[i]);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* IPB switch is allowed:                                                 */
		readout_widget = lookup_widget (PHOEBE, "luminosities_ipb_switch");
		gtk_widget_set_sensitive (readout_widget, TRUE);
		}

	if (strcmp (readout_str, "Overcontact binary of the W UMa type") == 0)
		{
		/* 0. Surface potential PHSV isn't constrained:                           */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, phsv[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 1. Surface potential PCSV is constrained:                              */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, pcsv[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* 2. Gravity brightening GR2 is constrained:                             */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, gr2[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* 3. Bolometric albedo ALB2 is constrained:                              */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, alb2[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* 4. Secondary temperature TAVC is constrained:                          */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, tavc[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* 5. Secondary star luminosities CLA are constrained:                    */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, cla[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_label");
			gtk_widget_set_sensitive (readout_widget, FALSE);
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_value");
			gtk_widget_set_sensitive (readout_widget, FALSE);
		/* 6. Limb darkening coefficients X2A and Y2A are constrained:            */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, ld[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* 7. The duration of eclipse for X-Ray binaries is constrained:          */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, the[i]);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* IPB switch is allowed:                                                 */
		readout_widget = lookup_widget (PHOEBE, "luminosities_ipb_switch");
		gtk_widget_set_sensitive (readout_widget, TRUE);
		}

	if (strcmp (readout_str, "Overcontact binary not in thermal contact") == 0)
		{
		/* 0. Surface potential PHSV isn't constrained:                           */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, phsv[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 1. Surface potential PCSV is constrained:                              */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, pcsv[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* 2. Gravity brightening GR2 isn't constrained:                          */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, gr2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 3. Bolometric albedo ALB2 isn't constrained:                           */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, alb2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 4. Secondary temperature TAVC isn't constrained:                       */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, tavc[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 5. Secondary star luminosities CLA are constrained:                    */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, cla[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_label");
			gtk_widget_set_sensitive (readout_widget, FALSE);
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_value");
			gtk_widget_set_sensitive (readout_widget, FALSE);
		/* 6. Limb darkening coefficients X2A and Y2A aren't constrained:         */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, ld[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 7. The duration of eclipse for X-Ray binaries is constrained:          */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, the[i]);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* IPB switch is allowed:                                                 */
		readout_widget = lookup_widget (PHOEBE, "luminosities_ipb_switch");
		gtk_widget_set_sensitive (readout_widget, TRUE);
		}

	if (strcmp (readout_str, "X-ray binary") == 0)
		{
		/* 0. Surface potential PHSV isn't constrained:                           */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, phsv[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 1. Surface potential PCSV is constrained:                              */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, pcsv[i]);
			if (i == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
			gtk_widget_set_sensitive (readout_widget, FALSE);
			}
		/* 2. Gravity brightening GR2 isn't constrained:                          */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, gr2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 3. Bolometric albedo ALB2 isn't constrained:                           */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, alb2[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 4. Secondary temperature TAVC isn't constrained:                       */
		for (i = 0; i < 6; i++)
			{
			readout_widget = lookup_widget (PHOEBE, tavc[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 5. Secondary star luminosities CLA aren't constrained:                 */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, cla[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_label");
			gtk_widget_set_sensitive (readout_widget, TRUE);
			readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_value");
			gtk_widget_set_sensitive (readout_widget, TRUE);
		/* 6. Limb darkening coefficients X2A and Y2A aren't constrained:         */
		for (i = 0; i < 7; i++)
			{
			readout_widget = lookup_widget (PHOEBE, ld[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* 7. The duration of eclipse for X-Ray binaries isn't constrained:       */
		for (i = 0; i < 4; i++)
			{
			readout_widget = lookup_widget (PHOEBE, the[i]);
			gtk_widget_set_sensitive (readout_widget, TRUE);
			}
		/* IPB switch isn't allowed:                                              */
		readout_widget = lookup_widget (PHOEBE, "luminosities_ipb_switch");
		gtk_widget_set_sensitive (readout_widget, FALSE);
		}
	}

void on_ipb_switch_toggled (GtkToggleButton *togglebutton, gpointer user_data)
	{
	/* The change of the model also changes the sensitivity of this switch, so  */
	/* we don't have to check for constraints. We may freely change the sensi-  */
	/* tivity of dependent widgets.                                             */

	const char *cla[]  = {"luminosities_lc_info_secondary_star_label", "luminosities_cla_adjust", "luminosities_cla_del_label", "luminosities_cla_del_value"};
	int i;
	GtkWidget *readout_widget;

	int activity;
	
	if (GTK_TOGGLE_BUTTON (togglebutton)->active == TRUE) activity = TRUE; else activity = FALSE;
	
	for (i = 0; i < 4; i++)
		{
		readout_widget = lookup_widget (PHOEBE, cla[i]);
		gtk_widget_set_sensitive (readout_widget, activity);
		}
	readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_label");
	gtk_widget_set_sensitive (readout_widget, activity);
	readout_widget = lookup_widget (PHOEBE_assign_lc_luminosity, "assign_lc_luminosity_cla_value");
	gtk_widget_set_sensitive (readout_widget, activity);
	}

void on_fitting_initiate_scripter_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_scripter);
	}

void on_scripter_close_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_scripter);
	}

void on_adjust_switch_toggled_update_fitting_quickbar (GtkToggleButton *togglebutton, gpointer user_data)
	{
	char *main_switches[]     = {"spots_xlat1_adjust", "spots_xlong1_adjust", "spots_radsp1_adjust", "spots_temsp1_adjust", "spots_xlat2_adjust", "spots_xlong2_adjust", "spots_radsp2_adjust", "spots_temsp2_adjust", "system_sma_adjust", "orbit_e_adjust", "orbit_perr0_adjust", "orbit_f1_adjust", "orbit_f2_adjust", "system_pshift_adjust", "system_vga_adjust", "system_incl_adjust", "surface_gr1_adjust", "surface_gr2_adjust", "component_tavh_adjust", "component_tavc_adjust", "surface_alb1_adjust", "surface_alb2_adjust", "component_phsv_adjust", "component_pcsv_adjust", "system_rm_adjust", "system_hjd0_adjust", "system_period_adjust", "system_dpdt_adjust", "orbit_dperdt_adjust", "luminosities_hla_adjust", "luminosities_cla_adjust", "ld_x1a_adjust", "ld_x2a_adjust", "luminosities_el3_adjust"};
	char *quickbar_switches[] = {"fitting_quickbar_latsp1_switch", "fitting_quickbar_longsp1_switch", "fitting_quickbar_radsp1_switch", "fitting_quickbar_temsp1_switch", "fitting_quickbar_latsp2_switch", "fitting_quickbar_longsp2_switch", "fitting_quickbar_radsp2_switch", "fitting_quickbar_temsp2_switch", "fitting_quickbar_sma_switch", "fitting_quickbar_e_switch", "fitting_quickbar_perr0_switch", "fitting_quickbar_f1_switch", "fitting_quickbar_f2_switch", "fitting_quickbar_pshift_switch", "fitting_quickbar_vga_switch", "fitting_quickbar_xincl_switch", "fitting_quickbar_gr1_switch", "fitting_quickbar_gr2_switch", "fitting_quickbar_tavh_switch", "fitting_quickbar_tavc_switch", "fitting_quickbar_alb1_switch", "fitting_quickbar_alb2_switch", "fitting_quickbar_phsv_switch", "fitting_quickbar_pcsv_switch", "fitting_quickbar_rm_switch", "fitting_quickbar_hjd0_switch", "fitting_quickbar_period_switch", "fitting_quickbar_dpdt_switch", "fitting_quickbar_dperdt_switch", "fitting_quickbar_hla_switch", "fitting_quickbar_cla_switch", "fitting_quickbar_x1a_switch", "fitting_quickbar_x2a_switch", "fitting_quickbar_el3_switch"};

	GtkWidget *phoebe_switch, *quickbar_switch;

	int i;

	for (i = 0; i < 34; i++)
		{
		phoebe_switch   = lookup_widget (PHOEBE, main_switches[i]);
		quickbar_switch = lookup_widget (PHOEBE_fitting_quickbar, quickbar_switches[i]);

		if ( (GTK_TOGGLE_BUTTON (phoebe_switch)->active == TRUE) && (GTK_TOGGLE_BUTTON (quickbar_switch)->active == FALSE) )
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (quickbar_switch), TRUE);
		if ( (GTK_TOGGLE_BUTTON (phoebe_switch)->active == FALSE) && (GTK_TOGGLE_BUTTON (quickbar_switch)->active == TRUE) )
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (quickbar_switch), FALSE);
		}
	}

void on_fitting_quickbar_adjust_switch_toggled_update_main_switches (GtkToggleButton *togglebutton, gpointer user_data)
	{
	char *main_switches[]     = {"spots_xlat1_adjust", "spots_xlong1_adjust", "spots_radsp1_adjust", "spots_temsp1_adjust", "spots_xlat2_adjust", "spots_xlong2_adjust", "spots_radsp2_adjust", "spots_temsp2_adjust", "system_sma_adjust", "orbit_e_adjust", "orbit_perr0_adjust", "orbit_f1_adjust", "orbit_f2_adjust", "system_pshift_adjust", "system_vga_adjust", "system_incl_adjust", "surface_gr1_adjust", "surface_gr2_adjust", "component_tavh_adjust", "component_tavc_adjust", "surface_alb1_adjust", "surface_alb2_adjust", "component_phsv_adjust", "component_pcsv_adjust", "system_rm_adjust", "system_hjd0_adjust", "system_period_adjust", "system_dpdt_adjust", "orbit_dperdt_adjust", "luminosities_hla_adjust", "luminosities_cla_adjust", "ld_x1a_adjust", "ld_x2a_adjust", "luminosities_el3_adjust"};
	char *quickbar_switches[] = {"fitting_quickbar_latsp1_switch", "fitting_quickbar_longsp1_switch", "fitting_quickbar_radsp1_switch", "fitting_quickbar_temsp1_switch", "fitting_quickbar_latsp2_switch", "fitting_quickbar_longsp2_switch", "fitting_quickbar_radsp2_switch", "fitting_quickbar_temsp2_switch", "fitting_quickbar_sma_switch", "fitting_quickbar_e_switch", "fitting_quickbar_perr0_switch", "fitting_quickbar_f1_switch", "fitting_quickbar_f2_switch", "fitting_quickbar_pshift_switch", "fitting_quickbar_vga_switch", "fitting_quickbar_xincl_switch", "fitting_quickbar_gr1_switch", "fitting_quickbar_gr2_switch", "fitting_quickbar_tavh_switch", "fitting_quickbar_tavc_switch", "fitting_quickbar_alb1_switch", "fitting_quickbar_alb2_switch", "fitting_quickbar_phsv_switch", "fitting_quickbar_pcsv_switch", "fitting_quickbar_rm_switch", "fitting_quickbar_hjd0_switch", "fitting_quickbar_period_switch", "fitting_quickbar_dpdt_switch", "fitting_quickbar_dperdt_switch", "fitting_quickbar_hla_switch", "fitting_quickbar_cla_switch", "fitting_quickbar_x1a_switch", "fitting_quickbar_x2a_switch", "fitting_quickbar_el3_switch"};

	GtkWidget *phoebe_switch, *quickbar_switch;

	int i;

	for (i = 0; i < 34; i++)
		{
		quickbar_switch = lookup_widget (PHOEBE_fitting_quickbar, quickbar_switches[i]);
		phoebe_switch   = lookup_widget (PHOEBE, main_switches[i]);

		if ( (GTK_TOGGLE_BUTTON (quickbar_switch)->active == TRUE) && (GTK_TOGGLE_BUTTON (phoebe_switch)->active == FALSE) )
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (phoebe_switch), TRUE);
		if ( (GTK_TOGGLE_BUTTON (quickbar_switch)->active == FALSE) && (GTK_TOGGLE_BUTTON (phoebe_switch)->active == TRUE) )
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (phoebe_switch), FALSE);
		}
	}

void on_step_value_changed_update_fitting_quickbar (GtkEditable *editable, gpointer user_data)
	{
	char *main_steps[]     = {"", "", "", "", "", "", "", "", "system_sma_step_value", "orbit_e_del_value", "orbit_perr0_del_value", "orbit_f1_del_value", "orbit_f2_del_value", "system_pshift_step_value", "system_vga_step_value", "system_incl_step_value", "surface_gr1_del_value", "surface_gr2_del_value", "component_tavh_del_value", "component_tavc_del_value", "surface_alb1_del_value", "surface_alb2_del_value", "component_phsv_del_value", "component_pcsv_del_value", "system_rm_step_value", "system_hjd0_step_value", "system_period_step_value", "system_dpdt_step_value", "orbit_dperdt_del_value", "luminosities_hla_del_value", "luminosities_cla_del_value", "ld_x1a_del_value", "ld_x2a_del_value", "luminosities_el3_del_value"};
	char *quickbar_steps[] = {"", "", "", "", "", "", "", "", "fitting_quickbar_sma_step_value", "fitting_quickbar_e_step_value", "fitting_quickbar_perr0_step_value", "fitting_quickbar_f1_step_value", "fitting_quickbar_f2_step_value", "fitting_quickbar_pshift_step_value", "fitting_quickbar_vga_step_value", "fitting_quickbar_xincl_step_value", "fitting_quickbar_gr1_step_value", "fitting_quickbar_gr2_step_value", "fitting_quickbar_tavh_step_value", "fitting_quickbar_tavc_step_value", "fitting_quickbar_alb1_step_value", "fitting_quickbar_alb2_step_value", "fitting_quickbar_phsv_step_value", "fitting_quickbar_pcsv_step_value", "fitting_quickbar_rm_step_value", "fitting_quickbar_hjd0_step_value", "fitting_quickbar_period_step_value", "fitting_quickbar_dpdt_step_value", "fitting_quickbar_dperdt_step_value", "fitting_quickbar_hla_step_value", "fitting_quickbar_cla_step_value", "fitting_quickbar_x1a_step_value", "fitting_quickbar_x2a_step_value", "fitting_quickbar_el3_step_value"};

	GtkWidget *main_step, *quickbar_step;

	int i;

	for (i = 0; i < 34; i++)
		{
		/* Spots still have to be supported:                                      */
		if (i < 8) continue;

		if ( (i == 25) || (i == 26) )
			{
			/* These widgets are not spin-buttons and thus we cannot check their    */
			/* values the same way as others.                                       */
			continue;
			}

		main_step     = lookup_widget (PHOEBE, main_steps[i]);
		quickbar_step = lookup_widget (PHOEBE_fitting_quickbar, quickbar_steps[i]);

		if ( fabs (gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (main_step)) - gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (quickbar_step))) > 1E-5 )
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (quickbar_step), gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (main_step)));
		}
	}

void on_fitting_quickbar_step_value_changed_update_main_step_values (GtkEditable *editable, gpointer user_data)
	{
	char *main_steps[]     = {"", "", "", "", "", "", "", "", "system_sma_step_value", "orbit_e_del_value", "orbit_perr0_del_value", "orbit_f1_del_value", "orbit_f2_del_value", "system_pshift_step_value", "system_vga_step_value", "system_incl_step_value", "surface_gr1_del_value", "surface_gr2_del_value", "component_tavh_del_value", "component_tavc_del_value", "surface_alb1_del_value", "surface_alb2_del_value", "component_phsv_del_value", "component_pcsv_del_value", "system_rm_step_value", "system_hjd0_step_value", "system_period_step_value", "system_dpdt_step_value", "orbit_dperdt_del_value", "luminosities_hla_del_value", "luminosities_cla_del_value", "ld_x1a_del_value", "ld_x2a_del_value", "luminosities_el3_del_value"};
	char *quickbar_steps[] = {"", "", "", "", "", "", "", "", "fitting_quickbar_sma_step_value", "fitting_quickbar_e_step_value", "fitting_quickbar_perr0_step_value", "fitting_quickbar_f1_step_value", "fitting_quickbar_f2_step_value", "fitting_quickbar_pshift_step_value", "fitting_quickbar_vga_step_value", "fitting_quickbar_xincl_step_value", "fitting_quickbar_gr1_step_value", "fitting_quickbar_gr2_step_value", "fitting_quickbar_tavh_step_value", "fitting_quickbar_tavc_step_value", "fitting_quickbar_alb1_step_value", "fitting_quickbar_alb2_step_value", "fitting_quickbar_phsv_step_value", "fitting_quickbar_pcsv_step_value", "fitting_quickbar_rm_step_value", "fitting_quickbar_hjd0_step_value", "fitting_quickbar_period_step_value", "fitting_quickbar_dpdt_step_value", "fitting_quickbar_dperdt_step_value", "fitting_quickbar_hla_step_value", "fitting_quickbar_cla_step_value", "fitting_quickbar_x1a_step_value", "fitting_quickbar_x2a_step_value", "fitting_quickbar_el3_step_value"};

	GtkWidget *main_step, *quickbar_step;

	int i;

	for (i = 0; i < 34; i++)
		{
		/* Spots still have to be supported:                                      */
		if (i < 8) continue;

		if ( (i == 25) || (i == 26) )
			{
			/* These widgets are not spin-buttons and thus we cannot check their    */
			/* values the same way as others.                                       */
			continue;
			}

		quickbar_step = lookup_widget (PHOEBE_fitting_quickbar, quickbar_steps[i]);
		main_step     = lookup_widget (PHOEBE, main_steps[i]);

		if ( fabs (gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (quickbar_step)) - gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (main_step))) > 1E-5 )
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (main_step), gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (quickbar_step)));
		}
	}

void on_data_file_dependent_variable_changed (GtkEditable *editable, gpointer user_data)
	{
	/* This function takes care that the reddening is allowed to be removed on- */
	/* ly when magnitudes are the dependent variable:                           */

	GtkWidget *readout_widget = lookup_widget (PHOEBE_assign_data_file, "data_file_column_2_entry");
	if (strcmp (gtk_entry_get_text (GTK_ENTRY (readout_widget)), "Magnitude") != 0)
		{
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_assign_data_file, "data_file_reddening_switch")), FALSE);
		gtk_widget_set_sensitive (lookup_widget (PHOEBE_assign_data_file, "data_file_reddening_switch"), FALSE);
		gtk_widget_set_sensitive (lookup_widget (PHOEBE_assign_data_file, "data_file_r_label"), FALSE);
		gtk_widget_set_sensitive (lookup_widget (PHOEBE_assign_data_file, "data_file_r_value"), FALSE);
		gtk_widget_set_sensitive (lookup_widget (PHOEBE_assign_data_file, "data_file_color_excess_label"), FALSE);
		gtk_widget_set_sensitive (lookup_widget (PHOEBE_assign_data_file, "data_file_color_excess_value"), FALSE);
		}
	else
		gtk_widget_set_sensitive (lookup_widget (PHOEBE_assign_data_file, "data_file_reddening_switch"), TRUE);
	}

void set_sensitivity_of_spots_widgets ()
{
	int sp_prim_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "spots_sprim_value")));
	int sp_sec_no  = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "spots_ssec_value")));
	int spots_no;
	int i;

	char working_string[255];
	char *working_str = working_string;

	GtkWidget *menu  = gtk_menu_new ();
	GtkWidget *menu2 = gtk_menu_new ();
	GtkWidget *menu3 = gtk_menu_new ();
	GtkWidget *menu4 = gtk_menu_new ();
	GtkWidget *menuitem;

	/* First, let's take care of the sensitivity:                               */
	if ( sp_prim_no + sp_sec_no == 0 ) {
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE, "spots_spot_1_adjust")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE, "spots_spot_2_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_spot_1_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_spot_2_adjust")), FALSE);

		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_xlat1_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_xlong1_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_radsp1_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_temsp1_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_xlat2_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_xlong2_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_radsp2_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_temsp2_adjust")), FALSE);

		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp1_switch")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp1_switch")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp1_switch")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp1_switch")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp2_switch")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp2_switch")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp2_switch")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp2_switch")), FALSE);

		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp1_switch")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp1_switch")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp1_switch")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp1_switch")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp1_step_value")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp1_step_value")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp1_step_value")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp1_step_value")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp2_switch")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp2_switch")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp2_switch")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp2_switch")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp2_step_value")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp2_step_value")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp2_step_value")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp2_step_value")), FALSE);
	}
	if ( sp_prim_no + sp_sec_no == 1 ) {
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE, "spots_spot_1_adjust")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE, "spots_spot_2_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_spot_2_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_xlat2_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_xlong2_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_radsp2_adjust")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE, "spots_temsp2_adjust")), FALSE);

		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp2_switch")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp2_switch")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp2_switch")), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp2_switch")), FALSE);

		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp1_switch")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp1_switch")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp1_switch")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp1_switch")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp1_step_value")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp1_step_value")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp1_step_value")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp1_step_value")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp2_switch")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp2_switch")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp2_switch")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp2_switch")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp2_step_value")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp2_step_value")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp2_step_value")), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp2_step_value")), FALSE);
	}
	if ( sp_prim_no + sp_sec_no >= 2 ) {
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE, "spots_spot_1_adjust")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE, "spots_spot_2_adjust")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp1_switch")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp1_switch")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp1_switch")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp1_switch")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp1_step_value")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp1_step_value")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp1_step_value")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp1_step_value")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp2_switch")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp2_switch")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp2_switch")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp2_switch")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_latsp2_step_value")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_longsp2_step_value")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_radsp2_step_value")), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (lookup_widget (PHOEBE_fitting_quickbar, "fitting_quickbar_temsp2_step_value")), TRUE);
	}

	/* The first option that has to be handled is the spot source, that could   */
	/* either the first or the second star. However, both spots to be adjusted  */
	/* may just as well be on only one star, so this gets a bit trickier... ;)  */
	gtk_option_menu_remove_menu (GTK_OPTION_MENU (lookup_widget (PHOEBE, "spots_spot_1_source_list")));
	gtk_option_menu_remove_menu (GTK_OPTION_MENU (lookup_widget (PHOEBE, "spots_spot_2_source_list")));

	if (sp_prim_no != 0) {
		menuitem = gtk_menu_item_new_with_label ("on primary"); gtk_widget_show (menuitem);
		gtk_menu_prepend (GTK_MENU (menu), menuitem);
		menuitem = gtk_menu_item_new_with_label ("on primary"); gtk_widget_show (menuitem);
		gtk_menu_prepend (GTK_MENU (menu2), menuitem);
	}
	if (sp_sec_no != 0) {
		menuitem = gtk_menu_item_new_with_label ("on secondary"); gtk_widget_show (menuitem);
		gtk_menu_append (GTK_MENU (menu), menuitem);
		menuitem = gtk_menu_item_new_with_label ("on secondary"); gtk_widget_show (menuitem);
		gtk_menu_append (GTK_MENU (menu2), menuitem);
	}

	gtk_option_menu_set_menu (GTK_OPTION_MENU (lookup_widget (PHOEBE, "spots_spot_1_source_list")), menu);
	gtk_option_menu_set_menu (GTK_OPTION_MENU (lookup_widget (PHOEBE, "spots_spot_2_source_list")), menu2);

	/* Now we have to do the same thing, but for spot number; we are going to   */
	/* be a bit sloppy here (maybe change it in future), but we will actually   */
	/* add the max (s1, s2) number of entries to this menu. Thus it might hap-  */
	/* pen that the user chooses non-existent spot, but things would complicate */
	/* beyond my current mood for programming.                                  */
	gtk_option_menu_remove_menu (GTK_OPTION_MENU (lookup_widget (PHOEBE, "spots_spot_1_spot_list")));
	gtk_option_menu_remove_menu (GTK_OPTION_MENU (lookup_widget (PHOEBE, "spots_spot_2_spot_list")));

	if (sp_prim_no > sp_sec_no) spots_no = sp_prim_no; else spots_no = sp_sec_no;
	for (i = 0; i < spots_no; i++) {
		sprintf (working_str, "Spot %d", i+1);
		menuitem = gtk_menu_item_new_with_label (working_str); gtk_widget_show (menuitem);
		gtk_menu_append (GTK_MENU (menu3), menuitem);
		menuitem = gtk_menu_item_new_with_label (working_str); gtk_widget_show (menuitem);
		gtk_menu_append (GTK_MENU (menu4), menuitem);
	}

	gtk_option_menu_set_menu (GTK_OPTION_MENU (lookup_widget (PHOEBE, "spots_spot_1_spot_list")), menu3);
	gtk_option_menu_set_menu (GTK_OPTION_MENU (lookup_widget (PHOEBE, "spots_spot_2_spot_list")), menu4);
}

void on_spots_sprim_value_changed (GtkEditable *editable, gpointer user_data)
	{
	add_empty_record_to_spots_primary_info_list ();
	set_sensitivity_of_spots_widgets ();
	}

void on_spots_ssec_value_changed (GtkEditable *editable, gpointer user_data)
	{
	add_empty_record_to_spots_secondary_info_list ();
	set_sensitivity_of_spots_widgets ();
	}

void on_assign_primary_spots_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *sp_list = lookup_widget (PHOEBE, "spots_primary_info_list");
	GtkWidget *readout_widget;

	int selected_row;
	double value;

	char working_string[255];
	char *working_str = working_string;

	char *readout_str;

	/* Let's find the selected row:                                             */
	selected_row = (int) ((GList *) (GTK_CLIST (sp_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_assign_primary_spots, "assign_spots_xlat_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%5.5lf", value);
	gtk_clist_set_text (GTK_CLIST (sp_list), selected_row, 1, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_primary_spots, "assign_spots_xlong_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%5.5lf", value);
	gtk_clist_set_text (GTK_CLIST (sp_list), selected_row, 2, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_primary_spots, "assign_spots_radsp_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%5.5lf", value);
	gtk_clist_set_text (GTK_CLIST (sp_list), selected_row, 3, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_primary_spots, "assign_spots_temsp_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%5.5lf", value);
	gtk_clist_set_text (GTK_CLIST (sp_list), selected_row, 4, working_str);

	gtk_widget_hide (PHOEBE_assign_primary_spots);
	}

void on_assign_primary_spots_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_assign_primary_spots);
	}

void on_assign_secondary_spots_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *sp_list = lookup_widget (PHOEBE, "spots_secondary_info_list");
	GtkWidget *readout_widget;

	int selected_row;
	double value;

	char working_string[255];
	char *working_str = working_string;

	char *readout_str;

	/* Let's find the selected row:                                             */
	selected_row = (int) ((GList *) (GTK_CLIST (sp_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_assign_secondary_spots, "assign_spots_xlat_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%5.5lf", value);
	gtk_clist_set_text (GTK_CLIST (sp_list), selected_row, 1, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_secondary_spots, "assign_spots_xlong_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%5.5lf", value);
	gtk_clist_set_text (GTK_CLIST (sp_list), selected_row, 2, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_secondary_spots, "assign_spots_radsp_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%5.5lf", value);
	gtk_clist_set_text (GTK_CLIST (sp_list), selected_row, 3, working_str);

	readout_widget = lookup_widget (PHOEBE_assign_secondary_spots, "assign_spots_temsp_value");
	value = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	sprintf (working_str, "%5.5lf", value);
	gtk_clist_set_text (GTK_CLIST (sp_list), selected_row, 4, working_str);

	gtk_widget_hide (PHOEBE_assign_secondary_spots);
	}

void on_assign_secondary_spots_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_hide (PHOEBE_assign_secondary_spots);
	}

void on_dc_show_correlation_matrix_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_dc_correlation_matrix);
	}

void on_luminosities_star_image_plot_button_clicked (GtkButton *button, gpointer user_data)
	{
	print_to_status_bar ("Generating 3D image of a binary star at a given phase...");
	plot_3d_image_plot (x11, NULL);
	}

void on_luminosities_star_image_phase_value_changed (GtkEditable *editable, gpointer user_data)
	{
	/* This callback takes care of the automatic replotting of binary image in  */
	/* Luminosities tab when phase value is changed. It should be executed only */
	/* if PHOEBE_3D_PLOT_CALLBACK_OPTION is set to 1 in Configuration window.   */

	if (PHOEBE_3D_PLOT_CALLBACK_OPTION == 1)
		{
		print_to_status_bar ("Generating 3D image of a binary star at a given phase...");
		plot_3d_image_plot (x11, NULL);
		}
	}

void on_data_star_name_entry_changed (GtkEditable *editable, gpointer user_data)
	{
	/* This procedure changes the PHOEBE window label to contain star name:     */
	char *readout_str = gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE, "data_star_name_entry")));

	char working_string[255];
	char *working_str = working_string;

	sprintf (working_str, "PHOEBE: %s", readout_str);
  gtk_window_set_title (GTK_WINDOW (PHOEBE), working_str);
	}

void on_lc_data_file_filter_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_object_remove_data (GTK_OBJECT (PHOEBE_filter_menu), "filter_source");
	gtk_menu_popup (GTK_MENU (PHOEBE_filter_menu), NULL, NULL, NULL, NULL, 1, 0);
	gtk_object_set_data (GTK_OBJECT (PHOEBE_filter_menu), "filter_source", button);
	}

void on_rv_data_file_filter_button_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_object_remove_data (GTK_OBJECT (PHOEBE_filter_menu), "filter_source");
	gtk_menu_popup (GTK_MENU (PHOEBE_filter_menu), NULL, NULL, NULL, NULL, 1, 0);
	gtk_object_set_data (GTK_OBJECT (PHOEBE_filter_menu), "filter_source", button);
	}

void on_filter_menu_specific_filter_activate (GtkMenuItem *menuitem, gpointer user_data)
	{
	/* This function reads the label of the selected menu item and writes it to */
	/* the button label; when called, the button should introduce itself as     */
	/* "filter_source" in PHOEBE_filter_menu widget.                            */

	char *readout_str;

	gtk_label_get (GTK_LABEL(GTK_BIN(menuitem)->child), &readout_str);
	gtk_label_set (GTK_LABEL(GTK_BIN(lookup_widget (PHOEBE_filter_menu, "filter_source"))->child), readout_str);
	}

void on_lagrange_dependent_variable_changed (GtkEditable *editable, gpointer user_data)
	{
	PHOEBE_main_parameters main = read_in_main_parameters ();

	double L1crit, L2crit;
	
	char working_string[255];
	char *working_str = working_string;

	GtkWidget *readout_widget;

	calculate_critical_potentials (main.RM, main.F1, main.E, &L1crit, &L2crit);

	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_lagrange_l1_potential_value");
	sprintf (working_str, "%5.5lf", L1crit);
	gtk_label_set_text (GTK_LABEL (readout_widget), working_str);
	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_lagrange_l2_potential_value");
	sprintf (working_str, "%5.5lf", L2crit);
	gtk_label_set_text (GTK_LABEL (readout_widget), working_str);

	readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_lagrange_l1_potential_value");
	sprintf (working_str, "%5.5lf", L1crit);
	gtk_label_set_text (GTK_LABEL (readout_widget), working_str);
	readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_lagrange_l2_potential_value");
	sprintf (working_str, "%5.5lf", L2crit);
	gtk_label_set_text (GTK_LABEL (readout_widget), working_str);

	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_lagrange_l1_exceeded_label");
	if (main.PHSV < L1crit) gtk_label_set_text (GTK_LABEL (readout_widget), "yes");
	                   else gtk_label_set_text (GTK_LABEL (readout_widget), "no");

	readout_widget = lookup_widget (PHOEBE_plot_lc, "plot_lc_lagrange_l2_exceeded_label");
	if (main.PHSV < L2crit) gtk_label_set_text (GTK_LABEL (readout_widget), "yes");
	                   else gtk_label_set_text (GTK_LABEL (readout_widget), "no");

	readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_lagrange_l1_exceeded_label");
	if (main.PHSV < L1crit) gtk_label_set_text (GTK_LABEL (readout_widget), "yes");
	                   else gtk_label_set_text (GTK_LABEL (readout_widget), "no");

	readout_widget = lookup_widget (PHOEBE_plot_rv, "plot_rv_lagrange_l2_exceeded_label");
	if (main.PHSV < L2crit) gtk_label_set_text (GTK_LABEL (readout_widget), "yes");
	                   else gtk_label_set_text (GTK_LABEL (readout_widget), "no");
	}

void on_data_sheet_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *readout_widget;
	char *readout_str;

	gtk_clist_clear (GTK_CLIST (lookup_widget (PHOEBE_data_sheet, "data_sheet_info_list")));

	readout_widget = lookup_widget (PHOEBE_data_sheet, "data_sheet_show_list");
	gtk_label_get (GTK_LABEL(GTK_BIN(readout_widget)->child), &readout_str);

	if (strcmp (readout_str, "Show all parameters") == 0)
		add_all_parameters_to_data_sheet_list ();
	else
		add_relevant_parameters_to_data_sheet_list ();

	gtk_widget_show (PHOEBE_data_sheet);
	}

void on_scripter_add_action_button_clicked (GtkButton *button, gpointer user_data)
	{
	char *widgets[] = {"scripter_parameter1_label", "scripter_parameter2_label", "scripter_parameter3_label", "scripter_parameter4_label"};
	char *entries[] = {"scripter_parameter1_entry", "scripter_parameter2_entry", "scripter_parameter3_entry", "scripter_parameter4_entry"};
	GtkWidget *script_list = lookup_widget (PHOEBE_scripter, "scripter_info_list");
	GtkWidget *readout_widget;

	char entry_string[3][255];
	char *entry[3] = {entry_string[0], entry_string[1], entry_string[2]};

	char *readout_str;
	int i;

	readout_widget = lookup_widget (PHOEBE_scripter, "scripter_action_list");
	gtk_label_get (GTK_LABEL(GTK_BIN(readout_widget)->child), &readout_str);
	sprintf (entry[0], readout_str);

	sprintf (entry[1], "");
	for (i = 0; i < 4; i++)
		{
		if (GTK_WIDGET_VISIBLE (lookup_widget (PHOEBE_scripter, widgets[i])))
			{
			readout_widget = lookup_widget (PHOEBE_scripter, entries[i]);
			readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
			if (i == 0) sprintf (entry[1], "%s",     readout_str);
			       else sprintf (entry[1], "%s, %s", entry[1], readout_str);
			}
		}

	sprintf (entry[2], "not executed");
	gtk_clist_append (GTK_CLIST (script_list), entry);
	}

void on_scripter_update_action_button_clicked (GtkButton *button, gpointer user_data)
	{
	char *widgets[] = {"scripter_parameter1_label", "scripter_parameter2_label", "scripter_parameter3_label", "scripter_parameter4_label"};
	char *entries[] = {"scripter_parameter1_entry", "scripter_parameter2_entry", "scripter_parameter3_entry", "scripter_parameter4_entry"};
	GtkWidget *script_list = lookup_widget (PHOEBE_scripter, "scripter_info_list");
	GtkWidget *readout_widget;

	char working_string[255];
	char *working_str = working_string;

	char *readout_str;
	int i;
	int selected_row;

	if (GTK_CLIST (script_list)->rows == 0) return;       /* Nothing to delete. */

	selected_row  = (int) ((GList *) (GTK_CLIST (script_list)->selection))->data;

	readout_widget = lookup_widget (PHOEBE_scripter, "scripter_action_list");
	gtk_label_get (GTK_LABEL(GTK_BIN(readout_widget)->child), &readout_str);
	gtk_clist_set_text (GTK_CLIST (script_list), selected_row, 0, readout_str);

	sprintf (working_str, "");
	for (i = 0; i < 4; i++)
		{
		if (GTK_WIDGET_VISIBLE (lookup_widget (PHOEBE_scripter, widgets[i])))
			{
			readout_widget = lookup_widget (PHOEBE_scripter, entries[i]);
			readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
			if (i == 0) sprintf (working_str, "%s",     readout_str);
			       else sprintf (working_str, "%s, %s", working_str, readout_str);
			}
		}
	gtk_clist_set_text (GTK_CLIST (script_list), selected_row, 1, working_str);

	gtk_clist_set_text (GTK_CLIST (script_list), selected_row, 2, "not executed");
	}

void on_scripter_delete_action_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *script_list = lookup_widget (PHOEBE_scripter, "scripter_info_list");
	int selected_row;

	if (GTK_CLIST (script_list)->rows == 0) return;       /* Nothing to delete. */

	selected_row  = (int) ((GList *) (GTK_CLIST (script_list)->selection))->data;
	gtk_clist_remove (GTK_CLIST (script_list), selected_row);
	}

void on_scripter_move_action_up_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *script_list = lookup_widget (PHOEBE_scripter, "scripter_info_list");
	int selected_row = (int) ((GList *) (GTK_CLIST (script_list)->selection))->data;

	/* This call's legality is taken care of in GTK+. Thus, we just call it:    */
	gtk_clist_swap_rows (GTK_CLIST (script_list), selected_row, selected_row - 1);
	}

void on_scripter_move_action_down_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *script_list = lookup_widget (PHOEBE_scripter, "scripter_info_list");
	int selected_row = (int) ((GList *) (GTK_CLIST (script_list)->selection))->data;

	/* This call's legality is taken care of in GTK+. Thus, we just call it:    */
	gtk_clist_swap_rows (GTK_CLIST (script_list), selected_row, selected_row + 1);
	}

void on_scripter_execute_script_button_clicked (GtkButton *button, gpointer user_data)
	{
	GtkWidget *script_list = lookup_widget (PHOEBE_scripter, "scripter_info_list");
	char *readout_str;
	char *param_str;
	int i, j;

	int control_switch = 0;
	char working_string[255];
	char *working_str = working_string;

	char param1_string[255]; char *param1_str = param1_string;
	char param2_string[255]; char *param2_str = param2_string;
	char param3_string[255]; char *param3_str = param3_string;

	char *parsed;

	/* This is needed for LC and RV plots:                                      */
	PHOEBE_plot_device device;

	/* Adjust switches are needed for PHOEBE keywords correlation:              */
	const char *keywords[] = {"XLAT1", "XLONG1", "RADSP1", "TEMSP1", "XLAT2", "XLONG2", "RADSP2", "TEMSP2", "SMA", "E", "PERR0", "F1", "F2", "PSHIFT", "VGA", "INCL", "GR1", "GR2", "TAVH", "TAVC", "ALB1", "ALB2", "PHSV", "PCSV", "RM", "HJD0", "PERIOD", "DPDT", "DPERDT", "HLA", "CLA", "X1A", "X2A", "EL3"};
	const char *switches[] = {"spots_xlat1_adjust", "spots_xlong1_adjust", "spots_radsp1_adjust", "spots_temsp1_adjust", "spots_xlat2_adjust", "spots_xlong2_adjust", "spots_radsp2_adjust", "spots_temsp2_adjust", "system_sma_adjust", "orbit_e_adjust", "orbit_perr0_adjust", "orbit_f1_adjust", "orbit_f2_adjust", "system_pshift_adjust", "system_vga_adjust", "system_incl_adjust", "surface_gr1_adjust", "surface_gr2_adjust", "component_tavh_adjust", "component_tavc_adjust", "surface_alb1_adjust", "surface_alb2_adjust", "component_phsv_adjust", "component_pcsv_adjust", "system_rm_adjust", "system_hjd0_adjust", "system_period_adjust", "system_dpdt_adjust", "orbit_dperdt_adjust", "luminosities_hla_adjust", "luminosities_cla_adjust", "ld_x1a_adjust", "ld_x2a_adjust", "luminosities_el3_adjust"};
	char *token; /* Its memory will be allocated internally by strdup () call.  */
	GtkWidget *readout_widget;

	for (i = 0; i < GTK_CLIST (script_list)->rows; i++)
		{
		gtk_clist_get_text (GTK_CLIST (script_list), i, 0, &readout_str);
		if (strcmp (readout_str, "Quit PHOEBE") == 0)
			{
			script_phoebe_quit ();
			control_switch = 1;
			}
		if (strcmp (readout_str, "Open Keyword File") == 0)
			{
			gtk_clist_get_text (GTK_CLIST (script_list), i, 1, &param_str);
			script_open_file (param_str);
			control_switch = 1;
			}
		if (strcmp (readout_str, "Save Keyword File") == 0)
			{
			gtk_clist_get_text (GTK_CLIST (script_list), i, 1, &param_str);
			script_save_file (param_str);
			control_switch = 1;
			}
		if (strcmp (readout_str, "Plot LC to File") == 0)
			{
			gtk_clist_get_text (GTK_CLIST (script_list), i, 1, &param_str);

			/* Let's parse the parameters' string:                                  */
			token = strdup (param_str);
			param1_str = strtok (token, ",");
			param2_str = strtok (NULL, ",");
			param3_str = strtok (NULL, ",");

			/* If any blanks remained at the beginning or the end of any of these   */
			/* strings, let's remove them:                                          */
			while (param1_str[strlen(param1_str)-1] == ' ') strip_string_tail (param1_str);
			while (param2_str[strlen(param1_str)-1] == ' ') strip_string_tail (param2_str);
			while (param3_str[strlen(param1_str)-1] == ' ') strip_string_tail (param3_str);
			while (param1_str[0] == ' ') param1_str++;
			while (param2_str[0] == ' ') param2_str++;
			while (param3_str[0] == ' ') param3_str++;

			if (strcmp (param2_str, "ascii") == 0) device = ascii;
			if (strcmp (param2_str, "eps")   == 0) device = eps;
			if (strcmp (param2_str, "xpm")   == 0) device = xpm;
			if (strcmp (param2_str, "gif")   == 0) device = gif;
			if (strcmp (param2_str, "ppm")   == 0) device = ppm;
			if (strcmp (param2_str, "png")   == 0) device = png;
			script_plot_lc_to_file (param1_str, device, param3_str);
			control_switch = 1;
			}
		if (strcmp (readout_str, "Plot RV to File") == 0)
			{
			gtk_clist_get_text (GTK_CLIST (script_list), i, 1, &param_str);

			/* Let's parse the parameters' string:                                  */
			token = strdup (param_str);
			param1_str = strtok (token, ",");
			param2_str = strtok (NULL, ",");
			param3_str = strtok (NULL, ",");

			/* If any blanks remained at the beginning or the end of any of these   */
			/* strings, let's remove them:                                          */
			while (param1_str[strlen(param1_str)-1] == ' ') strip_string_tail (param1_str);
			while (param2_str[strlen(param1_str)-1] == ' ') strip_string_tail (param2_str);
			while (param3_str[strlen(param1_str)-1] == ' ') strip_string_tail (param3_str);
			while (param1_str[0] == ' ') param1_str++;
			while (param2_str[0] == ' ') param2_str++;
			while (param3_str[0] == ' ') param3_str++;

			if (strcmp (param2_str, "ascii") == 0) device = ascii;
			if (strcmp (param2_str, "eps")   == 0) device = eps;
			if (strcmp (param2_str, "xpm")   == 0) device = xpm;
			if (strcmp (param2_str, "gif")   == 0) device = gif;
			if (strcmp (param2_str, "ppm")   == 0) device = ppm;
			if (strcmp (param2_str, "png")   == 0) device = png;
			script_plot_rv_to_file (param1_str, device, param3_str);
			control_switch = 1;
			}
		if (strcmp (readout_str, "Calculate Circular Gravity Potential for Primary Star") == 0)
			{
			gtk_clist_get_text (GTK_CLIST (script_list), i, 1, &param_str);
			sscanf (param_str, "%s%s", param1_str, param2_str);
			strip_string_tail (param1_str);          /* To get rid of the comma (,) */
			script_calculate_circular_phsv_value (atof (param1_str), atof (param2_str));
			control_switch = 1;
			}
		if (strcmp (readout_str, "Calculate Circular Gravity Potential for Secondary Star") == 0)
			{
			gtk_clist_get_text (GTK_CLIST (script_list), i, 1, &param_str);
			sscanf (param_str, "%s%s", param1_str, param2_str);
			strip_string_tail (param1_str);          /* To get rid of the comma (,) */
			script_calculate_circular_pcsv_value (atof (param1_str), atof (param2_str));
			control_switch = 1;
			}
		if (strcmp (readout_str, "Change Parameter Value") == 0)
			{
			gtk_clist_get_text (GTK_CLIST (script_list), i, 1, &param_str);

			token = strdup (param_str);
			param1_str = strtok (token, ",");
			param2_str = strtok (NULL, "\0");
			while (param2_str[strlen(param2_str)-1] == ' ') strip_string_tail (param2_str);
			while (param2_str[0] == ' ') param2_str++;

			script_change_parameter_value (param1_str, param2_str);
			control_switch = 1;
			}
		if (strcmp (readout_str, "Add Parameter To Data Sheet") == 0)
			{
			gtk_clist_get_text (GTK_CLIST (script_list), i, 1, &param_str);
			script_add_parameter_to_data_sheet (param_str);
			control_switch = 1;
			}
		if (strcmp (readout_str, "Save Data Sheet To File") == 0)
			{
			gtk_clist_get_text (GTK_CLIST (script_list), i, 1, &param_str);
			script_save_data_sheet_to_file (param_str);
			control_switch = 1;
			}
		if (strcmp (readout_str, "Save Relevant Data Sheet To File") == 0)
			{
			gtk_clist_get_text (GTK_CLIST (script_list), i, 1, &param_str);
			script_save_relevant_data_sheet_to_file (param_str);
			control_switch = 1;
			}
		if (strcmp (readout_str, "Adjust Parameters") == 0)
			{
			/* This parameter may actually contain many comma separated parameters. */
			gtk_clist_get_text (GTK_CLIST (script_list), i, 1, &param_str);

			/* Parameters must be PHOEBE keywords, this determines which adjustment */
			/* switches we have to turn on.                                         */

			/* 1. step: turn all adjust switches off:                               */
			for (j = 0; j < 33; j++)
				{
				readout_widget = lookup_widget (PHOEBE, switches[j]);
				if (GTK_TOGGLE_BUTTON (readout_widget)->active)
					gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
				}

			/* 2. step: turn on selected adjustment switches:                       */
			token = strdup (param_str);
			param1_str = strtok (token, ",");

			while (param1_str != NULL)
				{
				/* Clear all spaces before and after the keyword:                     */
				while (param1_str[strlen(param1_str)-1] == ' ') strip_string_tail (param1_str);
				while (param1_str[0] == ' ') param1_str++;

				/* Now the comparison function:                                       */
				for (j = 0; j < 33; j++)
					{
					if (strcmp (param1_str, keywords[j]) == 0)
						{
						readout_widget = lookup_widget (PHOEBE, switches[j]);
						gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), TRUE);
						}
					}
				param1_str = strtok (NULL, ",");
				}

			/* 3. step: call the fitting function through a scripter call:          */
			script_adjust_parameters ();
			
			/* 4. step: turn all adjustment switches off again:                     */
			for (j = 0; j < 33; j++)
				{
				readout_widget = lookup_widget (PHOEBE, switches[j]);
				if (GTK_TOGGLE_BUTTON (readout_widget)->active)
					gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (readout_widget), FALSE);
				}

			control_switch = 1;
			}

		if (strcmp (readout_str, "Estimate Normalizing Magnitude") == 0)
			{
			script_estimate_normalizing_magnitude ();
			control_switch = 1;
			}

		if (control_switch == 1)
			{
			gtk_clist_set_text (GTK_CLIST (script_list), i, 2, "executed");
			control_switch = 0;
			}
		else
			{
			sprintf (working_str, "command '%s' not found, skipping...", readout_str);
			script_warning (working_str);
			}
		}


/*
	if (match == 0)
		{
		sprintf (working_str, "Scripter command \"%s\" unknown", readout_str);
		readout_widget = create_notice_window (
			"Notice",
			working_str,
		  "You are using the unsupported scripter command",
			"in your script. It will be skipped during execution.",
			gtk_widget_destroy);
		}
*/

	}

void on_scripter_action_list_changed (GtkContainer *container, GtkWidget *widget, gpointer user_data)
	{
	char *labels[] = 
		{
		"scripter_parameter1_label",
		"scripter_parameter2_label",
		"scripter_parameter3_label",
		"scripter_parameter4_label"
		};

	char *entries[] =
		{
		"scripter_parameter1_entry",
		"scripter_parameter2_entry",
		"scripter_parameter3_entry",
		"scripter_parameter4_entry"
		};

	GtkWidget *readout_widget;

	char *readout_str;
	int i, j;

	readout_widget = lookup_widget (PHOEBE_scripter, "scripter_action_list");
	gtk_label_get (GTK_LABEL(GTK_BIN(readout_widget)->child), &readout_str);

	for (i = 0; i < PHOEBE_command_list.command_no; i++)
		{
		/* This loop will go through all scripter commands and try to find a mat- */
		/* ch. If it fails, the scripter command supplied does not exist and the  */
		/* warning should be displayed.                                           */
		
		if (strcmp (readout_str, PHOEBE_command_list.command[i].description) == 0)
			{
			/* First we need to show/hide the appropriate widgets; the typedeffed   */
			/* struct already carries information on what should be displayed, so   */
			/* here we hide everything that's shown and show only the predetermined */
			/* widgets.                                                             */
			for (j = 0; j < 4; j++)
				{
				readout_widget = lookup_widget (PHOEBE_scripter, labels[j]);
				if (GTK_WIDGET_VISIBLE (readout_widget)) gtk_widget_hide (readout_widget);
				readout_widget = lookup_widget (PHOEBE_scripter, entries[j]);
				gtk_entry_set_text (GTK_ENTRY (readout_widget), "");
				if (GTK_WIDGET_VISIBLE (readout_widget)) gtk_widget_hide (readout_widget);
				}
			for (j = 0; j < PHOEBE_command_list.command[i].parno; j++)
				gtk_widget_show (PHOEBE_command_list.command[i].widget[j]);

			/* Next we need to change the labels:                                   */
			for (j = 0; j < PHOEBE_command_list.command[i].parno; j++)
				{
				readout_widget = lookup_widget (PHOEBE_scripter, labels[j]);
				gtk_label_set_text (GTK_LABEL (readout_widget), PHOEBE_command_list.command[i].label[j]);
				gtk_widget_show (readout_widget);
				}
			}
		}
	}

void on_open_script_clicked (GtkButton *button, gpointer user_data)
	{
	char *readout_str = gtk_file_selection_get_filename (GTK_FILE_SELECTION (PHOEBE_file_selector));
	GtkWidget *notice_window;

	if (everything_ok_with_the_filename (readout_str))
		{
		open_script (readout_str);
		gtk_signal_disconnect_by_func (GTK_OBJECT (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button")), GTK_SIGNAL_FUNC (on_open_script_clicked), NULL);
		gtk_widget_hide (PHOEBE_file_selector);
		}
	else
		notice_window = create_notice_window (
			"Notice",
			"Filename problem",
		  "The filename you have selected has some problems,",
			"I cannot complete the process. Please choose different filename.",
			gtk_widget_destroy);
	}

void on_save_script_clicked (GtkButton *button, gpointer user_data)
	{
	char *readout_str = gtk_file_selection_get_filename (GTK_FILE_SELECTION (PHOEBE_file_selector));
	GtkWidget *notice_window;

	if (everything_ok_with_the_filename (readout_str))
		{
		save_script (readout_str);
		gtk_signal_disconnect_by_func (GTK_OBJECT (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button")), GTK_SIGNAL_FUNC (on_save_script_clicked), NULL);
		gtk_widget_hide (PHOEBE_file_selector);
		}
	else
		notice_window = create_notice_window (
			"Notice",
			"Filename problem",
		  "The filename you have selected has some problems,",
			"I cannot complete the process. Please choose different filename.",
			gtk_widget_destroy);
	}

void on_scripter_open_script_button_clicked (GtkButton *button, gpointer user_data)
	{
	/* We shall use PHOEBE's generic file selector window to prompt for data:   */
	gtk_window_set_title (GTK_WINDOW (PHOEBE_file_selector), "Open PHOEBE Script");
	gtk_label_set_text (GTK_LABEL (GTK_BIN (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button"))->child), "Open");
  gtk_signal_connect (GTK_OBJECT (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button")), "clicked", GTK_SIGNAL_FUNC (on_open_script_clicked), NULL);
	gtk_widget_show (PHOEBE_file_selector);
	}

void on_scripter_save_script_button_clicked (GtkButton *button, gpointer user_data)
	{
	/* We shall use PHOEBE's generic file selector window to prompt for data:   */
	gtk_window_set_title (GTK_WINDOW (PHOEBE_file_selector), "Save PHOEBE Script");
	gtk_label_set_text (GTK_LABEL (GTK_BIN (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button"))->child), "Save");
  gtk_signal_connect (GTK_OBJECT (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button")), "clicked", GTK_SIGNAL_FUNC (on_save_script_clicked), NULL);
	gtk_widget_show (PHOEBE_file_selector);
	}

void on_file_selector_cancel_button_clicked (GtkButton *button, gpointer user_data)
	{
	/* This function is connected to file selector's cancel and delete buttons. */
	/* Its purpose is to clear all signals connected to file selector buttons   */
	/* in case the user cancels any operation involving the file selector.      */

  gtk_signal_disconnect_by_data (GTK_OBJECT (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button")), NULL);
	gtk_widget_hide (PHOEBE_file_selector);
	}

void on_data_sheet_print_to_file_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	char *filename_str = gtk_file_selection_get_filename (GTK_FILE_SELECTION (PHOEBE_file_selector));
	GtkWidget *notice_window;

	if (everything_ok_with_the_filename (filename_str))
		{
		save_data_sheet_parameters_to_file (filename_str);
	  gtk_signal_disconnect_by_data (GTK_OBJECT (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button")), NULL);
		gtk_widget_hide (PHOEBE_file_selector);
		}
	else
		notice_window = create_notice_window (
			"Notice",
			"Filename problem",
		  "The filename you have selected has some problems,",
			"I cannot complete the process. Please choose different filename.",
			gtk_widget_destroy);
	}

void on_data_sheet_print_to_file_button_clicked (GtkButton *button, gpointer user_data)
	{
	/* We shall use PHOEBE's generic file selector window to prompt for data:   */
	gtk_window_set_title (GTK_WINDOW (PHOEBE_file_selector), "Save Data Sheet to File");
	gtk_label_set_text (GTK_LABEL (GTK_BIN (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button"))->child), "Save");
  gtk_signal_connect (GTK_OBJECT (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button")), "clicked", GTK_SIGNAL_FUNC (on_data_sheet_print_to_file_ok_button_clicked), NULL);
	gtk_widget_show (PHOEBE_file_selector);
	}

void on_menu_bar_file_import_from_fotel_activate (GtkMenuItem *menuitem, gpointer user_data)
	{
	gtk_widget_show (PHOEBE_import_from_fotel);
	}

void on_import_from_fotel_browse_clicked (GtkButton *button, gpointer user_data)
	{
	gtk_window_set_title (GTK_WINDOW (PHOEBE_file_selector), "Select FOTEL data file");
	gtk_label_set_text (GTK_LABEL (GTK_BIN (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button"))->child), "Import");
	gtk_signal_connect (GTK_OBJECT (lookup_widget (PHOEBE_file_selector, "file_selector_ok_button")), "clicked", GTK_SIGNAL_FUNC (on_import_from_fotel_file_selector_ok_button_clicked), NULL);
	gtk_widget_show (PHOEBE_file_selector);
	}

void on_import_from_fotel_file_selector_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	char *filename_str = gtk_file_selection_get_filename (GTK_FILE_SELECTION (PHOEBE_file_selector));
	gtk_entry_set_text (GTK_ENTRY (lookup_widget (PHOEBE_import_from_fotel, "import_from_fotel_filename")), filename_str);
	gtk_widget_hide (PHOEBE_file_selector);
	}

void on_import_from_fotel_ok_button_clicked (GtkButton *button, gpointer user_data)
	{
	char *input_file = gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE_import_from_fotel, "import_from_fotel_filename")));
	char *prefix     = gtk_entry_get_text (GTK_ENTRY (lookup_widget (PHOEBE_import_from_fotel, "import_from_fotel_prefix")));

	import_from_fotel (input_file, prefix);
	print_to_status_bar ("FOTEL data file imported.");

	gtk_widget_hide (PHOEBE_import_from_fotel);
	}

void on_critical_phases_changed (GtkEditable *editable, gpointer user_data)
	{
	double omega, e, pshift;
	double phiper, phiconj, phiinf, phiasc, phidesc;
	char value[255];

	omega  = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "orbit_perr0_value")));
	e      = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "orbit_e_value")));
	pshift = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "system_pshift_value")));

	if (fabs (e) < 1e-6) {
		phiper = 0.0;
		phiconj = 0.0;
	}
	else {
		calculate_critical_phases (omega, e, pshift, &phiper, &phiconj, &phiinf, &phiasc, &phidesc);
	}

	sprintf (value, "%5.5lf", phiper);
	gtk_label_set_text (GTK_LABEL (lookup_widget (PHOEBE, "orbit_periastron_phase")), value);

	sprintf (value, "%5.5lf", phiconj);
	gtk_label_set_text (GTK_LABEL (lookup_widget (PHOEBE, "orbit_superior_conjunction_phase")), value);

	sprintf (value, "%5.5lf", phiinf);
	gtk_label_set_text (GTK_LABEL (lookup_widget (PHOEBE, "orbit_inferior_conjunction_phase")), value);

	sprintf (value, "%5.5lf", phiasc);
	gtk_label_set_text (GTK_LABEL (lookup_widget (PHOEBE, "orbit_ascending_node_phase")), value);

	sprintf (value, "%5.5lf", phidesc);
	gtk_label_set_text (GTK_LABEL (lookup_widget (PHOEBE, "orbit_descending_node_phase")), value);
	}
