#ifndef PHOEBE_PHSV_PCSV_H
#define PHOEBE_PHSV_PCSV_H 1

#include <gtk/gtk.h>

double calculate_phsv_value (int ELLIPTIC, double D, double q, double r, double F, double lambda, double nu);
double calculate_pcsv_value (int ELLIPTIC, double D, double q, double r, double F, double lambda, double nu);

#endif
