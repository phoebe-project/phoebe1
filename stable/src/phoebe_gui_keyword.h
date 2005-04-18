#ifndef PHOEBE_GUI_KEYWORD_H
#define PHOEBE_GUI_KEYWORD_H 1

void add_to_keyword_file   (const char *keyword, GtkWidget *WIDGET, const char *widget_name, FILE *keyword_file);
void get_from_keyword_file (GtkWidget *WIDGET, const char *widget_name, char *value, FILE *keyword_file);

void save_keyword_file ();
void open_keyword_file (const char *filename);
void open_legacy_keyword_file (const char *filename);

int check_directory_consistency (GtkWidget *filesel1, GtkWidget *filesel2);
void update_keyword_file_list ();

void add_entry_to_data_sheet_list (char *keyword, char *value);
void add_parameter_to_data_sheet_list (char *keyword, PHOEBE_keyword delimeter);

void add_all_parameters_to_data_sheet_list ();
void add_relevant_parameters_to_data_sheet_list ();
void save_data_sheet_parameters_to_file (char *filename);

int import_from_fotel (char *filename, char *passed_prefix);
int enumerate_passbands ();
int gui_update_passbands ();

#endif
