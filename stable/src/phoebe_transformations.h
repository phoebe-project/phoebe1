#ifndef PHOEBE_TRANSFORMATIONS_H
#define PHOEBE_TRANSFORMATIONS_H 1

#include <gtk/gtk.h>

void transform_phase_to_hjd             (PHOEBE_data *data, double hjd0, double period);
void transform_hjd_to_phase             (PHOEBE_data *data, double hjd0, double period, double dpdt);
void transform_magnitude_to_flux        (PHOEBE_data *data, double mnorm);
void transform_flux_to_magnitude        (PHOEBE_data *data, double mnorm);
void transform_100kms_to_kms            (PHOEBE_data *data);
void transform_kms_to_100kms            (PHOEBE_data *data);
void transform_absolute_error_to_weight (PHOEBE_data *data);
void remove_reddening_from_data         (PHOEBE_data *data, double lambda, double R, double EBV);
void remove_reddening_from_fluxes       (PHOEBE_data *data, double lambda, double R, double EBV);
void normalize_rv_to_orbit              (PHOEBE_data *data, double sma, double period);

void alias_phase_to_interval (PHOEBE_data *data, double phmin, double phmax);

void transform_flux_sigma_to_magnitude_sigma (double flux_sigma, double mag_sigma);
void transform_magnitude_sigma_to_flux_sigma (double mag_sigma, double flux_sigma);

void get_plot_limits_of_data (PHOEBE_data data, double *xmin, double *ymin, double *xmax, double *ymax);

void calculate_residuals (PHOEBE_data *set1, PHOEBE_data *set2);

#endif
