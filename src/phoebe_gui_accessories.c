#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <errno.h>
#include <unistd.h>

#include "config.h"

#include "phoebe_error_handling.h"
#include "phoebe_global.h"
#include "phoebe_gui.h"
#include "phoebe_gui_accessories.h"
#include "phoebe_gui_callbacks.h"
#include "phoebe_gui_support.h"
#include "phoebe_scripting.h"

void parse_startup_line (int argc, char *argv[])
{
	/*
	 * This function parses the command line and looks for known switches; it
	 * doesn't really do anything with them, it just writes what it found to
	 * the PHOEBE_args variable that is supposed to be used for real actions.
	 */

	int i;

	for (i = 1; i < argc; i++) {
		if ( (strcmp (argv[i],  "-h"   ) == 0) ||
		     (strcmp (argv[i],  "-?"   ) == 0) ||
			 (strcmp (argv[i], "--help") == 0) ) {
			printf ("\nPHOEBE 0.29c command line arguments: [-hsv] [keyword_file]\n\n");
			printf ("  -h, --help, -?      ..  this help screen\n");
			printf ("  -s, --script        ..  execute PHOEBE script\n");
			printf ("  -v, --version       ..  display PHOEBE version and exit\n");
			printf ("\n");
			exit (0);
		}

		if ( (strcmp (argv[i],  "-v"      ) == 0) ||
				 (strcmp (argv[i], "--version") == 0) ) {
			printf ("\nPHOEBE 0.29c (stable release), July 4, 2006 by Andrej Prsa\n");
			printf ("  Send comments and/or requests to phoebe-discuss@list.fmf.uni-lj.si\n\n");
			exit (0);
		}

		if ( (strcmp (argv[i],  "-s"     ) == 0) ||
				 (strcmp (argv[i], "--script") == 0) ) {
			/*
			 * We cannot start the script from here because the widgets aren't
			 * initialized yet; thus we just initialize the proper switches:           
			 */

			if (i+1 >= argc) {
				printf ("\nPHOEBE 0.29c command line arguments: [-hsv] [keyword_file]\n\n");
				printf ("  -h, --help, -?      ..  this help screen\n");
				printf ("  -s, --script        ..  execute PHOEBE script\n");
				printf ("  -v, --version       ..  display PHOEBE version and exit\n");
				printf ("\n");
				printf ("PHOEBE error: please provide a script name to the -s switch.\n\n");
				exit (0);
			}

			PHOEBE_EXECUTE_SCRIPT = 1;
			sprintf (PHOEBE_EXECUTE_SCRIPT_NAME, "%s", argv[i+1]);
			i++;
			/* If this was the last switch, break the loop. */
			if (i >= argc) break; else continue;
		}

		if ( argv[i][0] != '-' )
			{
			/* This means that the command line argument doesn't contain '-'; thus  */
			/* it should be a keyword file. All other arguments to - and -- swit-   */
			/* ches (without -/--) are read in before and they should never evalua- */
			/* te here.                                                             */

			PHOEBE_args.KEYWORD_SWITCH = 1;
			sprintf (PHOEBE_args.KEYWORD, "%s", argv[i]);
			}
		}
	}

