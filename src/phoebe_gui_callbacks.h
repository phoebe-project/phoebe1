#ifndef PHOEBE_GUI_CALLBACKS_H
	#define PHOEBE_GUI_CALLBACKS_H 1

#include <gtk/gtk.h>

void on_switches_toggled (GtkToggleButton *togglebutton, gpointer user_data);
void on_switches_reverse_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void on_data_lc_no_value_changed (GtkEditable *editable, gpointer user_data);
void on_data_rv_no_value_changed (GtkEditable *editable, gpointer user_data);
void on_data_lc_filter_changed ();
void on_data_rv_filter_changed ();

void on_component_phsv_calculate_button_clicked (GtkButton *button, gpointer user_data);
void on_component_pcsv_calculate_button_clicked (GtkButton *button, gpointer user_data);

void on_calculate_phsv_calculate_button_clicked (GtkButton *button, gpointer user_data);
void on_calculate_phsv_update_button_clicked (GtkButton *button, gpointer user_data);
void on_calculate_pcsv_calculate_button_clicked (GtkButton *button, gpointer user_data);
void on_calculate_pcsv_update_button_clicked (GtkButton *button, gpointer user_data);

void on_ipb_switch_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void on_menu_bar_settings_configure_clicked (GtkMenuItem *menuitem, gpointer user_data);
void on_save_as_button_clicked (GtkMenuItem *menuitem, gpointer user_data);
void on_menu_bar_file_new_activated (GtkMenuItem *menuitem, gpointer user_data);
void on_menu_bar_file_exit_activated (GtkMenuItem *menuitem, gpointer user_data);
void on_menu_bar_file_import_from_dci_activate (GtkMenuItem *menuitem, gpointer user_data);
void on_menu_bar_file_export_to_dci_activate (GtkMenuItem *menuitem, gpointer user_data);

void on_open_button_clicked       (GtkButton *button, gpointer user_data);
void on_save_button_clicked       (GtkButton *button, gpointer user_data);
void on_defaults_button_clicked   (GtkButton *button, gpointer user_data);
void on_lc_plot_button_clicked    (GtkButton *button, gpointer user_data);
void on_rv_plot_button_clicked    (GtkButton *button, gpointer user_data);
void on_data_sheet_button_clicked (GtkButton *button, gpointer user_data);

void on_open_data_file_ok_button_clicked (GtkButton *button, gpointer user_data);

void on_open_keyword_file_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_save_keyword_file_ok_button_clicked  (GtkButton *button, gpointer user_data);

void on_plot_lc_plot_button_clicked  (GtkButton *button, gpointer user_data);
void on_plot_lc_clear_button_clicked (GtkButton *button, gpointer user_data);
void on_plot_lc_done_button_clicked  (GtkButton *button, gpointer user_data);

void on_configuration_browse_button_clicked (GtkButton *button, gpointer user_data);
void on_configuration_browse_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_configuration_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_configuration_save_button_clicked (GtkButton *button, gpointer user_data);

void on_warning_no_configuration_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_warning_keyword_file_exists_ok_button_clicked (GtkWidget *widget, gpointer user_data);
void on_warning_configuration_file_exists_ok_button_clicked (GtkWidget *widget, gpointer user_data);
void on_warning_on_new_ok_button_clicked (GtkWidget *widget, gpointer user_data);
void on_warning_on_exit_ok_button_clicked (GtkWidget *widget, gpointer user_data);
void on_warning_confirm_on_save_ok_button_clicked (GtkWidget *widget, gpointer user_data);

void on_plot_lc_shift_up_clicked (GtkButton *button, gpointer user_data);
void on_plot_lc_shift_left_clicked (GtkButton *button, gpointer user_data);
void on_plot_lc_shift_down_clicked (GtkButton *button, gpointer user_data);
void on_plot_lc_shift_right_clicked (GtkButton *button, gpointer user_data);
void on_plot_lc_reset_button_clicked (GtkButton *button, gpointer user_data);

void on_plot_lc_zoom_in_button_clicked (GtkButton *button, gpointer user_data);
void on_plot_lc_zoom_out_button_clicked (GtkButton *button, gpointer user_data);

void on_plot_lc_dependent_variable_changed (GtkEditable *editable, gpointer user_data);
void on_plot_rv_dependent_variable_changed (GtkEditable *editable, gpointer user_data);

void on_plot_rv_shift_up_clicked (GtkButton *button, gpointer user_data);
void on_plot_rv_shift_left_clicked (GtkButton *button, gpointer user_data);
void on_plot_rv_shift_down_clicked (GtkButton *button, gpointer user_data);
void on_plot_rv_shift_right_clicked (GtkButton *button, gpointer user_data);
void on_plot_rv_reset_button_clicked (GtkButton *button, gpointer user_data);
void on_plot_rv_zoom_out_button_clicked (GtkButton *button, gpointer user_data);
void on_plot_rv_zoom_in_button_clicked (GtkButton *button, gpointer user_data);
void on_plot_rv_plot_button_clicked (GtkButton *button, gpointer user_data);
void on_plot_rv_clear_button_clicked (GtkButton *button, gpointer user_data);
void on_plot_rv_done_button_clicked (GtkButton *button, gpointer user_data);

