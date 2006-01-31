#ifndef PHOEBE_FORTRAN_IMPLEMENTATIONS_H
#define PHOEBE_FORTRAN_IMPLEMENTATIONS_H 1

#include "phoebe_global.h"

int create_lci_file (char filename[], PHOEBE_main_parameters main, PHOEBE_switches switches,
                     PHOEBE_limb_darkening ld, PHOEBE_spots spots, PHOEBE_curve_parameters curve,
										 PHOEBE_wl_dependent_parameters mono);

int create_dci_file (char filename[], double DEL[35], int KEP[35], PHOEBE_main_parameters main,
                     PHOEBE_limb_darkening ld, PHOEBE_spots spots,
										 PHOEBE_switches switches, PHOEBE_mms mms);

int read_out_dci_file (char *filename);

#endif