void phoebe_init ()
	{
	GtkWidget *warning_window = NULL;

	GtkWidget *readout_widget;

	char working_string[255];
	char *working_str = working_string;

	char keyword_string[255];
	char *keyword_str = keyword_string;

	/* This is a read-in string used by getline():                            */
	char *delimeter_str = NULL;

	/* Two strings to create symbolic links to atmcof*.dat:                   */
	char source_string[255], dest_string[255];
	char *source_str = source_string, *dest_str = dest_string;

	FILE *config_file;

	/* First thing: set all numbers to conform to ISO "C" locale:             */
	PHOEBE_LOCALE = strdup (setlocale (LC_NUMERIC, NULL));
	setlocale (LC_NUMERIC, "C");

	sprintf (PHOEBE_VERSION_NUMBER, "0.29c (stable release)");
	sprintf (PHOEBE_VERSION_DATE,   "July 4, 2006");

	sprintf (PHOEBE_KEYWORD_FILENAME, "Undefined");

	LC_ZOOM_FACTOR = 0.0;
	LC_X_OFFSET    = 0.0;
	LC_Y_OFFSET    = 0.0;

	RV_ZOOM_FACTOR = 0.0;
	RV_X_OFFSET    = 0.0;
	RV_Y_OFFSET    = 0.0;
	
	PHOEBE_lc_data = NULL;
	PHOEBE_rv_data = NULL;

	/* Assign a current directory (i.e. the directory from which PHOEBE was     */
	/* started to PHOEBE_STARTUP_DIR; this is used for resolving relative       */
	/* pathnames.                                                               */
	getcwd (working_str, 255);
	sprintf (PHOEBE_STARTUP_DIR, "%s", working_str);

	/* Assign a .phoebe configuration path to the PHOEBE_CONFIG variable:       */
	if (getenv ("HOME") == NULL)
		{
		warning_window = create_notice_window (
			"Environment entry not found",
			"Environment entry $HOME missing",
			"PHOEBE cannot find the environment entry HOME. Please set it to your",
			"home directory (e.g. set HOME=/home/your_name) and restart PHOEBE.",
			gtk_main_quit);
		}

	sprintf (USER_HOME_DIR, "%s", getenv ("HOME"));
	sprintf (PHOEBE_HOME_DIR, "%s/.phoebe", USER_HOME_DIR);
	sprintf (PHOEBE_CONFIG, "%s/phoebe.config", PHOEBE_HOME_DIR);

	/* Read out the configuration from the config file. Do not fill in the con- */
	/* figuration window widgets from here, because it wouldn't work for tempo- */
	/* rary configurations. Rather use on_menu_bar_settings_configure_clicked() */
	/* callback.                                                                */
	if (file_exists (PHOEBE_CONFIG))
		{
		config_file = fopen (PHOEBE_CONFIG, "r");
		while (!feof (config_file))
			{
			/* The following line reads the line from the input file and checks if  */
			/* everything went OK; if en error occured (e.g. EoF reached), it bre-  */
			/* aks the loop.                                                        */
			if (fgets (keyword_str, 254, config_file) == NULL) break;

			if (strstr (keyword_str, "PHOEBE_BASE_DIR") != NULL)
				{
				if (sscanf (keyword_str, "PHOEBE_BASE_DIR %s", working_str) != 1) sprintf (PHOEBE_BASE_DIR, "");
				else sprintf (PHOEBE_BASE_DIR, "%s", working_str);
				}
			if (strstr (keyword_str, "PHOEBE_SOURCE_DIR") != NULL)
				{
				if (sscanf (keyword_str, "PHOEBE_SOURCE_DIR %s", working_str) != 1) sprintf (PHOEBE_SOURCE_DIR, "");
				else sprintf (PHOEBE_SOURCE_DIR, "%s", working_str);
				}
			if (strstr (keyword_str, "PHOEBE_DEFAULTS_DIR") != NULL)
				{
				if (sscanf (keyword_str, "PHOEBE_DEFAULTS_DIR %s", working_str) != 1) sprintf (PHOEBE_DEFAULTS_DIR, "");
				else sprintf (PHOEBE_DEFAULTS_DIR, "%s", working_str);
				}
			if (strstr (keyword_str, "PHOEBE_TEMP_DIR") != NULL)
				{
				if (sscanf (keyword_str, "PHOEBE_TEMP_DIR %s", working_str) != 1) sprintf (PHOEBE_TEMP_DIR, "");
				else sprintf (PHOEBE_TEMP_DIR, "%s", working_str);
				}
			if (strstr (keyword_str, "PHOEBE_DATA_DIR") != NULL)
				{
				if (sscanf (keyword_str, "PHOEBE_DATA_DIR %s", working_str) != 1) sprintf (PHOEBE_DATA_DIR, "");
				else sprintf (PHOEBE_DATA_DIR, "%s", working_str);
				}
			if (strstr (keyword_str, "PHOEBE_LC_DIR") != NULL)
				{
				if (sscanf (keyword_str, "PHOEBE_LC_DIR %s", working_str) != 1) sprintf (PHOEBE_LC_DIR, "");
				else sprintf (PHOEBE_LC_DIR, "%s", working_str);
				}
			if (strstr (keyword_str, "PHOEBE_DC_DIR") != NULL)
				{
				if (sscanf (keyword_str, "PHOEBE_DC_DIR %s", working_str) != 1) sprintf (PHOEBE_DC_DIR, "");
				else sprintf (PHOEBE_DC_DIR, "%s", working_str);
				}
			if (strstr (keyword_str, "PHOEBE_FF_DIR") != NULL)
				{
				if (sscanf (keyword_str, "PHOEBE_FF_DIR %s", working_str) != 1) sprintf (PHOEBE_FF_DIR, "");
				else sprintf (PHOEBE_FF_DIR, "%s", working_str);
				}
			if (strstr (keyword_str, "PHOEBE_PLOTTING_PACKAGE") != NULL)
				{
				if (sscanf (keyword_str, "PHOEBE_PLOTTING_PACKAGE %s", working_str) != 1) sprintf (PHOEBE_PLOTTING_PACKAGE, "");
				else sprintf (PHOEBE_PLOTTING_PACKAGE, "%s", working_str);
				}
			if (strstr (keyword_str, "PHOEBE_LD_SWITCH") != NULL)
				if (sscanf (keyword_str, "PHOEBE_LD_SWITCH %d", &PHOEBE_LD_SWITCH) != 1) PHOEBE_LD_SWITCH = 0;
			if (strstr (keyword_str, "PHOEBE_LD_DIR") != NULL)
				{
				if (sscanf (keyword_str, "PHOEBE_LD_DIR %s", working_str) != 1) sprintf (PHOEBE_LD_DIR, "");
				else sprintf (PHOEBE_LD_DIR, "%s", working_str);
				}
			if (strstr (keyword_str, "PHOEBE_3D_PLOT_CALLBACK_OPTION") != NULL)
				if (sscanf (keyword_str, "PHOEBE_3D_PLOT_CALLBACK_OPTION %d", &PHOEBE_3D_PLOT_CALLBACK_OPTION) != 1) PHOEBE_3D_PLOT_CALLBACK_OPTION = 0;
			if (strstr (keyword_str, "PHOEBE_CONFIRM_ON_SAVE") != NULL)
				if (sscanf (keyword_str, "PHOEBE_CONFIRM_ON_SAVE %d", &PHOEBE_CONFIRM_ON_SAVE) != 1) PHOEBE_CONFIRM_ON_SAVE = 1;
			if (strstr (keyword_str, "PHOEBE_CONFIRM_ON_QUIT") != NULL)
				if (sscanf (keyword_str, "PHOEBE_CONFIRM_ON_QUIT %d", &PHOEBE_CONFIRM_ON_QUIT) != 1) PHOEBE_CONFIRM_ON_QUIT = 1;
			if (strstr (keyword_str, "PHOEBE_WARN_ON_SYNTHETIC_SCATTER") != NULL)
				if (sscanf (keyword_str, "PHOEBE_WARN_ON_SYNTHETIC_SCATTER %d", &PHOEBE_WARN_ON_SYNTHETIC_SCATTER) != 1) PHOEBE_WARN_ON_SYNTHETIC_SCATTER = 1;
			}
		fclose (config_file);
		}

	if (!file_exists (PHOEBE_CONFIG)) /* Config file is missing */
		{
		warning_window = create_warning_window (
			"PHOEBE Configuration File Missing",
			"Welcome to PHOEBE!",
			"Since there is no configuration file, I guess this is the first time you started PHOEBE.",
			"I am about to create a hidden PHOEBE configuration directory in your home directory. Is that OK?",
			on_warning_no_configuration_ok_button_clicked,
			gtk_main_quit);

		sprintf (PHOEBE_BASE_DIR, "/usr/local/share/phoebe");
		sprintf (PHOEBE_SOURCE_DIR, "/usr/local/share/phoebe/src");
		sprintf (PHOEBE_DEFAULTS_DIR, "/usr/local/share/phoebe/defaults");
		sprintf (PHOEBE_TEMP_DIR, "/tmp");
		sprintf (PHOEBE_DATA_DIR, "%s/data", PHOEBE_BASE_DIR);
		sprintf (PHOEBE_LC_DIR, "/usr/local/share/phoebe/wd");
		sprintf (PHOEBE_DC_DIR, "/usr/local/share/phoebe/wd");
		sprintf (PHOEBE_FF_DIR, "/usr/local/share/phoebe/flux_files");
		sprintf (PHOEBE_PLOTTING_PACKAGE, "gnuplot");
		         PHOEBE_LD_SWITCH = 0;
             PHOEBE_3D_PLOT_CALLBACK_OPTION = 0;
             PHOEBE_CONFIRM_ON_SAVE = 1;
             PHOEBE_CONFIRM_ON_QUIT = 1;
             PHOEBE_WARN_ON_SYNTHETIC_SCATTER = 1;
		}

	/* We now set the pixmaps directories. These directories contain all PHOEBE */
	/* related pixmaps and they should be initialized through a config file. If */
	/* that file is missing, we try to set the pixmaps directories relatively.  */

	/* Pixmaps (empty LC/RV/Chi2 plots, logos, ...):                            */
	sprintf (working_str, "%s/pixmaps/", PHOEBE_BASE_DIR);
	add_pixmap_directory (working_str);

	/* Temporary directory:                                                     */
	sprintf (working_str, "%s/", PHOEBE_TEMP_DIR);
	add_pixmap_directory (working_str);

	if (!file_exists (PHOEBE_CONFIG))
		{
		/* This occurs when PHOEBE is started for the first time from src:        */

		/* Pixmaps (empty LC/RV/Chi2 plots, logos, ...):                            */
		add_pixmap_directory ("../pixmaps/");

		/* Temporary directory:                                                     */
		add_pixmap_directory (PHOEBE_TEMP_DIR);
		}

	PHOEBE = create_PHOEBE ();
	gtk_widget_show (PHOEBE);

	/* If warning window is created, be sure it's on top of main PHOEBE window: */
	if (GTK_IS_WINDOW (warning_window))
		{
		gtk_object_set_data (GTK_OBJECT (PHOEBE), "warning_window", warning_window);
		gdk_window_raise (warning_window->window);
		}

	if (file_exists (PHOEBE_CONFIG)) chdir (PHOEBE_DATA_DIR);
	PHOEBE_open_keyword_file     = create_PHOEBE_open_keyword_file ();
	PHOEBE_plot_to_file_selector = create_PHOEBE_plot_to_file_selector ();
	PHOEBE_open_data_file        = create_PHOEBE_open_data_file ();
	PHOEBE_file_selector         = create_PHOEBE_file_selector ();

	if (file_exists (PHOEBE_CONFIG)) chdir (PHOEBE_BASE_DIR);

	PHOEBE_calculate_grid        = create_PHOEBE_calculate_grid ();
	PHOEBE_calculate_grid_edit_parameters
	                             = create_PHOEBE_calculate_grid_edit_parameters ();

	PHOEBE_calculate_phsv        = create_PHOEBE_calculate_phsv ();
	PHOEBE_calculate_pcsv        = create_PHOEBE_calculate_pcsv ();

	PHOEBE_plot_lc               = create_PHOEBE_plot_lc ();
	PHOEBE_plot_rv               = create_PHOEBE_plot_rv ();
	PHOEBE_plot_to_file          = create_PHOEBE_plot_to_file ();
	PHOEBE_ld_interpolation      = create_PHOEBE_ld_interpolation ();
	PHOEBE_dc                    = create_PHOEBE_dc ();
	PHOEBE_dc_correlation_matrix = create_PHOEBE_dc_correlation_matrix ();
	PHOEBE_fitting_quickbar      = create_PHOEBE_fitting_quickbar ();

	PHOEBE_filter_menu           = create_PHOEBE_filter_menu ();
	PHOEBE_assign_data_file      = create_PHOEBE_assign_data_file ();
	PHOEBE_assign_rv_data_file   = create_PHOEBE_assign_rv_data_file ();
	PHOEBE_assign_el3            = create_PHOEBE_assign_el3 ();
	PHOEBE_assign_lc_luminosity  = create_PHOEBE_assign_lc_luminosity ();
	PHOEBE_assign_ld_monochromatic_lc
                               = create_PHOEBE_assign_ld_monochromatic_lc ();
	PHOEBE_assign_ld_monochromatic_rv
                               = create_PHOEBE_assign_ld_monochromatic_rv ();
	PHOEBE_assign_primary_spots  = create_PHOEBE_assign_primary_spots ();
	PHOEBE_assign_secondary_spots
	                             = create_PHOEBE_assign_secondary_spots ();
	PHOEBE_assign_weighting      = create_PHOEBE_assign_weighting ();
	PHOEBE_scripter              = create_PHOEBE_scripter ();
	PHOEBE_data_sheet            = create_PHOEBE_data_sheet ();

	PHOEBE_import_from_fotel     = create_PHOEBE_import_from_fotel ();

	/* GLADE has problems defining clist justifications, so we do it manually:  */
	set_clist_justifications ();

	if (file_exists (PHOEBE_CONFIG)) chdir (PHOEBE_BASE_DIR);
	PHOEBE_configuration        = create_PHOEBE_configuration ();
	PHOEBE_configuration_browse = create_PHOEBE_configuration_browse ();

	/* If LD interpolation switch is set on, set the interpolation button sen-  */
	/* sitive:                                                                  */
	readout_widget = lookup_widget (PHOEBE, "ld_vanhamme_interpolation");
	if (PHOEBE_LD_SWITCH == 0) gtk_widget_set_sensitive (readout_widget, FALSE);
	if (PHOEBE_LD_SWITCH == 1) gtk_widget_set_sensitive (readout_widget, TRUE);

	/* Create About window and change the version label to contain information  */
	/* given in PHOEBE_VERSION_NUMBER and PHOEBE_VERSION_DATE:                  */
	PHOEBE_about = create_PHOEBE_about ();
	readout_widget = lookup_widget (PHOEBE_about, "about_version_label");
	sprintf (working_str, "Version %s       %s", PHOEBE_VERSION_NUMBER, PHOEBE_VERSION_DATE);
	gtk_label_set_text (GTK_LABEL (readout_widget), working_str);

	/* Turn on all scripter commands:                                           */
	PHOEBE_command_list.command_no = 0;
	PHOEBE_command_list.command = NULL;
	define_scripter_commands ();
	populate_scripter_command_list ();

	/* Put the devices into the Plot-to-File window:                            */
	create_plot_to_file_drop_down_menu ();

	/* Finally, we have to set a working directory; this will be the temporary  */
	/* directory, where the user has to have full access to:                    */
	if (access (PHOEBE_TEMP_DIR, W_OK) == -1)
		{
		warning_window = create_notice_window (
			"PHOEBE warning",
			"PHOEBE temporary directory selection issue",
			"The directory you have currently chosen to be temporary (storage for temporary files)",
			"doesn't allow you to write to it. Please change permissions or choose another directory.",
			gtk_widget_destroy);
		}
	else chdir (PHOEBE_TEMP_DIR);

	/* Open the default values:                                                 */
	sprintf (PHOEBE_DEFAULTS, "%s/default.phoebe", PHOEBE_DEFAULTS_DIR);
	if (file_exists (PHOEBE_DEFAULTS))
		open_keyword_file (PHOEBE_DEFAULTS);

	/* Check whether temporary directory contains links to atmcof.dat and atm-  */
	/* cofplanck.dat:                                                           */
	sprintf (dest_str,   "%s/atmcof.dat", PHOEBE_TEMP_DIR);
	sprintf (source_str, "%s/atmcof.dat", PHOEBE_LC_DIR);
	if (file_exists (source_str))
		{
		if (!file_exists (dest_str))
			symlink (source_str, dest_str);
		}
	else
		phoebe_warning ("file atmcof.dat not found!\n");

	sprintf (dest_str,   "%s/phoebe_atmcofplanck.dat", PHOEBE_TEMP_DIR);
	sprintf (source_str, "%s/phoebe_atmcofplanck.dat", PHOEBE_LC_DIR);
	if (file_exists (source_str))
		{
		if (!file_exists (dest_str))
			symlink (source_str, dest_str);
		}
	else
		phoebe_warning ("file phoebe_atmcofplanck.dat not found!\n");

	/* Finally, set the window title to a generic form:                       */
	sprintf (working_str, "PHOEBE %s", PHOEBE_VERSION_NUMBER);
	gtk_window_set_title (GTK_WINDOW (PHOEBE), working_str);

	print_to_status_bar ("PHOEBE Started...");

	/* If the command line contains the keyword file, try to open it:           */
	if (PHOEBE_args.KEYWORD_SWITCH == 1)
		{
		/* We have to make a distinction between absolute and relative filenames: */
		if (PHOEBE_args.KEYWORD[0] == '/')
			sprintf (working_str, "%s", PHOEBE_args.KEYWORD);
		else
			sprintf (working_str, "%s/%s", PHOEBE_STARTUP_DIR, PHOEBE_args.KEYWORD);
		if (file_exists (working_str))
			{
			open_keyword_file (working_str);
			on_data_lc_filter_changed ();
			on_data_rv_filter_changed ();
			add_filters_to_available_filter_lists ();
			print_to_status_bar ("Keyword file opened.");
			}
		else
			warning_window = create_notice_window (
				"PHOEBE warning",
				"PHOEBE keyword file not found",
				"The filename you have supplied for your keyword file cannot be found.",
				"Please open a valid file through File->Open selection.",
				gtk_widget_destroy);
		}

	/* If SuperMongo libraries are missing, disable the SM selection widget:    */
	#ifndef HAVE_LIBDEVICES
	gtk_widget_set_sensitive (lookup_widget (PHOEBE_configuration, "configuration_sm_switch"), FALSE);
	#endif

	/* If GnuPlot is missing, disable the corresponding selection widget:     */
	#ifndef PHOEBE_GNUPLOT_SUPPORT
	gtk_widget_set_sensitive (lookup_widget (PHOEBE_configuration, "configuration_gnuplot_switch"), FALSE);
	#endif

	/* If the script is run non-interactively, run it:                          */
	if (PHOEBE_EXECUTE_SCRIPT == 1)
		{
		/* We have to make a distinction between absolute and relative filenames: */
		if (PHOEBE_EXECUTE_SCRIPT_NAME[0] == '/')
			sprintf (working_str, "%s", PHOEBE_EXECUTE_SCRIPT_NAME);
		else
			sprintf (working_str, "%s/%s", PHOEBE_STARTUP_DIR, PHOEBE_EXECUTE_SCRIPT_NAME);
		if (file_exists (working_str))
			{
			open_script (working_str);
			on_scripter_execute_script_button_clicked (NULL, NULL);
			}
		else
			phoebe_fatal ("The script you want to execute does not seem to exist.");
		}
	}

