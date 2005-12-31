#ifndef PHOEBE_GUI_ACCESSORIES_H
#define PHOEBE_GUI_ACCESSORIES_H 1

#include <gtk/gtk.h>
#include "phoebe_global.h"

void parse_startup_line (int argc, char *argv[]);
void phoebe_init ();

int  file_exists                    (char *file_name);
int everything_ok_with_the_filename (char *file_name);
void strip_string_tail              (char *in);
int parse_input_data                (char **in);
void print_to_status_bar            (char *text);

GtkWidget *create_warning_window (char *title, char *main_label, char *description1, char *description2, GtkSignalFunc ok_function, GtkSignalFunc cancel_function);
GtkWidget *create_notice_window  (char *title, char *main_label, char *description1, char *description2, GtkSignalFunc ok_function);

void set_clist_justifications ();

void add_empty_record_to_all_lc_dependent_info_lists ();
void add_empty_record_to_all_rv_dependent_info_lists ();
void add_empty_record_to_lc_info_list ();
void add_empty_record_to_rv_info_list ();
void add_empty_record_to_luminosities_lc_info_list ();
void add_empty_record_to_luminosities_el3_info_list ();
void add_empty_record_to_ld_monochromatic_lc_info_list ();
void add_empty_record_to_ld_monochromatic_rv_info_list ();
void add_empty_record_to_luminosities_weighting_info_list ();
void add_empty_record_to_spots_primary_info_list ();
void add_empty_record_to_spots_secondary_info_list ();
void add_empty_record_to_data_files_info_list ();

void add_filters_to_available_filter_lists ();
void add_filters_to_lc_plot_filter_list ();
void add_filters_to_rv_plot_filter_list ();
void add_filters_to_chi2_filter_list ();
void add_filters_to_ld_filter_list ();

int create_plot_to_file_drop_down_menu ();

GtkWidget           *phoebe_widget (PHOEBE_keyword keyword);
PHOEBE_keyword       get_phoebe_keyword_from_keyword_name (char *keyword);
void                 phoebe_common_name (PHOEBE_keyword keyword, char **string);

void define_scripter_commands ();
void add_to_scripter_commands (PHOEBE_script_command command);
void populate_scripter_command_list ();

#endif
