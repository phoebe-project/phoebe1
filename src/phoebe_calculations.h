#ifndef PHOEBE_CALCULATIONS_H
	#define PHOEBE_CALCULATIONS_H 1

#include "phoebe_global.h"

double calculate_median (PHOEBE_data data);
double calculate_sum (PHOEBE_data data);
int calculate_critical_potentials (double q, double F, double e, double *L1crit, double *L2crit);

double calculate_eccentric_anomaly_from_true_anomaly (double upsilon, double e);
double calculate_mean_anomaly_from_eccentric_anomaly (double E, double e);
int calculate_critical_phases (double omega, double e, double pshift, double *phiper, double *phiconj);

#endif