int file_exists (char *file_name)
	{
	/* This function checks whether a file exists; if it does, it returns 1; if */
	/* not, it returns 0. Thus we use it like this:                             */
  /*                                                                          */
	/*   if (file_exists ("some_file"))  or  if (! file_exists ("some_file"))   */
  /*                                                                          */
	int return_value = 1;

	FILE *test_file = fopen (file_name, "r");
	
	if (test_file != NULL) fclose (test_file);
		else return_value = 0;

	return return_value;
	}

int everything_ok_with_the_filename (char *file_name)
	{
	/* This function is called whenever a filename is given by the user; here   */
	/* the file is checked for access privilidges and proper contruction.       */

/* FIX ME !!! */

	return 1;
	}

void strip_string_tail (char *in)
	{
	if (!in) return;
	if (!(*in)) return;
	in[strlen(in)-1] = '\0';
	return;
	}

int parse_input_data (char **in)
{
	/*
	 * This function filters out all commented parts and undesired spaces
	 * from the passed string and returns it clean. If it returns non-zero,
	 * it means that the line contains no useful data and that the caller
	 * function should disregard it.                                           
	 */

	char *copy = strdup (*in);
	char *ptr;

	/* Free the original string: */
	free (*in);

	/* If the line contains the comment delimeter '#', discard everything     */
	/* that follows it (strip the rest of the line):                          */
	if ( (ptr = strchr (copy, '#')) ) *ptr = '\0';

	/* Remove any newline characters (*nix AND DOS/Windows): */
	if ( (ptr = strchr (copy, '\n')) ) *ptr = '\0';
	if ( (ptr = strchr (copy, 13))   ) *ptr = '\0';

	/* If we have spaces in front of the first character in line, remove      */
	/* them by incrementing the pointer by 1:                                 */
	ptr = copy;
	while (*ptr == ' ' || *ptr == '\t') {
		ptr++;
	}

	/* If the file we read out is an empty line, return non-zero:               */
	if ( *ptr == '\0' ) {
		*in = NULL;
		free (copy);
		return -1;
	}
	else {
		*in = strdup (ptr);
		free (copy);
		return 0;
	}
}

void print_to_status_bar (char *text)
	{
	GtkWidget *status_bar = lookup_widget (PHOEBE, "status_bar");

	char outtext_string[255];
	char *outtext_str = outtext_string;

	sprintf (outtext_str, " %s", text);
	gtk_statusbar_push (GTK_STATUSBAR (status_bar), 1, outtext_str);
	}

