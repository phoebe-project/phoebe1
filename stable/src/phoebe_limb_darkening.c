#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "phoebe_global.h"

PHOEBE_vector read_in_ld_coeficients (char *input_filter, int T, double lg, double M, int ld_law)
	{
	int succ;

	int Teff;
	double logg, met;
	double EPS = 0.0001;

	int breaked = 0;

	FILE *ld_file;

	char ld_filename_string[255];
	char *ld_filename_str = ld_filename_string;

	char pm;

	char working_string[255];
	char *working_str = working_string;

	char filter_name_string[10];
	char *filter_name = filter_name_string;

	char current_filter_string[10];
	char *current_filter = current_filter_string;

	double c1, c1e, c2x, c2y, c2e, c3x, c3y, c3e;


	PHOEBE_vector return_value;

	/* Before we proceed, let's be sure there are LD tables present:            */
	if (PHOEBE_LD_SWITCH == 0) { return_value.z = -1.0; return return_value; }

	/* We must take care of the correspondence between the chosen filter and    */
	/* the filter in LD tables:                                                 */
	sprintf (current_filter, "Unsupported");

	/* Bolometric value:                                                        */
	if (strncmp (input_filter, "Bolometric", 10  ) == 0) sprintf (current_filter, "bolo");

	/* Johnson series:                                                          */
	if (strncmp (input_filter, "360nm (U)", 9    ) == 0) sprintf (current_filter, "U"   );
	if (strncmp (input_filter, "440nm (B)", 9    ) == 0) sprintf (current_filter, "B"   );
	if (strncmp (input_filter, "550nm (V)", 9    ) == 0) sprintf (current_filter, "V"   );
	if (strncmp (input_filter, "700nm (R)", 9    ) == 0) sprintf (current_filter, "R"   );
	if (strncmp (input_filter, "900nm (I)", 9    ) == 0) sprintf (current_filter, "I"   );
	if (strncmp (input_filter, "1250nm (J)", 10  ) == 0) sprintf (current_filter, "J"   );
        /* Johnson H is not implemented in the Van Hamme LD Tables
	if (strncmp (input_filter, "1620nm (H)", 10  ) == 0) sprintf (current_filter, "H"   );
        */
	if (strncmp (input_filter, "2200nm (K)", 10  ) == 0) sprintf (current_filter, "K"   );
	if (strncmp (input_filter, "3400nm (L)", 10  ) == 0) sprintf (current_filter, "L"   );
	if (strncmp (input_filter, "5000nm (M)", 10  ) == 0) sprintf (current_filter, "M"   );
	if (strncmp (input_filter, "10200nm (N)", 11 ) == 0) sprintf (current_filter, "N"   );

	/* Stroemgren series:                                                       */
	if (strncmp (input_filter, "350nm (u)", 9    ) == 0) sprintf (current_filter, "u"   );
	if (strncmp (input_filter, "467nm (b)", 9    ) == 0) sprintf (current_filter, "b"   );
	if (strncmp (input_filter, "411nm (v)", 9    ) == 0) sprintf (current_filter, "v"   );
	if (strncmp (input_filter, "547nm (y)", 9    ) == 0) sprintf (current_filter, "y"   );

	/* Hipparcos series:                                                        */
	if (strncmp (input_filter, "505nm (Hp)", 10  ) == 0) sprintf (current_filter, "HIP" );
	if (strncmp (input_filter, "419nm (Bt)", 10  ) == 0) sprintf (current_filter, "TyB" );
	if (strncmp (input_filter, "523nm (Vt)", 10  ) == 0) sprintf (current_filter, "TyV" );

        /* Cousins series:                                                          */
	if (strncmp (input_filter, "647nm (Rc)", 9   ) == 0) sprintf (current_filter, "Rc"  );
	if (strncmp (input_filter, "786nm (Ic)", 9   ) == 0) sprintf (current_filter, "Ic"  );


	/* Radial velocities:                                                       */
	if (strncmp (input_filter, "861nm (RVIJ)", 12) == 0) sprintf (current_filter, "858" );

	/* Falling back to unsupported:                                             */
	if (strcmp (current_filter, "Unsupported") == 0) phoebe_warning ("LD tables do not contain information for this filter!");

	/* First, let us create a string containing a VanHamme filename:            */

	/* Instead of + and - VanHamme uses p and m; therefore we use char pm:      */
	if (M < 0) pm = 'm'; else pm = 'p';

	/* That's it; now let's print it to our string and open the file:           */
	sprintf (ld_filename_str, "%s/limcof_bp_%c%02d.dat", PHOEBE_LD_DIR, pm, (int) (10.0 * fabs (M) + EPS));

	ld_file = fopen (ld_filename_str, "r");

	/* Now we scan that file line by line (fgets function stops at eoln) while  */
	/* we don't find desired T, log g and M; the return value of fgets is       */
	/* either working_str if everything goes right, or NULL if EoF is reached.  */
	do
		{
		if (fgets (working_str, 255, ld_file) == NULL) {breaked = 1; break;}      /* EOF reached */
		succ = sscanf (working_str, "\t\t  Teff = %d K, log g = %lf,  [M/H] = %lf\n", &Teff, &logg, &met);
		}
	while ( (succ != 3) || (T != Teff) || (lg - logg > EPS) || (M - met > EPS) );

	/* If breaked, there is no such entry and user should be aware of that. */
	if (breaked == 1) { return_value.z = -1.0; return return_value; }

	/* Now we want to find the corresponding filter values: */
	do
		{
		if (fgets (working_str, 255, ld_file) == NULL) break;
		succ = sscanf (working_str, "%s %lf (%lf) %lf %lf (%lf) %lf %lf (%lf)\n", filter_name, &c1, &c1e, &c2x, &c2y, &c2e, &c3x, &c3y, &c3e);
		}
	while ( (succ != 9) || (strcmp (filter_name, current_filter) != 0) );

	/* If breaked, there is no such entry and user should be aware of that. */
	if (breaked == 1) { return_value.z = -1.0; return return_value; }

	fclose (ld_file);

	/* Finally, let's assign read values to return_value: */
	if (ld_law == 0) { return_value.x = c1;  return_value.y = 0;   return_value.z = c1e; }
	if (ld_law == 1) { return_value.x = c2x; return_value.y = c2y; return_value.z = c2e; }
	if (ld_law == 2) { return_value.x = c3x; return_value.y = c3y; return_value.z = c3e; }

	return return_value;
	}

