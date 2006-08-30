#ifndef PHOEBE_ALLOCATIONS_H
#define PHOEBE_ALLOCATIONS_H 1

#include "phoebe_global.h"

int allocate_memory_for_data_record (PHOEBE_data_record **data, int records_no);
int allocate_memory_for_data        (PHOEBE_data *data);

int allocate_memory_for_spots       (PHOEBE_spots *spots);
int free_memory_allocated_for_spots (PHOEBE_spots *spots);

PHOEBE_main_parameters          read_in_main_parameters ();
PHOEBE_switches                 read_in_switches ();
PHOEBE_curve_parameters         read_in_curve_parameters ();
PHOEBE_limb_darkening           read_in_ld_coefficients ();
PHOEBE_mms                      read_in_mms ();
PHOEBE_wl_dependent_parameters  read_in_wl_dependent_parameters (char *filter);

int read_in_spots (PHOEBE_spots *spots);

int read_in_data_file_info       (GtkWidget *parent, PHOEBE_data_record *input);
int read_in_synthetic_lc_data    (char *filename, PHOEBE_data *data, PHOEBE_calculated_parameters *params, int indep, int dep);
int read_in_experimental_lc_data (int curve, PHOEBE_data *data, int indep, int dep);
int read_in_synthetic_rv_data    (char *filename, PHOEBE_data *data, PHOEBE_calculated_parameters *params, int indep, int dep);
int read_in_experimental_rv_data (int curve, PHOEBE_data *data, int indep, int dep, double requested_vunit);
int read_in_3d_image_data        (char *filename, PHOEBE_data *data);

int read_in_dco_values (char *filename, PHOEBE_dco_record *dco_record, double *correlation_matrix, int el3_switch);

int read_in_data_file_specifics ();

#endif