GtkWidget *create_warning_window (char *title, char *main_label, char *description1, char *description2, GtkSignalFunc ok_function, GtkSignalFunc cancel_function)
	{
  GtkWidget *warning_window;
  GtkWidget *warning_window_vbox;
  GtkWidget *warning_window_frame;
  GtkWidget *warning_window_table;
  GtkWidget *warning_window_main_label;
  GtkWidget *warning_window_description_line_1;
  GtkWidget *warning_window_separator;
  GtkWidget *warning_window_description_line_2;
  GtkWidget *warning_window_button_box;
  GtkWidget *warning_window_ok_button;
  GtkWidget *warning_window_cancel_button;

  warning_window = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (warning_window), "warning_window", warning_window);
  gtk_window_set_title (GTK_WINDOW (warning_window), title);
  gtk_window_set_position (GTK_WINDOW (warning_window), GTK_WIN_POS_CENTER);

  warning_window_vbox = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (warning_window_vbox);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_vbox", warning_window_vbox, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_vbox);
  gtk_container_add (GTK_CONTAINER (warning_window), warning_window_vbox);

  warning_window_frame = gtk_frame_new (NULL);
  gtk_widget_ref (warning_window_frame);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_frame", warning_window_frame, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_frame);
  gtk_box_pack_start (GTK_BOX (warning_window_vbox), warning_window_frame, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (warning_window_frame), 5);
  gtk_frame_set_shadow_type (GTK_FRAME (warning_window_frame), GTK_SHADOW_IN);

  warning_window_table = gtk_table_new (4, 3, TRUE);
  gtk_widget_ref (warning_window_table);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_table", warning_window_table, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_table);
  gtk_container_add (GTK_CONTAINER (warning_window_frame), warning_window_table);
  gtk_container_set_border_width (GTK_CONTAINER (warning_window_table), 5);

  warning_window_main_label = gtk_label_new ("");
  gtk_label_parse_uline (GTK_LABEL (warning_window_main_label), main_label);
  gtk_widget_ref (warning_window_main_label);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_main_label", warning_window_main_label, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_main_label);
  gtk_table_attach (GTK_TABLE (warning_window_table), warning_window_main_label, 0, 3, 0, 1, (GtkAttachOptions) (GTK_EXPAND), (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (warning_window_main_label), 0.0, 0.5);

  warning_window_description_line_1 = gtk_label_new ("");
  gtk_label_parse_uline (GTK_LABEL (warning_window_description_line_1), description1);
  gtk_widget_ref (warning_window_description_line_1);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_description_line_1", warning_window_description_line_1, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_description_line_1);
  gtk_table_attach (GTK_TABLE (warning_window_table), warning_window_description_line_1, 0, 3, 2, 3, (GtkAttachOptions) (GTK_EXPAND), (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (warning_window_description_line_1), 0.0, 0.5);
  gtk_misc_set_padding (GTK_MISC (warning_window_description_line_1), 10, 0);

  warning_window_separator = gtk_hseparator_new ();
  gtk_widget_ref (warning_window_separator);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_separator", warning_window_separator, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_separator);
  gtk_table_attach (GTK_TABLE (warning_window_table), warning_window_separator, 0, 3, 1, 2, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

  warning_window_description_line_2 = gtk_label_new ("");
  gtk_label_parse_uline (GTK_LABEL (warning_window_description_line_2), description2);
  gtk_widget_ref (warning_window_description_line_2);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_description_line_2", warning_window_description_line_2, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_description_line_2);
  gtk_table_attach (GTK_TABLE (warning_window_table), warning_window_description_line_2, 0, 3, 3, 4, (GtkAttachOptions) (GTK_EXPAND), (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (warning_window_description_line_2), 0.0, 0.5);

  warning_window_button_box = gtk_hbox_new (TRUE, 5);
  gtk_widget_ref (warning_window_button_box);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_button_box", warning_window_button_box, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_button_box);
  gtk_box_pack_start (GTK_BOX (warning_window_vbox), warning_window_button_box, FALSE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (warning_window_button_box), 5);

  warning_window_ok_button = gtk_button_new_with_label ("OK");
  gtk_widget_ref (warning_window_ok_button);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_ok_button", warning_window_ok_button, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_ok_button);
  gtk_box_pack_start (GTK_BOX (warning_window_button_box), warning_window_ok_button, FALSE, TRUE, 0);
  gtk_signal_connect_object (GTK_OBJECT (warning_window_ok_button), "clicked", GTK_SIGNAL_FUNC (ok_function), GTK_OBJECT (warning_window));

  warning_window_cancel_button = gtk_button_new_with_label ("Cancel");
  gtk_widget_ref (warning_window_cancel_button);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_cancel_button", warning_window_cancel_button, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_cancel_button);
  gtk_box_pack_start (GTK_BOX (warning_window_button_box), warning_window_cancel_button, FALSE, TRUE, 0);
  gtk_signal_connect_object (GTK_OBJECT (warning_window_cancel_button), "clicked", GTK_SIGNAL_FUNC (cancel_function), GTK_OBJECT (warning_window));

	gtk_widget_show (warning_window);

	return warning_window;
	}

GtkWidget *create_notice_window (char *title, char *main_label, char *description1, char *description2, GtkSignalFunc ok_function)
	{
  GtkWidget *warning_window;
  GtkWidget *warning_window_vbox;
  GtkWidget *warning_window_frame;
  GtkWidget *warning_window_table;
  GtkWidget *warning_window_main_label;
  GtkWidget *warning_window_description_line_1;
  GtkWidget *warning_window_separator;
  GtkWidget *warning_window_description_line_2;
  GtkWidget *warning_window_ok_button;

  warning_window = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (warning_window), "warning_window", warning_window);
  gtk_window_set_title (GTK_WINDOW (warning_window), title);
  gtk_window_set_position (GTK_WINDOW (warning_window), GTK_WIN_POS_CENTER);

  warning_window_vbox = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (warning_window_vbox);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_vbox", warning_window_vbox, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_vbox);
  gtk_container_add (GTK_CONTAINER (warning_window), warning_window_vbox);

  warning_window_frame = gtk_frame_new (NULL);
  gtk_widget_ref (warning_window_frame);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_frame", warning_window_frame, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_frame);
  gtk_box_pack_start (GTK_BOX (warning_window_vbox), warning_window_frame, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (warning_window_frame), 5);
  gtk_frame_set_shadow_type (GTK_FRAME (warning_window_frame), GTK_SHADOW_IN);

  warning_window_table = gtk_table_new (4, 3, TRUE);
  gtk_widget_ref (warning_window_table);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_table", warning_window_table, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_table);
  gtk_container_add (GTK_CONTAINER (warning_window_frame), warning_window_table);
  gtk_container_set_border_width (GTK_CONTAINER (warning_window_table), 5);

  warning_window_main_label = gtk_label_new ("");
  gtk_label_parse_uline (GTK_LABEL (warning_window_main_label), main_label);
  gtk_widget_ref (warning_window_main_label);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_main_label", warning_window_main_label, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_main_label);
  gtk_table_attach (GTK_TABLE (warning_window_table), warning_window_main_label, 0, 3, 0, 1, (GtkAttachOptions) (GTK_EXPAND), (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (warning_window_main_label), 0.0, 0.5);

  warning_window_description_line_1 = gtk_label_new ("");
  gtk_label_parse_uline (GTK_LABEL (warning_window_description_line_1), description1);
  gtk_widget_ref (warning_window_description_line_1);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_description_line_1", warning_window_description_line_1, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_description_line_1);
  gtk_table_attach (GTK_TABLE (warning_window_table), warning_window_description_line_1, 0, 3, 2, 3, (GtkAttachOptions) (GTK_EXPAND), (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (warning_window_description_line_1), 0.0, 0.5);
  gtk_misc_set_padding (GTK_MISC (warning_window_description_line_1), 10, 0);

  warning_window_separator = gtk_hseparator_new ();
  gtk_widget_ref (warning_window_separator);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_separator", warning_window_separator, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_separator);
  gtk_table_attach (GTK_TABLE (warning_window_table), warning_window_separator, 0, 3, 1, 2, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

  warning_window_description_line_2 = gtk_label_new ("");
  gtk_label_parse_uline (GTK_LABEL (warning_window_description_line_2), description2);
  gtk_widget_ref (warning_window_description_line_2);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_description_line_2", warning_window_description_line_2, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_description_line_2);
  gtk_table_attach (GTK_TABLE (warning_window_table), warning_window_description_line_2, 0, 3, 3, 4, (GtkAttachOptions) (GTK_EXPAND), (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (warning_window_description_line_2), 0.0, 0.5);

  warning_window_ok_button = gtk_button_new_with_label ("OK");
  gtk_widget_ref (warning_window_ok_button);
  gtk_object_set_data_full (GTK_OBJECT (warning_window), "warning_window_ok_button", warning_window_ok_button, (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (warning_window_ok_button);
  gtk_box_pack_start (GTK_BOX (warning_window_vbox), warning_window_ok_button, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (warning_window_ok_button), 5);
  gtk_signal_connect_object (GTK_OBJECT (warning_window_ok_button), "clicked", GTK_SIGNAL_FUNC (ok_function), GTK_OBJECT (warning_window));

	gtk_object_set_data (GTK_OBJECT (PHOEBE), "warning_window", warning_window);
	gtk_widget_show (warning_window);

	return warning_window;
	}

void set_clist_justifications ()
	{
	/* GLADE has problems defining the column justification for CList widgets,  */
	/* so we have to do it here manually:                                       */
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list")), 1, GTK_JUSTIFY_LEFT);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list")), 2, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_lc_info_list")), 3, GTK_JUSTIFY_CENTER);

	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list")), 1, GTK_JUSTIFY_LEFT);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list")), 2, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_rv_info_list")), 3, GTK_JUSTIFY_CENTER);

	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE_dc, "dc_parameters_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE_dc, "dc_parameters_info_list")), 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE_dc, "dc_parameters_info_list")), 2, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE_dc, "dc_parameters_info_list")), 3, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE_dc, "dc_parameters_info_list")), 4, GTK_JUSTIFY_CENTER);

	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE_dc, "dc_chi2_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE_dc, "dc_chi2_info_list")), 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE_dc, "dc_chi2_info_list")), 2, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE_dc, "dc_chi2_info_list")), 3, GTK_JUSTIFY_CENTER);

	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_lc_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_lc_info_list")), 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_lc_info_list")), 2, GTK_JUSTIFY_CENTER);

	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_el3_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_el3_info_list")), 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_el3_info_list")), 2, GTK_JUSTIFY_CENTER);

	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), 2, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), 3, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list")), 4, GTK_JUSTIFY_CENTER);

	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), 2, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), 3, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list")), 4, GTK_JUSTIFY_CENTER);

	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_weighting_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "luminosities_weighting_info_list")), 1, GTK_JUSTIFY_CENTER);

	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE_scripter, "scripter_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE_scripter, "scripter_info_list")), 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE_scripter, "scripter_info_list")), 2, GTK_JUSTIFY_CENTER);

	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), 2, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), 3, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "spots_primary_info_list")), 4, GTK_JUSTIFY_CENTER);

	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), 2, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), 3, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "spots_secondary_info_list")), 4, GTK_JUSTIFY_CENTER);

	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_files_info_list")), 0, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_files_info_list")), 1, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_files_info_list")), 2, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_files_info_list")), 3, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_files_info_list")), 4, GTK_JUSTIFY_CENTER);
	gtk_clist_set_column_justification (GTK_CLIST (lookup_widget (PHOEBE, "data_files_info_list")), 5, GTK_JUSTIFY_CENTER);

	return;
	}

void add_empty_record_to_all_lc_dependent_info_lists ()
{
	add_empty_record_to_lc_info_list ();
	add_empty_record_to_luminosities_lc_info_list ();
	add_empty_record_to_luminosities_el3_info_list ();
	add_empty_record_to_ld_monochromatic_lc_info_list ();
	add_empty_record_to_luminosities_weighting_info_list ();
	add_empty_record_to_data_files_info_list ();
}

void add_empty_record_to_all_rv_dependent_info_lists ()
	{
	add_empty_record_to_rv_info_list ();
	add_empty_record_to_ld_monochromatic_rv_info_list ();
	add_empty_record_to_data_files_info_list ();
	}

