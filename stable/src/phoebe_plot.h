#ifndef PHOEBE_PLOT_H
#define PHOEBE_PLOT_H 1

#include <gtk/gtk.h>

int scan_temporary_directory_for_lci_file_index (char *prefix);
int scan_temporary_directory_for_dci_file_index (char *prefix);

void create_lci_input_file (char *prefix, PHOEBE_main_parameters main, PHOEBE_switches switches,
     PHOEBE_limb_darkening ld, PHOEBE_spots spots, PHOEBE_curve_parameters curve,
		 PHOEBE_wl_dependent_parameters mono);

void create_dci_input_file (double DEL[35], int KEP[35], PHOEBE_main_parameters main, PHOEBE_limb_darkening ld, PHOEBE_spots spots, PHOEBE_switches switches, PHOEBE_mms mms);

void calculate_plot_limits (PHOEBE_data synthetic_data, PHOEBE_data experimental_data, double *xmin, double *ymin, double *xmax, double *ymax, int plot_synthetic, int plot_experimental, double x_offset, double y_offset, double zoom);

void create_lc_plot_using_sm   (PHOEBE_plot_device device, char *filename, PHOEBE_data synthetic_data, PHOEBE_data experimental_data, int indep, int dep, int grid, int box, double x_offset, double y_offset, double zoom, int plot_synthetic, int plot_experimental);
void create_rv_plot_using_sm   (PHOEBE_plot_device device, char *filename, PHOEBE_data synthetic_data, PHOEBE_data experimental_data, int indep, int dep, int grid, int box, double x_offset, double y_offset, double zoom, int plot_synthetic, int plot_experimental);
void create_chi2_plot_using_sm (PHOEBE_plot_device device, char *filename, PHOEBE_3D_data chi2);
void create_3d_image_plot_using_sm (PHOEBE_plot_device device, char *filename, PHOEBE_data data);

void create_lc_plot_using_gnuplot (PHOEBE_plot_device device, char *filename, PHOEBE_data synthetic_data, PHOEBE_data experimental_data, int indep, int dep, int grid, int box, double x_offset, double y_offset, double zoom, int plot_synthetic, int plot_experimental);
void create_rv_plot_using_gnuplot (PHOEBE_plot_device device, char *filename, PHOEBE_data synthetic_data, PHOEBE_data experimental_data, int indep, int dep, int grid, int box, double x_offset, double y_offset, double zoom, int plot_synthetic, int plot_experimental);
void create_chi2_plot_using_gnuplot (PHOEBE_plot_device device, char *filename, PHOEBE_3D_data chi2);
void create_3d_image_plot_using_gnuplot (PHOEBE_plot_device device, char *filename, PHOEBE_data data);


#endif
