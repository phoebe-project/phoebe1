#include <gtk/gtk.h>

#include "phoebe_global.h"
#include "phoebe_gui_ld.h"
#include "phoebe_gui_support.h"

int set_values_of_ld_window ()
	{
	/* This function takes parameters from main PHOEBE window and inputs them   */
	/* to ld_interpolation window widgets.                                      */

	GtkWidget *readout_widget;
	double readout_dbl;
	char *readout_str;

	readout_widget = lookup_widget (PHOEBE, "ld_ld_law_combo_box_entry");
	readout_str = gtk_entry_get_text (GTK_ENTRY (readout_widget));
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_ldlaw_box_entry");
	gtk_entry_set_text (GTK_ENTRY (readout_widget), readout_str);
	
	readout_widget = lookup_widget (PHOEBE, "component_tavh_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_tavh_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);

	readout_widget = lookup_widget (PHOEBE, "component_tavc_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_tavc_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);

	readout_widget = lookup_widget (PHOEBE, "component_logg1_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_primary_logg_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);

	readout_widget = lookup_widget (PHOEBE, "component_logg2_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_secondary_logg_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);

	readout_widget = lookup_widget (PHOEBE, "component_met1_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_primary_metallicity_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);

	readout_widget = lookup_widget (PHOEBE, "component_met2_value");
	readout_dbl = gtk_spin_button_get_value_as_float (GTK_SPIN_BUTTON (readout_widget));
	readout_widget = lookup_widget (PHOEBE_ld_interpolation, "ld_interpolation_secondary_metallicity_value");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (readout_widget), readout_dbl);

	return 0;
	}