void add_empty_record_to_lc_info_list ()
{
 	GtkWidget *lc_list = lookup_widget (PHOEBE, "data_lc_info_list");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rows_already_present = GTK_CLIST (lc_list)->rows;
	int i;

	char **entry = phoebe_malloc (4 * sizeof (*entry));
	for (i = 0; i < 4; i++)
		entry[i] = phoebe_malloc (255 * sizeof (**entry));

	/* If lc_no is greater than 0, Edit button should be available: */
	if (lc_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "data_lc_edit_data_entry_button"), TRUE);
	if (lc_no == 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "data_lc_edit_data_entry_button"), FALSE);

	if (lc_no < rows_already_present)
		{
		for (i = rows_already_present; i > lc_no; i--)
			gtk_clist_remove (GTK_CLIST (lc_list), i-1);
		}

	if (lc_no > rows_already_present)
		for (i = rows_already_present; i < lc_no; i++) {
			sprintf (entry[0], "%d.", i+1);
			sprintf (entry[1], "Undefined");
			sprintf (entry[2], "0.01000");
			sprintf (entry[3], "Undefined");

			sprintf (PHOEBE_lc_data[i].column1,  "Phase");
			sprintf (PHOEBE_lc_data[i].column2,  "Magnitude");
			sprintf (PHOEBE_lc_data[i].column3,  "Weight (int)");
			sprintf (PHOEBE_lc_data[i].filename, "Undefined");
			sprintf (PHOEBE_lc_data[i].sigma,    "0.01000");
			sprintf (PHOEBE_lc_data[i].filter,   "Undefined");

			gtk_clist_append (GTK_CLIST (lc_list), entry);
		}

	for (i = 0; i < 4; i++) free (entry[i]); free (entry);
}

void add_empty_record_to_data_files_info_list ()
	{
	GtkWidget *data_list = lookup_widget (PHOEBE, "data_files_info_list");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));
	int rows_already_present = GTK_CLIST (data_list)->rows;
	int i;

	char entry_string[6][255];
	char *entry[6] = {entry_string[0], entry_string[1], entry_string[2], entry_string[3], entry_string[4], entry_string[5]};

	for (i = rows_already_present; i > 0; i--)
		gtk_clist_remove (GTK_CLIST (data_list), i-1);

	for (i = 0; i < lc_no; i++)
		{
		sprintf (entry[0], "Undefined");
		sprintf (entry[1], "0");
		sprintf (entry[2], "0.00000");
		sprintf (entry[3], "0.00000");
		sprintf (entry[4], "");
		sprintf (entry[5], "");

		gtk_clist_append (GTK_CLIST (data_list), entry);
		}
	for (i = 0; i < rv_no; i++)
		{
		sprintf (entry[0], "Undefined");
		sprintf (entry[1], "0");
		sprintf (entry[2], "0.00000");
		sprintf (entry[3], "0.00000");
		sprintf (entry[4], "");
		sprintf (entry[5], "");

		gtk_clist_append (GTK_CLIST (data_list), entry);
		}
	}

void add_empty_record_to_rv_info_list ()
	{
	GtkWidget *rv_list = lookup_widget (PHOEBE, "data_rv_info_list");
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));
	int rows_already_present = GTK_CLIST (rv_list)->rows;
	int i;

	char entry_string[4][255];
	char *entry[4] = {entry_string[0], entry_string[1], entry_string[2], entry_string[3]};

	/* If rv_no is greater than 0, Edit button should be available: */
	if (rv_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "data_rv_edit_data_entry_button"), TRUE);
	if (rv_no == 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "data_rv_edit_data_entry_button"), FALSE);

	if (rv_no < rows_already_present)
		{
		for (i = rows_already_present; i > rv_no; i--)
			gtk_clist_remove (GTK_CLIST (rv_list), i-1);
		}

	if (rv_no > rows_already_present)
		for (i = rows_already_present; i < rv_no; i++)
			{
			sprintf (entry[0], "%d.", i+1);
			sprintf (entry[1], "Undefined");
			sprintf (entry[2], "0.01000");
			sprintf (entry[3], "Undefined");

			sprintf (PHOEBE_rv_data[i].column1,  "Phase");
			sprintf (PHOEBE_rv_data[i].column2,  "RV in km/s");
			sprintf (PHOEBE_rv_data[i].column3,  "Weight (int)");
			sprintf (PHOEBE_rv_data[i].filename, "Undefined");
			sprintf (PHOEBE_rv_data[i].sigma,    "0.01000");
			sprintf (PHOEBE_rv_data[i].filter,   "Undefined");

			gtk_clist_append (GTK_CLIST (rv_list), entry);
			}
	}

void add_empty_record_to_luminosities_lc_info_list ()
	{
	GtkWidget *lc_list = lookup_widget (PHOEBE, "luminosities_lc_info_list");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rows_already_present = GTK_CLIST (lc_list)->rows;

	char entry_string[3][255];
	char *entry[3] = {entry_string[0], entry_string[1], entry_string[2]};

	int i;

	/* If lc_no is greater than 0, Edit button should be available: */
	if (lc_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "luminosities_lc_edit_entry_button"), TRUE);
	if (lc_no == 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "luminosities_lc_edit_entry_button"), FALSE);

	if (lc_no < rows_already_present)
		{
		for (i = rows_already_present; i > lc_no; i--)
			gtk_clist_remove (GTK_CLIST (lc_list), i-1);
		}

	if (lc_no > rows_already_present)
		for (i = rows_already_present; i < lc_no; i++)
			{
			sprintf (entry[0], "%s", PHOEBE_lc_data[i].filter);
			sprintf (entry[1], "10.00000");
			sprintf (entry[2], "10.00000");

			gtk_clist_append (GTK_CLIST (lc_list), entry);
			}
	}

void add_empty_record_to_luminosities_el3_info_list ()
	{
	GtkWidget *el3_list = lookup_widget (PHOEBE, "luminosities_el3_info_list");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rows_already_present = GTK_CLIST (el3_list)->rows;

	char entry_string[3][255];
	char *entry[3] = {entry_string[0], entry_string[1], entry_string[2]};

	int i;

	/* If lc_no is greater than 0, Edit button should be available: */
	if (lc_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "luminosities_el3_edit_entry_button"), TRUE);
	if (lc_no == 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "luminosities_el3_edit_entry_button"), FALSE);

	if (lc_no < rows_already_present)
		{
		for (i = rows_already_present; i > lc_no; i--)
			gtk_clist_remove (GTK_CLIST (el3_list), i-1);
		}

	if (lc_no > rows_already_present)
		for (i = rows_already_present; i < lc_no; i++)
			{
			sprintf (entry[0], "%s", PHOEBE_lc_data[i].filter);
			sprintf (entry[1], "0.00000");
			sprintf (entry[2], "0.00000");

			gtk_clist_append (GTK_CLIST (el3_list), entry);
			}
	}

void add_empty_record_to_ld_monochromatic_lc_info_list ()
	{
	GtkWidget *ld_list = lookup_widget (PHOEBE, "ld_monochromatic_lc_info_list");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rows_already_present = GTK_CLIST (ld_list)->rows;

	char entry_string[5][255];
	char *entry[5] = {entry_string[0], entry_string[1], entry_string[2], entry_string[3], entry_string[4]};

	int i;

	/* If lc_no is greater than 0, Edit button should be available: */
	if (lc_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "ld_monochromatic_lc_edit_entry_button"), TRUE);
	if (lc_no == 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "ld_monochromatic_lc_edit_entry_button"), FALSE);

	if (lc_no < rows_already_present)
		{
		for (i = rows_already_present; i > lc_no; i--)
			gtk_clist_remove (GTK_CLIST (ld_list), i-1);
		}

	if (lc_no > rows_already_present)
		for (i = rows_already_present; i < lc_no; i++)
			{
			sprintf (entry[0], "%s", PHOEBE_lc_data[i].filter);
			sprintf (entry[1], "0.50000");
			sprintf (entry[2], "0.50000");
			sprintf (entry[3], "0.50000");
			sprintf (entry[4], "0.50000");

			gtk_clist_append (GTK_CLIST (ld_list), entry);
			}
	}

void add_empty_record_to_ld_monochromatic_rv_info_list ()
	{
	GtkWidget *ld_list = lookup_widget (PHOEBE, "ld_monochromatic_rv_info_list");
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));
	int rows_already_present = GTK_CLIST (ld_list)->rows;

	char entry_string[5][255];
	char *entry[5] = {entry_string[0], entry_string[1], entry_string[2], entry_string[3], entry_string[4]};

	int i;

	/* If rv_no is greater than 0, Edit button should be available: */
	if (rv_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "ld_monochromatic_rv_edit_entry_button"), TRUE);
	if (rv_no == 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "ld_monochromatic_rv_edit_entry_button"), FALSE);

	if (rv_no < rows_already_present)
		{
		for (i = rows_already_present; i > rv_no; i--)
			gtk_clist_remove (GTK_CLIST (ld_list), i-1);
		}

	if (rv_no > rows_already_present)
		for (i = rows_already_present; i < rv_no; i++)
			{
			sprintf (entry[0], "%s", PHOEBE_rv_data[i].filter);
			sprintf (entry[1], "0.50000");
			sprintf (entry[2], "0.50000");
			sprintf (entry[3], "0.50000");
			sprintf (entry[4], "0.50000");

			gtk_clist_append (GTK_CLIST (ld_list), entry);
			}
	}

