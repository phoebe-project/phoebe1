#ifndef PHOEBE_GUI_PLOT_H
#define PHOEBE_GUI_PLOT_H 1

#include <gtk/gtk.h>

void plot_lc_plot       (PHOEBE_plot_device device, char *filename);
void plot_rv_plot       (PHOEBE_plot_device device, char *filename);
void plot_chi2_plot     (PHOEBE_plot_device device, char *filename);
void plot_3d_image_plot (PHOEBE_plot_device device, char *filename);

void plot_lc_zoom_in ();
void plot_lc_zoom_out ();
void plot_lc_shift_left ();
void plot_lc_shift_right ();
void plot_lc_shift_up ();
void plot_lc_shift_down ();

void plot_update_info (int DESTINATION, PHOEBE_calculated_parameters params);

void plot_rv_shift_up ();
void plot_rv_shift_down ();
void plot_rv_shift_left ();
void plot_rv_shift_right ();
void plot_rv_zoom_in ();
void plot_rv_zoom_out ();

int draw_image_to_screen (GtkWidget *frame, char *image_name);

#endif
