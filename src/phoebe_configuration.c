#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <unistd.h>

#include "phoebe_global.h"
#include "phoebe_gui_accessories.h"
#include "phoebe_gui_support.h"

void configuration_save_file (GtkWidget *widget, gpointer user_data)
	{
	GtkWidget *readout_widget;
	GtkWidget *notice_window;

	char working_string[255];
	char *working_str = working_string;

	char *readout_str;

	FILE *CONFIG_FILE;

	CONFIG_FILE = fopen (PHOEBE_CONFIG, "w");

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_base_directory");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	fprintf (CONFIG_FILE, "PHOEBE_BASE_DIR                  %s\n", readout_str);
	sprintf (PHOEBE_BASE_DIR, "%s", readout_str);

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_source_directory");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	fprintf (CONFIG_FILE, "PHOEBE_SOURCE_DIR                %s\n", readout_str);
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
		fclose (CONFIG_FILE);
		return;
		}
	fprintf (CONFIG_FILE, "PHOEBE_DEFAULTS_DIR              %s\n", readout_str);

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
		fclose (CONFIG_FILE);
		return;
		}
	fprintf (CONFIG_FILE, "PHOEBE_TEMP_DIR                  %s\n", readout_str);

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_data_directory");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	sprintf (PHOEBE_DATA_DIR, "%s", readout_str);
	if (access (PHOEBE_DATA_DIR, W_OK) == -1)
		{
		notice_window = create_notice_window (
			"PHOEBE notice",
			"PHOEBE Data directory selection issue",
			"The directory you have currently chosen to contain data files doesn't have",
			"write priviliges. Please change permissions or choose another directory.",
			gtk_widget_destroy);
		fclose (CONFIG_FILE);
		return;
		}
	fprintf (CONFIG_FILE, "PHOEBE_DATA_DIR                  %s\n", readout_str);

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
		fclose (CONFIG_FILE);
		return;
		}
	fprintf (CONFIG_FILE, "PHOEBE_LC_DIR                    %s\n", readout_str);

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
		fclose (CONFIG_FILE);
		return;
		}
	fprintf (CONFIG_FILE, "PHOEBE_DC_DIR                    %s\n", readout_str);

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_flux_files_directory");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	fprintf (CONFIG_FILE, "PHOEBE_FF_DIR                    %s\n", readout_str);
	sprintf (PHOEBE_FF_DIR, "%s", readout_str);

	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_sm_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		{
		fprintf (CONFIG_FILE, "PHOEBE_PLOTTING_PACKAGE          sm\n");
		sprintf (PHOEBE_PLOTTING_PACKAGE, "sm");
		}
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_gnuplot_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		{
		fprintf (CONFIG_FILE, "PHOEBE_PLOTTING_PACKAGE          gnuplot\n");
		sprintf (PHOEBE_PLOTTING_PACKAGE, "gnuplot");
		}
	readout_widget = lookup_widget (GTK_WIDGET (PHOEBE_configuration), "configuration_pgplot_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		{
		fprintf (CONFIG_FILE, "PHOEBE_PLOTTING_PACKAGE          pgplot\n");
		sprintf (PHOEBE_PLOTTING_PACKAGE, "pgplot");
		}

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_ld_switch");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		{
		fprintf (CONFIG_FILE, "PHOEBE_LD_SWITCH                 1\n");
		PHOEBE_LD_SWITCH = 1;
		}
	else
		{
		fprintf (CONFIG_FILE, "PHOEBE_LD_SWITCH                 0\n");
		PHOEBE_LD_SWITCH = 0;
		}

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
		fclose (CONFIG_FILE);
		return;
		}
	fprintf (CONFIG_FILE, "PHOEBE_LD_DIR                    %s\n", readout_str);

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_3d_plot_callback_option");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		{
		fprintf (CONFIG_FILE, "PHOEBE_3D_PLOT_CALLBACK_OPTION   1\n");
		PHOEBE_3D_PLOT_CALLBACK_OPTION = 1;
		}
	else
		{
		fprintf (CONFIG_FILE, "PHOEBE_3D_PLOT_CALLBACK_OPTION   0\n");
		PHOEBE_3D_PLOT_CALLBACK_OPTION = 0;
		}

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_confirm_on_save");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		{
		fprintf (CONFIG_FILE, "PHOEBE_CONFIRM_ON_SAVE           1\n");
		PHOEBE_CONFIRM_ON_SAVE = 1;
		}
	else
		{
		fprintf (CONFIG_FILE, "PHOEBE_CONFIRM_ON_SAVE           0\n");
		PHOEBE_CONFIRM_ON_SAVE = 0;
		}

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_confirm_on_quit");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		{
		fprintf (CONFIG_FILE, "PHOEBE_CONFIRM_ON_QUIT           1\n");
		PHOEBE_CONFIRM_ON_QUIT = 1;
		}
	else
		{
		fprintf (CONFIG_FILE, "PHOEBE_CONFIRM_ON_QUIT           0\n");
		PHOEBE_CONFIRM_ON_QUIT = 0;
		}

	readout_widget = lookup_widget (PHOEBE_configuration, "configuration_warn_on_synthetic_scatter");
	if (GTK_TOGGLE_BUTTON (readout_widget)->active == TRUE)
		{
		fprintf (CONFIG_FILE, "PHOEBE_WARN_ON_SYNTHETIC_SCATTER 1\n");
		PHOEBE_CONFIRM_ON_QUIT = 1;
		}
	else
		{
		fprintf (CONFIG_FILE, "PHOEBE_WARN_ON_SYNTHETIC_SCATTER 0\n");
		PHOEBE_CONFIRM_ON_QUIT = 0;
		}

	fclose (CONFIG_FILE);

	/* Put the devices into the Plot-to-File window:                            */
	create_plot_to_file_drop_down_menu ();

	print_to_status_bar ("PHOEBE Configuration File Saved...");

	gtk_widget_hide (PHOEBE_configuration);
	}