void add_empty_record_to_luminosities_weighting_info_list ()
	{
	GtkWidget *w_list = lookup_widget (PHOEBE, "luminosities_weighting_info_list");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rows_already_present = GTK_CLIST (w_list)->rows;

	char entry_string[2][255];
	char *entry[2] = {entry_string[0], entry_string[1]};

	int i;

	/* If lc_no is greater than 0, Edit button should be available: */
	if (lc_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "luminosities_weighting_edit_entry_button"), TRUE);
	if (lc_no == 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "luminosities_weighting_edit_entry_button"), FALSE);

	if (lc_no < rows_already_present)
		{
		for (i = rows_already_present; i > lc_no; i--)
			gtk_clist_remove (GTK_CLIST (w_list), i-1);
		}

	if (lc_no > rows_already_present)
		for (i = rows_already_present; i < lc_no; i++)
			{
			sprintf (entry[0], "%s", PHOEBE_lc_data[i].filter);
			sprintf (entry[1], "No Level-Dependent Weighting");

			gtk_clist_append (GTK_CLIST (w_list), entry);
			}
	}

void add_empty_record_to_spots_primary_info_list ()
	{
	GtkWidget *sp_list = lookup_widget (PHOEBE, "spots_primary_info_list");
	int sp_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "spots_sprim_value")));
	int rows_already_present = GTK_CLIST (sp_list)->rows;
	int i;

	char entry_string[5][255];
	char *entry[5] = {entry_string[0], entry_string[1], entry_string[2], entry_string[3], entry_string[4]};

	/* If sp_no is greater than 0, Edit button should be available: */
	if (sp_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "spots_edit_primary_button"), TRUE);
	if (sp_no == 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "spots_edit_primary_button"), FALSE);

	if (sp_no < rows_already_present)
		{
		for (i = rows_already_present; i > sp_no; i--)
			gtk_clist_remove (GTK_CLIST (sp_list), i-1);
		}

	if (sp_no > rows_already_present)
		for (i = rows_already_present; i < sp_no; i++)
			{
			sprintf (entry[0], "%d.", i+1);
			sprintf (entry[1], "0.00000");
			sprintf (entry[2], "0.00000");
			sprintf (entry[3], "0.00000");
			sprintf (entry[4], "1.00000");

			gtk_clist_append (GTK_CLIST (sp_list), entry);
			}
	}

void add_empty_record_to_spots_secondary_info_list ()
	{
	GtkWidget *sp_list = lookup_widget (PHOEBE, "spots_secondary_info_list");
	int sp_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "spots_ssec_value")));
	int rows_already_present = GTK_CLIST (sp_list)->rows;
	int i;

	char entry_string[5][255];
	char *entry[5] = {entry_string[0], entry_string[1], entry_string[2], entry_string[3], entry_string[4]};

	/* If sp_no is greater than 0, Edit button should be available: */
	if (sp_no != 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "spots_edit_secondary_button"), TRUE);
	if (sp_no == 0) gtk_widget_set_sensitive (lookup_widget (PHOEBE, "spots_edit_secondary_button"), FALSE);

	if (sp_no < rows_already_present)
		{
		for (i = rows_already_present; i > sp_no; i--)
			gtk_clist_remove (GTK_CLIST (sp_list), i-1);
		}

	if (sp_no > rows_already_present)
		for (i = rows_already_present; i < sp_no; i++)
			{
			sprintf (entry[0], "%d.", i+1);
			sprintf (entry[1], "0.00000");
			sprintf (entry[2], "0.00000");
			sprintf (entry[3], "0.00000");
			sprintf (entry[4], "0.00000");

			gtk_clist_append (GTK_CLIST (sp_list), entry);
			}
	}

void add_filters_to_available_filter_lists ()
	{
	/* This function is used to set all filter lists with one call from call-   */
	/* backs routines. This way, when adding available filter lists, we must    */
	/* change only this routine, everything else remains intact.                */

	add_filters_to_lc_plot_filter_list ();
	add_filters_to_rv_plot_filter_list ();
	add_filters_to_chi2_filter_list ();
	add_filters_to_ld_filter_list ();
	}

void add_filters_to_lc_plot_filter_list ()
	{
	/* This function fills the LC plotting combo box with filters that have     */
	/* been selected in a PHOEBE CList. */

	GtkWidget *filter_box = lookup_widget (PHOEBE_plot_lc, "plot_lc_data_combo_box");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));

	GtkWidget *new_item;
	int i;
	int modified = 0;

	/* First let's clear the contents of the combo-box:                         */
  gtk_list_clear_items (GTK_LIST (GTK_COMBO (filter_box)->list), 0, -1);

	/* Next, if there are no light-curves, put "None specified" to the combo:   */
	if (lc_no == 0)
		{
		new_item = gtk_list_item_new_with_label ("None Specified");
		gtk_widget_show (new_item);
		gtk_container_add (GTK_CONTAINER (GTK_COMBO (filter_box)->list), new_item);
		return;
		}

	/* Now we scan through all light curves and read out filters:               */
	for (i = 0; i < lc_no; i++)
		{
		if (strcmp (PHOEBE_lc_data[i].filter, "Undefined") != 0)
			{
			modified = 1;
			new_item = gtk_list_item_new_with_label (PHOEBE_lc_data[i].filter);
			gtk_widget_show (new_item);
			gtk_container_add (GTK_CONTAINER (GTK_COMBO (filter_box)->list), new_item);
			}
		}

	/* We don't want to have an empty combo box, so if there are no filters de- */
	/* fined, let's have a "None Specified" entry.                              */
	if (modified == 0)
		{
		new_item = gtk_list_item_new_with_label ("None Specified");
		gtk_widget_show (new_item);
		gtk_container_add (GTK_CONTAINER (GTK_COMBO (filter_box)->list), new_item);
		}

	return;
	}

void add_filters_to_rv_plot_filter_list ()
	{
	/* This function fills the RV plotting combo box with filters that have     */
	/* been selected in a PHOEBE CList. */

	GtkWidget *filter_box = lookup_widget (PHOEBE_plot_rv, "plot_rv_data_combo_box");
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));

	GtkWidget *new_item;
	int i;
	int modified = 0;

	if (rv_no == 0) return;

  gtk_list_clear_items (GTK_LIST (GTK_COMBO (filter_box)->list), 0, -1);

	for (i = 0; i < rv_no; i++)
		{
		if (strcmp (PHOEBE_rv_data[i].filter, "Undefined") != 0)
			{
			modified = 1;
			new_item = gtk_list_item_new_with_label (PHOEBE_rv_data[i].filter);
			gtk_widget_show (new_item);
			gtk_container_add (GTK_CONTAINER (GTK_COMBO (filter_box)->list), new_item);
			}
		}

	/* We don't want to have an empty combo box, so if there are no filters de- */
	/* fined, let's have a "None Specified" entry.                              */
	if (modified == 0)
		{
		new_item = gtk_list_item_new_with_label ("None Specified");
		gtk_widget_show (new_item);
		gtk_container_add (GTK_CONTAINER (GTK_COMBO (filter_box)->list), new_item);
		}

	return;
	}

void add_filters_to_chi2_filter_list ()
	{
	GtkWidget *filter_box = lookup_widget (PHOEBE, "fitting_chi2_filter");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));

	GtkWidget *new_item;
	int i;
	int modified = 0;

	if (lc_no == 0) return;

  gtk_list_clear_items (GTK_LIST (GTK_COMBO (filter_box)->list), 0, -1);

	for (i = 0; i < lc_no; i++)
		{
		if (strcmp (PHOEBE_lc_data[i].filter, "Undefined") != 0)
			{
			modified = 1;
			new_item = gtk_list_item_new_with_label (PHOEBE_lc_data[i].filter);
			gtk_widget_show (new_item);
			gtk_container_add (GTK_CONTAINER (GTK_COMBO (filter_box)->list), new_item);
			}
		}

	/* We don't want to have an empty combo box, so if there are no filters de- */
	/* fined, let's have an undefined entry. */
	if (modified == 0)
		{
		new_item = gtk_list_item_new_with_label ("Filter: None Specified");
		gtk_widget_show (new_item);
		gtk_container_add (GTK_CONTAINER (GTK_COMBO (filter_box)->list), new_item);
		}

	return;
	}

void add_filters_to_ld_filter_list ()
	{
	/* This function adds filter names that have been assigned at PHOEBE's LC   */
	/* CList widget and puts them to ld_interpolation combo box.                */

	GtkWidget *filter_box = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_filter_box");
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_lc_no_value")));
	int rv_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "data_rv_no_value")));

	GtkWidget *new_item;
	int i;

  gtk_list_clear_items (GTK_LIST (GTK_COMBO (filter_box)->list), 0, -1);

	/* We always want to have "bolometric" entry in the box:                    */
	new_item = gtk_list_item_new_with_label ("Bolometric");
	gtk_widget_show (new_item);
	gtk_container_add (GTK_CONTAINER (GTK_COMBO (filter_box)->list), new_item);

	for (i = 0; i < lc_no; i++)
		{
		if (strcmp (PHOEBE_lc_data[i].filter, "Undefined") != 0)
			{
			new_item = gtk_list_item_new_with_label (PHOEBE_lc_data[i].filter);
			gtk_widget_show (new_item);
			gtk_container_add (GTK_CONTAINER (GTK_COMBO (filter_box)->list), new_item);
			}
		}
	for (i = 0; i < rv_no; i++)
		{
		if (strcmp (PHOEBE_rv_data[i].filter, "Undefined") != 0)
			{
			new_item = gtk_list_item_new_with_label (PHOEBE_rv_data[i].filter);
			gtk_widget_show (new_item);
			gtk_container_add (GTK_CONTAINER (GTK_COMBO (filter_box)->list), new_item);
			}
		}

	return;
	}

