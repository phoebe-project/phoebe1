#ifndef PHOEBE_CALCULATIONS_H
	#define PHOEBE_CALCULATIONS_H 1

#include "phoebe_global.h"

double calculate_median (PHOEBE_data data);
double calculate_sum (PHOEBE_data data);
int calculate_critical_potentials (double q, double F, double e, double *L1crit, double *L2crit);


#endif
