#ifndef PHOEBE_CHI2_H
#define PHOEBE_CHI2_H 1

#include <gtk/gtk.h>

#include "phoebe_global.h"

double calculate_chi2 (PHOEBE_data synthetic_data, PHOEBE_data experimental_data, double sigma, int type);

#endif