int create_plot_to_file_drop_down_menu ()
	{
	/* Since SuperMongo and GnuPlot support different devices, the Plot to File */
	/* selector mustn't use all of them. This function is called on start-up    */
	/* and whenever the plotting program in the configuration is changed.       */

	GtkWidget *menu = lookup_widget (PHOEBE_plot_to_file, "plot_to_file_device_list");
	GList *menu_contents = NULL;

	menu_contents = g_list_append (menu_contents, (gpointer) "Encapsulated Postscript (.eps)");
	menu_contents = g_list_append (menu_contents, (gpointer) "Plain Text Table (.ascii)");
	menu_contents = g_list_append (menu_contents, (gpointer) "X-Windows Pixmap (.xpm)");
	if (strcmp (PHOEBE_PLOTTING_PACKAGE, "sm") == 0)
		{
		menu_contents = g_list_append (menu_contents, (gpointer) "Graphics Interchange Format (.gif)");
		menu_contents = g_list_append (menu_contents, (gpointer) "Small GIF: 256x128 (.gif)");
		menu_contents = g_list_append (menu_contents, (gpointer) "Portable Pixmap (.ppm)");
		}
	if (strcmp (PHOEBE_PLOTTING_PACKAGE, "gnuplot") == 0)
		menu_contents = g_list_append (menu_contents, (gpointer) "Portable Network Graphics (.png)");
	gtk_combo_set_popdown_strings (GTK_COMBO (menu), menu_contents);
	g_list_free (menu_contents);
	}

GtkWidget *phoebe_widget (PHOEBE_keyword keyword)
	{
	if (keyword == STARNAME) return lookup_widget (PHOEBE, "data_star_name_entry");
	if (keyword == MODEL)    return lookup_widget (PHOEBE, "data_model_list_entry");
	if (keyword == LCNO)     return lookup_widget (PHOEBE, "data_lc_no_value");
	if (keyword == RVNO)     return lookup_widget (PHOEBE, "data_rv_no_value");
	if (keyword == SPECNO)   return lookup_widget (PHOEBE, "data_spectra_no_value");
	if (keyword == HJD0)     return lookup_widget (PHOEBE, "system_hjd0_value");
	if (keyword == PERIOD)   return lookup_widget (PHOEBE, "system_period_value");
	if (keyword == DPDT)     return lookup_widget (PHOEBE, "system_dpdt_value");
	if (keyword == PSHIFT)   return lookup_widget (PHOEBE, "system_pshift_value");
	if (keyword == SMA)      return lookup_widget (PHOEBE, "system_sma_value");
	if (keyword == RM)       return lookup_widget (PHOEBE, "system_rm_value");
	if (keyword == INCL)     return lookup_widget (PHOEBE, "system_incl_value");
	if (keyword == VGA)      return lookup_widget (PHOEBE, "system_vga_value");
	if (keyword == TAVH)     return lookup_widget (PHOEBE, "component_tavh_value");
	if (keyword == TAVC)     return lookup_widget (PHOEBE, "component_tavc_value");
	if (keyword == PHSV)     return lookup_widget (PHOEBE, "component_phsv_value");
	if (keyword == PCSV)     return lookup_widget (PHOEBE, "component_pcsv_value");
	if (keyword == LOGG1)    return lookup_widget (PHOEBE, "component_logg1_value");
	if (keyword == LOGG2)    return lookup_widget (PHOEBE, "component_logg2_value");
	if (keyword == MET1)     return lookup_widget (PHOEBE, "component_met1_value");
	if (keyword == MET2)     return lookup_widget (PHOEBE, "component_met2_value");
	if (keyword == E)        return lookup_widget (PHOEBE, "orbit_e_value");
	if (keyword == PERR0)    return lookup_widget (PHOEBE, "orbit_perr0_value");
	if (keyword == DPERDT)   return lookup_widget (PHOEBE, "orbit_dperdt_value");
	if (keyword == F1)       return lookup_widget (PHOEBE, "orbit_f1_value");
	if (keyword == F2)       return lookup_widget (PHOEBE, "orbit_f2_value");
	if (keyword == ALB1)     return lookup_widget (PHOEBE, "surface_alb1_value");
	if (keyword == ALB2)     return lookup_widget (PHOEBE, "surface_alb2_value");
	if (keyword == GR1)      return lookup_widget (PHOEBE, "surface_gr1_value");
	if (keyword == GR2)      return lookup_widget (PHOEBE, "surface_gr2_value");
	if (keyword == MNORM)    return lookup_widget (PHOEBE, "data_zero_magnitude_value");
	if (keyword == LC_PLOT_SYNTHETIC)
	                         return lookup_widget (PHOEBE_plot_lc, "plot_lc_synthetic_lightcurve");
	if (keyword == LC_PLOT_EXPERIMENTAL)
	                         return lookup_widget (PHOEBE_plot_lc, "plot_lc_experimental_data");
	if (keyword == LC_FILTER)
	                         return lookup_widget (PHOEBE_plot_lc, "plot_lc_data_combo_box_entry");
	if (keyword == RV_PLOT_SYNTHETIC)
	                         return lookup_widget (PHOEBE_plot_rv, "plot_rv_synthetic_lightcurve");
	if (keyword == RV_PLOT_EXPERIMENTAL)
	                         return lookup_widget (PHOEBE_plot_rv, "plot_rv_experimental_data");
	if (keyword == RV_FILTER)
	                         return lookup_widget (PHOEBE_plot_rv, "plot_rv_data_combo_box_entry");
	}

PHOEBE_keyword get_phoebe_keyword_from_keyword_name (char *keyword)
	{
	if (strcmp (keyword, "STARNAME")             == 0) return STARNAME;
	if (strcmp (keyword, "MODEL")                == 0) return MODEL;
	if (strcmp (keyword, "LCNO")                 == 0) return LCNO;
	if (strcmp (keyword, "RVNO")                 == 0) return RVNO;
	if (strcmp (keyword, "SPECNO")               == 0) return SPECNO;
	if (strcmp (keyword, "HJD0")                 == 0) return HJD0;
	if (strcmp (keyword, "PERIOD")               == 0) return PERIOD;
	if (strcmp (keyword, "DPDT")                 == 0) return DPDT;
	if (strcmp (keyword, "PSHIFT")               == 0) return PSHIFT;
	if (strcmp (keyword, "SMA")                  == 0) return SMA;
	if (strcmp (keyword, "RM")                   == 0) return RM;
	if (strcmp (keyword, "INCL")                 == 0) return INCL;
	if (strcmp (keyword, "VGA")                  == 0) return VGA;
	if (strcmp (keyword, "TAVH")                 == 0) return TAVH;
	if (strcmp (keyword, "TAVC")                 == 0) return TAVC;
	if (strcmp (keyword, "PHSV")                 == 0) return PHSV;
	if (strcmp (keyword, "PCSV")                 == 0) return PCSV;
	if (strcmp (keyword, "LOGG1")                == 0) return LOGG1;
	if (strcmp (keyword, "LOGG2")                == 0) return LOGG2;
	if (strcmp (keyword, "MET1")                 == 0) return MET1;
	if (strcmp (keyword, "MET2")                 == 0) return MET2;
	if (strcmp (keyword, "E")                    == 0) return E;
	if (strcmp (keyword, "PERR0")                == 0) return PERR0;
	if (strcmp (keyword, "DPERDT")               == 0) return DPERDT;
	if (strcmp (keyword, "F1")                   == 0) return F1;
	if (strcmp (keyword, "F2")                   == 0) return F2;
	if (strcmp (keyword, "ALB1")                 == 0) return ALB1;
	if (strcmp (keyword, "ALB2")                 == 0) return ALB2;
	if (strcmp (keyword, "GR1")                  == 0) return GR1;
	if (strcmp (keyword, "GR2")                  == 0) return GR2;
	if (strcmp (keyword, "MNORM")                == 0) return MNORM;
	if (strcmp (keyword, "LC_PLOT_SYNTHETIC")    == 0) return LC_PLOT_SYNTHETIC;
	if (strcmp (keyword, "LC_PLOT_EXPERIMENTAL") == 0) return LC_PLOT_EXPERIMENTAL;
	if (strcmp (keyword, "LC_FILTER")            == 0) return LC_FILTER;
	if (strcmp (keyword, "RV_PLOT_SYNTHETIC")    == 0) return RV_PLOT_SYNTHETIC;
	if (strcmp (keyword, "RV_PLOT_EXPERIMENTAL") == 0) return RV_PLOT_EXPERIMENTAL;
	if (strcmp (keyword, "RV_FILTER")            == 0) return RV_FILTER;
	}

