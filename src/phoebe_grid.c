#include <math.h>
#include <stdio.h>

void calculate_estimated_synthetic_grid_file_size (int params_no, int nodes_no, int vertexes_no, int filters_no, char **size_str)
	{
	double size = pow (nodes_no, params_no) * (8.0 * vertexes_no + 1.0) * filters_no;

	char working_string[255];
	char *working_str = working_string;

	if ( size < 1024 )
		sprintf (working_str, "Estimated grid size: %0.0lf bytes", size);

	if ( (size > 1024) && (size < 1024 * 1024) )
		sprintf (working_str, "Estimated grid size: %1.1lf Kb", size / 1024);

	if ( (size > 1024 * 1024) && (size < 1024 * 1024 * 1024) )
		sprintf (working_str, "Estimated grid size: %2.2lf Mb", size / 1024 / 1024);

	if ( size > 1024 * 1024 * 1024 )
		sprintf (working_str, "Estimated grid size: %3.3lf Gb", size / 1024 / 1024 / 1024);

	*size_str = working_string;

	return;
	}