void on_ld_interpolation_clicked (GtkButton *button, gpointer user_data);
void on_ld_interpolation_interpolate_button_clicked (GtkButton *button, gpointer user_data);
void on_ld_interpolation_update_button_clicked (GtkButton *button, gpointer user_data);
void on_ld_interpolation_update_all_button_clicked (GtkButton *button, gpointer user_data);

void on_menu_bar_about_clicked (GtkMenuItem *menuitem, gpointer user_data);

void on_fitting_chi2_calculate_button_clicked (GtkButton *button, gpointer user_data);
void on_luminosities_seed_button_clicked (GtkButton *button, gpointer user_data);

void on_fitting_mms_value_changed (GtkEditable *editable, gpointer user_data);

void on_utilities_use_grid_button_clicked (GtkButton *button, gpointer user_data);
void on_utilities_calculate_grid_button_clicked (GtkButton *button, gpointer user_data);

void on_synthetic_grid_calculate_button_clicked (GtkButton *button, gpointer user_data);
void on_synthetic_grid_cancel_button_clicked (GtkButton *button, gpointer user_data);

void     on_synthetic_grid_edit_entry_button_clicked (GtkButton *button, gpointer user_data);
gboolean on_synthetic_grid_list_double_clicked       (GtkWidget *widget, GdkEvent *event, gpointer user_data);

void on_synthetic_grid_params_value_changed (GtkEditable *editable, gpointer user_data);
void on_synthetic_grid_nodes_value_changed (GtkEditable *editable, gpointer user_data);
void on_synthetic_grid_vertexes_value_changed (GtkEditable *editable, gpointer user_data);
void on_synthetic_grid_filters_value_changed (GtkEditable *editable, gpointer user_data);

void on_synthetic_grid_parameters_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_synthetic_grid_parameters_cancel_button_clicked (GtkButton *button, gpointer user_data);

void     on_data_lc_edit_data_entry_button_clicked (GtkButton *button, gpointer user_data);
gboolean on_data_lc_info_double_clicked            (GtkWidget *widget, GdkEvent *event, gpointer user_data);

void on_data_file_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_data_file_cancel_button_clicked (GtkButton *button, gpointer user_data);
void on_data_file_browse_button_clicked (GtkButton *button, gpointer user_data);

void     on_data_rv_edit_data_entry_button_clicked (GtkButton *button, gpointer user_data);
gboolean on_data_rv_info_double_clicked            (GtkWidget *widget, GdkEvent *event, gpointer user_data);

void on_data_rv_file_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_data_rv_file_cancel_button_clicked (GtkButton *button, gpointer user_data);

void     on_luminosities_lc_edit_entry_button_clicked (GtkButton *button, gpointer user_data);
gboolean on_luminosities_lc_info_list_double_clicked  (GtkWidget *widget, GdkEvent *event, gpointer user_data);

void populate_dc_parameters_info_list ();

void on_assign_lc_luminosity_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_assign_lc_luminosity_cancel_button_clicked (GtkButton *button, gpointer user_data);

gboolean on_luminosities_el3_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data);
void     on_luminosities_el3_edit_entry_button_clicked (GtkButton *button, gpointer user_data);

void on_assign_el3_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_assign_el3_cancel_button_clicked (GtkButton *button, gpointer user_data);

gboolean on_ld_monochromatic_lc_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data);
void     on_ld_monochromatic_lc_edit_entry_button_clicked (GtkButton *button, gpointer user_data);

void on_assign_ld_monochromatic_lc_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_assign_ld_monochromatic_lc_cancel_button_clicked (GtkButton *button, gpointer user_data);

gboolean on_luminosities_weighting_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data);
void     on_luminosities_weighting_edit_entry_button_clicked (GtkButton *button, gpointer user_data);

void on_assign_weighting_ok_button_clicked  (GtkButton *button, gpointer user_data);
void on_assign_weighting_cancel_button_clicked (GtkButton *button, gpointer user_data);

gboolean on_ld_monochromatic_rv_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data);
void     on_ld_monochromatic_rv_edit_entry_button_clicked (GtkButton *button, gpointer user_data);

gboolean on_spots_primary_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data);
void on_spots_edit_primary_button_clicked (GtkButton *button, gpointer user_data);
gboolean on_spots_secondary_info_list_double_clicked (GtkWidget *widget, GdkEvent *event, gpointer user_data);
void on_spots_edit_secondary_button_clicked (GtkButton *button, gpointer user_data);

void on_assign_ld_monochromatic_rv_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_assign_ld_monochromatic_rv_cancel_button_clicked (GtkButton *button, gpointer user_data);