void phoebe_common_name (PHOEBE_keyword keyword, char **string)
	{
	if (keyword == STARNAME) sprintf (*string, "Star Name:");
	if (keyword == MODEL)    sprintf (*string, "Model:");
	if (keyword == LCNO)     sprintf (*string, "Light Curves:");
	if (keyword == RVNO)     sprintf (*string, "RV Curves:");
	if (keyword == SPECNO)   sprintf (*string, "Spectra:");
	if (keyword == HJD0)     sprintf (*string, "HJD0:");
	if (keyword == PERIOD)   sprintf (*string, "Period:");
	if (keyword == DPDT)     sprintf (*string, "Period Time Derivative:");
	if (keyword == PSHIFT)   sprintf (*string, "Phase Shift:");
	if (keyword == SMA)      sprintf (*string, "Semimajor Axis:");
	if (keyword == RM)       sprintf (*string, "Mass Ratio:");
	if (keyword == INCL)     sprintf (*string, "Inclination:");
	if (keyword == VGA)      sprintf (*string, "Gamma Velocity:");
	if (keyword == TAVH)     sprintf (*string, "Primary Temperature:");
	if (keyword == TAVC)     sprintf (*string, "Secondary Temperature:");
	if (keyword == PHSV)     sprintf (*string, "Primary Potential:");
	if (keyword == PCSV)     sprintf (*string, "Secondary Potential:");
	if (keyword == LOGG1)    sprintf (*string, "Primary log g:");
	if (keyword == LOGG2)    sprintf (*string, "Secondary log g:");
	if (keyword == MET1)     sprintf (*string, "Primary Metallicity:");
	if (keyword == MET2)     sprintf (*string, "Secondary Metallicity:");
	if (keyword == E)        sprintf (*string, "Orbital Eccentricity:");
	if (keyword == PERR0)    sprintf (*string, "Argument of Periastron:");
	if (keyword == DPERDT)   sprintf (*string, "Periastron Time Derivative:");
	if (keyword == F1)       sprintf (*string, "Primary Synchronicity:");
	if (keyword == F2)       sprintf (*string, "Secondary Synchronicity:");
	if (keyword == ALB1)     sprintf (*string, "Primary Star Albedo:");
	if (keyword == ALB2)     sprintf (*string, "Secondary Star Albedo:");
	if (keyword == GR1)      sprintf (*string, "Primary Gravity Brightening:");
	if (keyword == GR2)      sprintf (*string, "Secondary Gravity Brightening:");
	if (keyword == MNORM)    sprintf (*string, "Flux-normalizing Magnitude:");
	if (keyword == LC_PLOT_SYNTHETIC)
	                         sprintf (*string, "Plot synthetic lightcurve:");
	if (keyword == LC_PLOT_EXPERIMENTAL)
	                         sprintf (*string, "Plot observed lightcurve:");
	if (keyword == LC_FILTER)
	                         sprintf (*string, "Plotted LC filter:");
	if (keyword == RV_PLOT_SYNTHETIC)
	                         sprintf (*string, "Plot synthetic RV curve:");
	if (keyword == RV_PLOT_EXPERIMENTAL)
	                         sprintf (*string, "Plot observed RV curve:");
	if (keyword == RV_FILTER)
	                         sprintf (*string, "Plotted RV filter:");
	}

void add_to_scripter_commands (PHOEBE_script_command command)
	{
	int i;

	PHOEBE_command_list.command_no++;
	PHOEBE_command_list.command = phoebe_realloc (PHOEBE_command_list.command, PHOEBE_command_list.command_no * sizeof (PHOEBE_script_command));
	sprintf (PHOEBE_command_list.command[PHOEBE_command_list.command_no-1].name, command.name);
	sprintf (PHOEBE_command_list.command[PHOEBE_command_list.command_no-1].description, command.description);
	PHOEBE_command_list.command[PHOEBE_command_list.command_no-1].parno = command.parno;
	for (i = 0; i < command.parno; i++)
		{
		sprintf (PHOEBE_command_list.command[PHOEBE_command_list.command_no-1].label[i], command.label[i]);
 		PHOEBE_command_list.command[PHOEBE_command_list.command_no-1].widget[i] = command.widget[i];
		}
	}

void define_scripter_commands ()
	{
	PHOEBE_script_command command;

	sprintf (command.name, "OpenKeywordFile");
	sprintf (command.description, "Open Keyword File");
	command.parno = 1;
	sprintf (command.label[0], "Filename:");
	command.widget[0] = lookup_widget (PHOEBE_scripter, "scripter_parameter1_entry");
	add_to_scripter_commands (command);

	sprintf (command.name, "SaveKeywordFile");
	sprintf (command.description, "Save Keyword File");
	command.parno = 1;
	sprintf (command.label[0], "Filename:");
	command.widget[0] = lookup_widget (PHOEBE_scripter, "scripter_parameter1_entry");
	add_to_scripter_commands (command);

	sprintf (command.name, "QuitPHOEBE");
	sprintf (command.description, "Quit PHOEBE");
	command.parno = 0;
	add_to_scripter_commands (command);

	sprintf (command.name, "ChangeParameterValue");
	sprintf (command.description, "Change Parameter Value");
	command.parno = 2;
	sprintf (command.label[0], "Keyword:");
	command.widget[0] = lookup_widget (PHOEBE_scripter, "scripter_parameter1_entry");
	sprintf (command.label[1], "Value:");
	command.widget[1] = lookup_widget (PHOEBE_scripter, "scripter_parameter2_entry");
	add_to_scripter_commands (command);

	sprintf (command.name, "PlotLCToFile");
	sprintf (command.description, "Plot LC to File");
	command.parno = 3;
	sprintf (command.label[0], "Filter:");
	command.widget[0] = lookup_widget (PHOEBE_scripter, "scripter_parameter1_entry");
	sprintf (command.label[1], "Device:");
	command.widget[1] = lookup_widget (PHOEBE_scripter, "scripter_parameter2_entry");
	sprintf (command.label[2], "Filename:");
	command.widget[2] = lookup_widget (PHOEBE_scripter, "scripter_parameter3_entry");
	add_to_scripter_commands (command);

	sprintf (command.name, "PlotRVToFile");
	sprintf (command.description, "Plot RV to File");
	command.parno = 3;
	sprintf (command.label[0], "Filter:");
	command.widget[0] = lookup_widget (PHOEBE_scripter, "scripter_parameter1_entry");
	sprintf (command.label[1], "Device:");
	command.widget[1] = lookup_widget (PHOEBE_scripter, "scripter_parameter2_entry");
	sprintf (command.label[2], "Filename:");
	command.widget[2] = lookup_widget (PHOEBE_scripter, "scripter_parameter3_entry");
	add_to_scripter_commands (command);

	sprintf (command.name, "AddParameterToDataSheet");
	sprintf (command.description, "Add Parameter to Data Sheet");
	command.parno = 1;
	sprintf (command.label[0], "Parameter:");
	command.widget[0] = lookup_widget (PHOEBE_scripter, "scripter_parameter1_entry");
	add_to_scripter_commands (command);

	sprintf (command.name, "SaveDataSheetToFile");
	sprintf (command.description, "Save Data Sheet to File");
	command.parno = 1;
	sprintf (command.label[0], "Filename:");
	command.widget[0] = lookup_widget (PHOEBE_scripter, "scripter_parameter1_entry");
	add_to_scripter_commands (command);

	sprintf (command.name, "SaveRelevantSheetToFile");
	sprintf (command.description, "Save Relevant Data Sheet to File");
	command.parno = 1;
	sprintf (command.label[0], "Filename:");
	command.widget[0] = lookup_widget (PHOEBE_scripter, "scripter_parameter1_entry");
	add_to_scripter_commands (command);

	sprintf (command.name, "CalculateCircularGravityPotentialForPrimaryStar");
	sprintf (command.description, "Calculate Circular Gravity Potential for Primary Star");
	command.parno = 2;
	sprintf (command.label[0], "Mass ratio:");
	command.widget[0] = lookup_widget (PHOEBE_scripter, "scripter_parameter1_entry");
	sprintf (command.label[1], "R/SMA:");
	command.widget[1] = lookup_widget (PHOEBE_scripter, "scripter_parameter2_entry");
	add_to_scripter_commands (command);

	sprintf (command.name, "CalculateCircularGravityPotentialForSecondaryStar");
	sprintf (command.description, "Calculate Circular Gravity Potential for Secondary Star");
	command.parno = 2;
	sprintf (command.label[0], "Mass ratio:");
	command.widget[0] = lookup_widget (PHOEBE_scripter, "scripter_parameter1_entry");
	sprintf (command.label[1], "R/SMA:");
	command.widget[1] = lookup_widget (PHOEBE_scripter, "scripter_parameter2_entry");
	add_to_scripter_commands (command);

	sprintf (command.name, "AdjustParameters");
	sprintf (command.description, "Adjust Parameters");
	command.parno = 1;
	sprintf (command.label[0], "Parameter(s):");
	command.widget[0] = lookup_widget (PHOEBE_scripter, "scripter_parameter1_entry");
	add_to_scripter_commands (command);

	sprintf (command.name, "EstimateNormalizingMagnitude");
	sprintf (command.description, "Estimate Normalizing Magnitude");
	command.parno = 0;
	add_to_scripter_commands (command);
	}

void populate_scripter_command_list ()
	{
	GtkWidget *list = lookup_widget (PHOEBE_scripter, "scripter_action_list");
	GtkWidget *menu = gtk_menu_new ();
	GtkWidget *menu_item;
	
	int i;
	
	for (i = 0; i < PHOEBE_command_list.command_no; i++)
		{
	  menu_item = gtk_menu_item_new_with_label (PHOEBE_command_list.command[i].description);
		gtk_menu_append (GTK_MENU (menu), menu_item);
		gtk_widget_show (menu_item);
		}

  gtk_option_menu_set_menu (GTK_OPTION_MENU (list), menu);
	}
