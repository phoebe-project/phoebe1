#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "phoebe_allocations.h"
#include "phoebe_global.h"
#include "phoebe_gui_accessories.h"
#include "phoebe_gui_support.h"
#include "phoebe_gui_keyword.h"
#include "phoebe_phsv_pcsv.h"
#include "phoebe_scripting.h"

void save_script (char *filename)
	{
	GtkWidget *script_list = lookup_widget (PHOEBE_scripter, "scripter_info_list");

	int i;
	FILE *script_file = fopen (filename, "w");

	char *action, *params;

	for (i = 0; i < GTK_CLIST (script_list)->rows; i++)
		{
		gtk_clist_get_text (GTK_CLIST (script_list), i, 0, &action);
		gtk_clist_get_text (GTK_CLIST (script_list), i, 1, &params);
		fprintf (script_file, "%s (%s)\n", action, params);
		}

	fclose (script_file);
	}

void open_script (char *filename)
	{
	GtkWidget *script_list = lookup_widget (PHOEBE_scripter, "scripter_info_list");

	FILE *script_file = fopen (filename, "r");

	char keyword_string[255];
	char *keyword_str = keyword_string;

	char action_string[255];
	char *action = action_string;

	char params_string[255];
	char *params = params_string;

	int i = 0;

	char entry_string[3][255];
	char *entry[3] = {entry_string[0], entry_string[1], entry_string[2]};

	/* Let's clear the contents of the script list:                             */
	gtk_clist_clear (GTK_CLIST (script_list));

	while (!feof (script_file))
		{
		i++;
		if (fgets (keyword_str, 255, script_file) == NULL) break;
		params = strchr (keyword_str, '(');
		if (params == NULL)
			{
			printf ("Delimeters '(', ')' missing in script line %d. Breaking...\n", i);
			break;
			}
		keyword_str[strlen(keyword_str)] = '\0';
		params[strlen(params)-1] = '\0';
		strncpy (action, keyword_str, strlen(keyword_str)-strlen(params));
		action[strlen(keyword_str)-strlen(params)] = '\0';
		/* Strip all white spaces at the end of the action name:                  */
		while (action[strlen(action)-1] == ' ') strip_string_tail (action);
		/* Strip parentheses from parameters' list:                               */
		params[strlen(params)-1] = '\0'; params++;
		/* Fill in the values to the script list:                                 */
		sprintf (entry[0], action);
		sprintf (entry[1], params);
		sprintf (entry[2], "not executed");
		gtk_clist_append (GTK_CLIST (script_list), entry);
		}

	fclose (script_file);
	}

void script_open_file (char *filename)
	{
	open_keyword_file (filename);
	on_data_lc_filter_changed ();
	on_data_rv_filter_changed ();
	add_filters_to_available_filter_lists ();
	read_in_data_file_specifics ();
	}

void script_save_file (char *filename)
	{
	save_keyword_file (filename);
	}

void script_phoebe_quit ()
	{
	char system_string[255];
	char *system_str = system_string;

	sprintf (system_str, "rm -f %s/phoebe_*", PHOEBE_TEMP_DIR);
	system (system_str);

	exit (0);
	}

void script_plot_lc_to_file (char *filter, PHOEBE_plot_device device, char *filename)
	{
	script_change_parameter_value ("LC_FILTER", filter);
	plot_lc_plot (device, filename);
	}

void script_plot_rv_to_file (char *filter, PHOEBE_plot_device device, char *filename)
	{
	plot_rv_plot (device, filename);
	}

void script_calculate_circular_phsv_value (double q, double r)
	{
	double value;

	value = calculate_phsv_value (0, 1.0, q, r, 1.0, 1.0, 0.0);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "component_phsv_value")), value);
	}

void script_calculate_circular_pcsv_value (double q, double r)
	{
	double value;

	value = calculate_pcsv_value (0, 1.0, q, r, 1.0, 1.0, 0.0);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (lookup_widget (PHOEBE, "component_pcsv_value")), value);
	}

void script_add_parameter_to_data_sheet (char *keyword)
	{
	/* The user may input only strings, not PHOEBE_keyword types, thus we must  */
	/* make a conversion first.                                                 */
	PHOEBE_keyword delimeter = get_phoebe_keyword_from_keyword_name (keyword);
	char readout_string[255];
	char *readout_str = readout_string;

	phoebe_common_name (delimeter, &readout_str);
	add_parameter_to_data_sheet_list (readout_str, delimeter);
	}

void script_add_custom_parameter_to_data_sheet (char *keyword, char *value)
	{
	add_entry_to_data_sheet_list (keyword, value);
	}

void script_save_data_sheet_to_file (char *filename)
	{
	save_data_sheet_parameters_to_file (filename);
	}

void script_save_relevant_data_sheet_to_file (char *filename)
	{
	add_relevant_parameters_to_data_sheet_list ();
	save_data_sheet_parameters_to_file (filename);
	}

void script_change_parameter_value (char *keyword, char *value)
	{
	PHOEBE_keyword delimeter = get_phoebe_keyword_from_keyword_name (keyword);
	GtkWidget *widget = phoebe_widget (delimeter);
	
	if ( (GTK_IS_ENTRY (widget)) && (!GTK_IS_SPIN_BUTTON (widget)) )
		{
		/* GtkSpinButton contains an entry, so GTK_IS_ENTRY returns true for      */
		/* GtkSpinButton as well. That's why we have to avoid it this way.        */
		gtk_entry_set_text (GTK_ENTRY (widget), value);
		}
	if (GTK_IS_SPIN_BUTTON (widget))
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), atof (value));
	if (GTK_IS_TOGGLE_BUTTON (widget))
		{
		if (strcmp (value, "TRUE") == 0) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);
		                            else gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), FALSE);
		}
	}

void script_adjust_parameters ()
	{
	on_dc_calculate_button_clicked (NULL, NULL);
	on_dc_update_corrections_button_clicked (NULL, NULL);
	}

void script_estimate_normalizing_magnitude ()
	{
	int lc_no = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (phoebe_widget (LCNO)));
	int i;

	char *readout_str;
	double median = 0.0;

	char working_string[255];
	char *working_str = working_string;

	for (i = 0; i < lc_no; i++)
		{
		gtk_clist_get_text (GTK_CLIST (lookup_widget (PHOEBE, "data_files_info_list")), i, 3, &readout_str);
		median += atof (readout_str);
		}
	median /= lc_no;
	sprintf (working_str, "%lf", median);
	script_change_parameter_value ("MNORM", working_str);
	}