void on_dc_calculate_button_clicked (GtkButton *button, gpointer user_data);
void on_dc_show_quickbar_button_clicked (GtkButton *button, gpointer user_data);
void on_dc_update_corrections_button_clicked (GtkButton *button, gpointer user_data);
void on_dc_update_selection_button_clicked (GtkButton *button, gpointer user_data);
void on_dc_cancel_button_clicked (GtkButton *button, gpointer user_data);

void on_fitting_fit_button_clicked (GtkButton *button, gpointer user_data);
void on_adjust_switch_toggled_update_fitting_window (GtkToggleButton *togglebutton, gpointer user_data);

void on_plot_lc_plot_to_file_button_clicked (GtkButton *button, gpointer user_data);
void on_plot_rv_plot_to_file_button_clicked (GtkButton *button, gpointer user_data);
void on_fitting_chi2_plot_to_file_button_clicked (GtkButton *button, gpointer user_data);

void on_plot_to_file_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_plot_to_file_cancel_button_clicked (GtkButton *button, gpointer user_data);

void on_plot_to_file_selector_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_plot_to_file_selector_cancel_button_clicked (GtkButton *button, gpointer user_data);

void on_data_model_entry_changed (GtkEditable *editable, gpointer user_data);

void on_fitting_initiate_scripter_button_clicked (GtkButton *button, gpointer user_data);
void on_scripter_close_button_clicked (GtkButton *button, gpointer user_data);

void on_adjust_switch_toggled_update_fitting_quickbar (GtkToggleButton *togglebutton, gpointer user_data);
void on_fitting_quickbar_adjust_switch_toggled_update_main_switches (GtkToggleButton *togglebutton, gpointer user_data);
void on_step_value_changed_update_fitting_quickbar (GtkEditable *editable, gpointer user_data);
void on_fitting_quickbar_step_value_changed_update_main_step_values (GtkEditable *editable, gpointer user_data);

void on_data_file_dependent_variable_changed (GtkEditable *editable, gpointer user_data);

void on_spots_sprim_value_changed (GtkEditable *editable, gpointer user_data);
void on_spots_ssec_value_changed (GtkEditable *editable, gpointer user_data);

void on_assign_primary_spots_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_assign_primary_spots_cancel_button_clicked (GtkButton *button, gpointer user_data);
void on_assign_secondary_spots_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_assign_secondary_spots_cancel_button_clicked (GtkButton *button, gpointer user_data);

void on_dc_show_correlation_matrix_button_clicked (GtkButton *button, gpointer user_data);

void on_luminosities_star_image_plot_button_clicked (GtkButton *button, gpointer user_data);
void on_luminosities_star_image_phase_value_changed (GtkEditable *editable, gpointer user_data);
void on_luminosities_star_image_plot_to_file_button_clicked (GtkButton *button, gpointer user_data);

void on_data_star_name_entry_changed (GtkEditable *editable, gpointer user_data);

void on_lc_data_file_filter_button_clicked (GtkButton *button, gpointer user_data);
void on_rv_data_file_filter_button_clicked (GtkButton *button, gpointer user_data);
void on_filter_menu_specific_filter_activate (GtkMenuItem *menuitem, gpointer user_data);

void on_lagrange_dependent_variable_changed (GtkEditable *editable, gpointer user_data);

void on_scripter_add_action_button_clicked       (GtkButton *button, gpointer user_data);
void on_scripter_update_action_button_clicked    (GtkButton *button, gpointer user_data);
void on_scripter_delete_action_button_clicked    (GtkButton *button, gpointer user_data);
void on_scripter_move_action_up_button_clicked   (GtkButton *button, gpointer user_data);
void on_scripter_move_action_down_button_clicked (GtkButton *button, gpointer user_data);
void on_scripter_execute_script_button_clicked   (GtkButton *button, gpointer user_data);

void on_scripter_action_list_changed        (GtkContainer *container, GtkWidget *widget, gpointer user_data);
void on_scripter_open_script_button_clicked (GtkButton *button, gpointer user_data);
void on_scripter_save_script_button_clicked (GtkButton *button, gpointer user_data);

/* Scripter opening and saving callbacks, called by the generic file selector:*/
void on_open_script_clicked (GtkButton *button, gpointer user_data);
void on_save_script_clicked (GtkButton *button, gpointer user_data);

void on_file_selector_cancel_button_clicked (GtkButton *button, gpointer user_data);

void on_data_sheet_print_to_file_button_clicked (GtkButton *button, gpointer user_data);

void on_menu_bar_file_import_from_fotel_activate (GtkMenuItem *menuitem, gpointer user_data);
void on_import_from_fotel_browse_clicked (GtkButton *button, gpointer user_data);
void on_import_from_fotel_file_selector_ok_button_clicked (GtkButton *button, gpointer user_data);

void on_import_from_fotel_ok_button_clicked (GtkButton *button, gpointer user_data);
void on_critical_phases_changed (GtkEditable *editable, gpointer user_data);

#endif
