#ifndef PHOEBE_SCRIPTING_H
#define PHOEBE_SCRIPTING_H 1

void save_script (char *filename);
void open_script (char *filename);

void script_open_file (char *filename);
void script_save_file (char *filename);
void script_phoebe_quit ();
void script_plot_lc_to_file (char *filter, PHOEBE_plot_device device, char *filename);
void script_plot_rv_to_file (char *filter, PHOEBE_plot_device device, char *filename);
void script_calculate_circular_phsv_value (double q, double r);
void script_calculate_circular_pcsv_value (double q, double r);
void script_add_parameter_to_data_sheet (char *keyword);
void script_add_custom_parameter_to_data_sheet (char *keyword, char *value);
void script_save_data_sheet_to_file (char *filename);
void script_save_relevant_data_sheet_to_file (char *filename);
void script_change_parameter_value (char *keyword, char *value);
void script_adjust_parameters ();
void script_estimate_normalizing_magnitude ();

#endif