PHOEBE_vector interpolate_from_ld_tables (char *input_filter, int T, double lg, double M, int ld_law)
	{
	double EPS = 1e-5;

	char ld_avail_string[255];
	char *ld_avail_str = ld_avail_string;

	FILE *ld_avail;

	int read_T;
	double read_lg, read_M;

	int T_lo = -10, T_hi = -10;
	double lg_lo = -10.0, lg_hi = -10.0;
	double M_lo = -10.0, M_hi = -10.0;

	double delta_1 = 1e20;
	double delta_2 = 1e20;

	PHOEBE_vector ld_coefs, ld_coefs_1, ld_coefs_2;

	double c11, c12, c21, c22, c31, c32;

	/* First, we must open the ld_availability.data file and find interpolation */
	/* limits within which our values are:                                      */
	sprintf (ld_avail_str, "%s/ld_availability.data", PHOEBE_LD_DIR);
	ld_avail = fopen (ld_avail_str, "r");

	do
		{
		if (fscanf (ld_avail, "%d %lf %lf\n", &read_T, &read_lg, &read_M) != 3) break;

		if ( (read_T <= T) && (read_lg <= lg) && (read_M <= M) &&
	     ( (read_T-T)*(read_T-T)+(read_lg-lg)*(read_lg-lg)+(read_M-M)*(read_M-M) < delta_1 ) )
			{
			delta_1 = (read_T-T)*(read_T-T)+(read_lg-lg)*(read_lg-lg)+(read_M-M)*(read_M-M);
			T_lo  = read_T; lg_lo = read_lg; M_lo  = read_M;
			}

		if ( (read_T >= T) && (read_lg >= lg) && (read_M >= M) &&
	     ( (read_T-T)*(read_T-T)+(read_lg-lg)*(read_lg-lg)+(read_M-M)*(read_M-M) < delta_2 ) )
			{
			delta_2 = (read_T-T)*(read_T-T)+(read_lg-lg)*(read_lg-lg)+(read_M-M)*(read_M-M);
			T_hi  = read_T; lg_hi = read_lg; M_hi  = read_M;
			}
		}
	while (TRUE);

	fclose (ld_avail);

	/* The idea of interpolation is as follows: we expand f (T, lg, M) in Tay-  */
	/* lor series to the 1st order, where we substitute 1st derivatives by fi-  */
	/* nite differences: \partial f / \partial x_i = (f-f_0) / (x_i-x_{i0}).    */
	/* What we take for x_{i0} depends on whether the interpolating value lies  */
	/* closer to _lo or to _hi values, but we always presume it's _lo.          */

	ld_coefs_1 = read_in_ld_coeficients (input_filter, T_lo, lg_lo, M_lo, ld_law);
	ld_coefs_2 = read_in_ld_coeficients (input_filter, T_hi, lg_lo, M_lo, ld_law);
	if (T_hi - T_lo < EPS)
		{
		c11 = c12 = 0.0;
		}
	else
		{
		c11 = (ld_coefs_2.x - ld_coefs_1.x) * (T - T_lo) / (T_hi - T_lo);
		c12 = (ld_coefs_2.y - ld_coefs_1.y) * (T - T_lo) / (T_hi - T_lo);
		}

	ld_coefs_1 = read_in_ld_coeficients (input_filter, T_lo, lg_lo, M_lo, ld_law);
	ld_coefs_2 = read_in_ld_coeficients (input_filter, T_lo, lg_hi, M_lo, ld_law);
	if (lg_hi - lg_lo < EPS)
		{
		c21 = c22 = 0.0;
		}
	else
		{
		c21 = (ld_coefs_2.x - ld_coefs_1.x) * (lg - lg_lo) / (lg_hi - lg_lo);
		c22 = (ld_coefs_2.y - ld_coefs_1.y) * (lg - lg_lo) / (lg_hi - lg_lo);
		}

	ld_coefs_1 = read_in_ld_coeficients (input_filter, T_lo, lg_lo, M_lo, ld_law);
	ld_coefs_2 = read_in_ld_coeficients (input_filter, T_lo, lg_lo, M_hi, ld_law);
	if (M_hi - M_lo < EPS)
		{
		c31 = c32 = 0.0;
		}
	else
		{
		c31 = (ld_coefs_2.x - ld_coefs_1.x) * (M - M_lo) / (M_hi - M_lo);
		c32 = (ld_coefs_2.y - ld_coefs_1.y) * (M - M_lo) / (M_hi - M_lo);
		}
		
	ld_coefs.x = ld_coefs_1.x + c11 + c21 + c31;
	ld_coefs.y = ld_coefs_1.y + c12 + c22 + c32;

	return ld_coefs;
	}
